package internal

import (
	"errors"
	"fmt"
	"io"
	"log/slog"
	"regexp"
	"slices"
	"strconv"
	"strings"
	"sync"
)

// Also allows just a / and trailing slash
var dirPathRe = regexp.MustCompile(
	`^/$|^/[a-zA-Z0-9._-]+(?:/[a-zA-Z0-9._-]+)*/?$`,
)
var filePathRe = regexp.MustCompile(`^/[a-zA-Z0-9._-]+(?:/[a-zA-Z0-9._-]+)*$`)

type File struct {
	path      string
	revisions []string
}

type VCS struct {
	mu    sync.Mutex
	files map[string]*File
}

type CommandExecutionResponse struct {
	ShouldSendReady bool
	ShouldQuit      bool
	Response        string
}

func NewVCS() *VCS {
	return &VCS{
		files: map[string]*File{},
	}
}

func NewFile(path string) *File {
	return &File{
		path:      path,
		revisions: []string{},
	}
}

func (vcs *VCS) ExecuteCommand(command string, r io.Reader) CommandExecutionResponse {
	args := strings.Split(command, " ")
	quoted := fmt.Sprintf(`'%s'`, strings.Join(args, `', '`))
	slog.Info("execute command", "args", quoted)

	switch strings.ToUpper(args[0]) {
	case "GET":
		return vcs.handleGet(args)
	case "PUT":
		return vcs.handlePut(args, r)
	case "LIST":
		return vcs.handleList(args)
	case "HELP":
		return vcs.handleHelp()
	}
	return CommandExecutionResponse{
		ShouldQuit: true,
		Response:   errIllegalMethod + args[0] + "\n",
	}
}

func (vcs *VCS) handleHelp() CommandExecutionResponse {
	return CommandExecutionResponse{
		ShouldSendReady: true,
		Response:        usageHelp,
	}
}

func (vcs *VCS) handleList(args []string) CommandExecutionResponse {
	if len(args) != 2 {
		return CommandExecutionResponse{
			ShouldSendReady: true,
			Response:        errUsageList,
		}
	}
	if !isValidDirPath(args[1]) {
		return CommandExecutionResponse{
			Response: errIllegalDirName,
		}
	}

	entries := vcs.Ls(args[1])
	slices.Sort(entries)
	var response string
	if len(entries) > 0 {
		response = fmt.Sprintf("OK %d\n%s\n", len(entries), strings.Join(entries, "\n"))
	} else {
		response = "OK 0\n"
	}

	return CommandExecutionResponse{
		ShouldSendReady: true,
		Response:        response,
	}
}

func (vcs *VCS) handlePut(args []string, r io.Reader) CommandExecutionResponse {
	if len(args) != 3 {
		return CommandExecutionResponse{
			ShouldSendReady: true,
			Response:        errUsagePut,
		}
	}

	path := args[1]

	if !isValidFilePath(path) {
		return CommandExecutionResponse{
			Response: errIllegalFileName,
		}
	}

	// parse size from args[2], if not integer assume 0
	size, err := strconv.Atoi(args[2])
	if err != nil {
		size = 0
	}
	var content string
	if size <= 0 {
		content = ""
	} else {
		buf, err := io.ReadAll(io.LimitReader(r, int64(size)))
		if err != nil {
			return CommandExecutionResponse{
				ShouldQuit: true,
				Response:   "ERR reading file contents",
			}
		}
		content = string(buf)
	}

	if !isPrint(content) {
		return CommandExecutionResponse{
			ShouldSendReady: true,
			Response:        errTextFilesOnly,
		}
	}

	revision := vcs.updateFileContent(path, content)

	return CommandExecutionResponse{
		ShouldSendReady: true,
		Response:        fmt.Sprintf("OK r%d\n", revision),
	}
}

func (vcs *VCS) handleGet(args []string) CommandExecutionResponse {
	// Args should be of length 2/3 (i.e. GET path or GET path [revision])
	if !(len(args) == 2 || len(args) == 3) {
		return CommandExecutionResponse{
			ShouldSendReady: true,
			Response:        errUsageGet,
		}
	}
	if !isValidFilePath(args[1]) {
		return CommandExecutionResponse{
			Response: errIllegalFileName,
		}
	}
	var revision string = ""
	if len(args) == 3 {
		revision = args[2]
	}
	content, err := vcs.getFileContent(args[1], revision)

	if err != nil {
		return CommandExecutionResponse{
			ShouldSendReady: true,
			Response:        err.Error(),
		}
	}

	return CommandExecutionResponse{
		ShouldSendReady: true,
		Response:        fmt.Sprintf("OK %d\n%s", len(content), content),
	}
}

func (vcs *VCS) updateFileContent(path string, content string) int {
	vcs.mu.Lock()
	defer vcs.mu.Unlock()
	file, ok := vcs.files[path]
	if !ok {
		file = NewFile(path)
		vcs.files[path] = file
	}
	n := len(file.revisions)
	if n >= 1 && file.revisions[n-1] == content {
		// No change
		return n
	}
	file.revisions = append(file.revisions, content)
	return n + 1
}

func (vcs *VCS) getFileContent(path string, revision string) (string, error) {
	vcs.mu.Lock()
	defer vcs.mu.Unlock()

	file, ok := vcs.files[path]
	if !ok {
		return "", errors.New(errNoSuchFile)
	}

	if revision == "" {
		return file.revisions[len(file.revisions)-1], nil
	}

	if !strings.HasPrefix(revision, "r") {
		return "", errors.New(errNoSuchRevision)
	}

	revNum, err := strconv.Atoi(strings.TrimPrefix(revision, "r"))
	if err != nil || revNum <= 0 {
		return "", errors.New(errNoSuchRevision)
	}

	if revNum > len(file.revisions) {
		return "", errors.New(errNoSuchRevision)
	}

	return file.revisions[revNum-1], nil
}

func (vcs *VCS) Ls(dirPath string) []string {
	vcs.mu.Lock()
	defer vcs.mu.Unlock()

	var entries []string

	// Make sure that the path ends with a slash so that it doesn't match unrelated files
	prefix := dirPath
	if !strings.HasSuffix(prefix, "/") {
		prefix += "/"
	}
	if prefix == "//" {
		prefix = "/"
	}

	seenDirs := make(map[string]bool)

	// If both file & dir have same name, file will be preferred
	fileSeen := make(map[string]struct{})

	for key, value := range vcs.files {
		if !strings.HasPrefix(key, prefix) {
			continue
		}

		remaining := strings.TrimPrefix(key, prefix)
		if remaining == "" {
			continue
		}

		idx := strings.Index(remaining, "/")
		if idx == -1 {
			fileSeen[remaining] = struct{}{}
			entry := fmt.Sprintf("%s r%d", remaining, len(value.revisions))
			entries = append(entries, entry)
		} else {
			subDir := remaining[:idx]
			_, ok := fileSeen[subDir]
			if ok {
				continue
			}
			if !seenDirs[subDir] {
				seenDirs[subDir] = true
				entry := fmt.Sprintf("%s/ DIR", subDir)
				entries = append(entries, entry)
			}
		}
	}

	return entries
}

func isValidFilePath(s string) bool {
	return filePathRe.MatchString(s)
}

func isValidDirPath(s string) bool {
	return dirPathRe.MatchString(s)
}

func isPrint(s string) bool {
	for i := 0; i < len(s); i++ {
		b := s[i]
		// Also allow whitespace chars
		if b == '\n' || b == '\r' || b == '\t' {
			continue
		}
		if b < 32 || b > 126 {
			return false
		}
	}
	return true
}
