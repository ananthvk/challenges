package internal

import (
	"bufio"
	"log/slog"
	"net"
	"time"

	"github.com/ananthvk/protohackers-go/11_pest_control/internal/protocol"
)

const timeoutDuration = time.Second * 15

func Handle(pest *PestControl, connection net.Conn) {
	slog.Info("client connected", "remote_address", connection.RemoteAddr().String())
	defer func() {
		slog.Info("client disconnected", "address", connection.RemoteAddr().String())
	}()
	defer connection.Close()

	r := bufio.NewReader(connection)
	w := bufio.NewWriter(connection)

	// Send the hello message
	if !Send(w, protocol.HelloMessage) {
		return
	}

	connection.SetReadDeadline(time.Now().Add(timeoutDuration))
	// The first message should be a hello message
	msg, err := protocol.ReadMessage(r)
	if err != nil {
		Send(w, protocol.ErrorMessage{Message: err.Error()})
		return
	}
	_, ok := msg.(protocol.HelloMessageType)
	if !ok {
		Send(w, protocol.ErrorMessage{Message: "first message must be hello"})
		return
	}

	for {
		// Add a timeout to prevent reads from hanging
		connection.SetReadDeadline(time.Now().Add(timeoutDuration))

		// Read a message
		msg, err := protocol.ReadMessage(r)
		if err != nil {
			Send(w, protocol.ErrorMessage{Message: err.Error()})
			return
		}
		// From clients, only MessageSiteVisit is allowed
		siteVisit, ok := msg.(protocol.SiteVisitMessage)
		if !ok {
			Send(w, protocol.ErrorMessage{Message: "invalid message type"})
			return
		}
		slog.Info("got site visit", "remote_address", connection.RemoteAddr().String())
		if err := pest.UpdatePolicies(siteVisit); err != nil {
			Send(w, protocol.ErrorMessage{Message: err.Error()})
			return
		}
	}
}

func Send(w *bufio.Writer, m protocol.Message) bool {
	if err := protocol.WriteMessage(w, m); err != nil {
		return false
	}
	if err := w.Flush(); err != nil {
		return false
	}
	return true
}
