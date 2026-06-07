package internal

import (
	"bufio"
	"log/slog"
	"net"
	"strings"
	"unicode"
)

func Handle(vcs *VCS, connection net.Conn) {
	slog.Info("client connected", "remote_address", connection.RemoteAddr().String())
	defer func() {
		slog.Info("client disconnected", "address", connection.RemoteAddr().String())
	}()
	defer connection.Close()

	r := bufio.NewReader(connection)
	w := bufio.NewWriter(connection)

	// Send the initial ready message
	if !sendMessage(w, "READY\n") {
		return
	}

	// Switch to command parsing mode
	for {
		command, err := r.ReadString('\n')
		if err != nil {
			return
		}
		command = strings.TrimRightFunc(command, unicode.IsSpace)
		response := vcs.ExecuteCommand(command, r)

		if !sendMessage(w, response.Response) {
			return
		}

		if response.ShouldQuit {
			return
		}

		if response.ShouldSendReady {
			if !sendMessage(w, "READY\n") {
				return
			}
		}
	}
}

func sendMessage(w *bufio.Writer, s string) bool {
	if _, err := w.WriteString(s); err != nil {
		return false
	}
	if err := w.Flush(); err != nil {
		return false
	}
	return true
}
