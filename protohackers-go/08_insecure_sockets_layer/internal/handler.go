package internal

import (
	"bufio"
	"log/slog"
	"net"

	"github.com/ananthvk/protohackers-go/08_insecure_sockets_layer/internal/isl"
)

// Handle handles a single client connection. This should be run in a separate gorutine so that requests can be handled
// concurrently.
func Handle(connection net.Conn) {
	slog.Info("client connected", "remote_address", connection.RemoteAddr().String())
	defer func() {
		slog.Info("client disconnected", "address", connection.RemoteAddr().String())
	}()
	defer connection.Close()

	// Read the cipherspec
	cipherspec, err := isl.ReadCipherSpec(connection)
	if err != nil {
		slog.Info("error reading cipherspec", "error", err, "address", connection.RemoteAddr().String())
		return
	}
	slog.Info("got cipherspec", "cipherspec", cipherspec, "address", connection.RemoteAddr().String())
	// Wrap the connection
	connection = isl.WrapConn(connection, cipherspec)
	r := bufio.NewReader(connection)
	w := bufio.NewWriter(connection)

	for {
		line, err := r.ReadString('\n')
		if err != nil {
			return
		}
		maxToy := GetMaxToy(line) + "\n"
		if _, err = w.WriteString(maxToy); err != nil {
			return
		}
		if err = w.Flush(); err != nil {
			return
		}
	}
}
