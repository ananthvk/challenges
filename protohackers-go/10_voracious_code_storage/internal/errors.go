package internal

const (
	errIllegalMethod   = "ERR illegal method: "
	errUsageGet        = "ERR usage: GET file [revision]\n"
	errUsagePut        = "ERR usage: PUT file length newline data\n"
	errUsageList       = "ERR usage: LIST dir\n"
	usageHelp          = "OK usage: HELP|GET|PUT|LIST\n"
	errIllegalFileName = "ERR illegal file name\n"
	errIllegalDirName  = "ERR illegal dir name\n"
	errTextFilesOnly   = "ERR text files only\n"
	errNoSuchFile      = "ERR no such file\n"
	errNoSuchRevision  = "ERR no such revision\n"
)
