package protocol

import (
	"errors"
	"io"

	"github.com/ananthvk/protohackers-go/11_pest_control/internal/serialization"
)

const maxMessageLength = 64 * 1024

func WriteMessage(w io.Writer, message any) error {
	cw := NewChecksumWriter(w)

	var p [1]byte
	var payloadSize int

	switch v := message.(type) {
	case ErrorMessage:
		p[0] = MessageError
		payloadSize += 4              // for string size
		payloadSize += len(v.Message) // for the string
	case DialAuthorityMessage:
		p[0] = MessageDialAuthority
		payloadSize += 4
	case CreatePolicyMessage:
		p[0] = MessageCreatePolicy
		payloadSize += 4              // string size
		payloadSize += len(v.Species) // string
		payloadSize += 1              // for action byte
	case DeletePolicyMessage:
		p[0] = MessageDeletePolicy
		payloadSize += 4
	case string:
		_, err := w.Write([]byte(v))
		return err
	default:
		panic("logic error: Invalid message type to write")
	}

	// Write the type (one byte)
	if _, err := cw.Write(p[:]); err != nil {
		return err
	}

	// Write the total size (5 (type + length) + payloadSize + 1 (checksum))
	var totalSize uint32 = uint32(payloadSize) + 6
	if err := serialization.WriteValue(cw, totalSize); err != nil {
		return err
	}

	// Write the payload
	if err := serialization.WriteValue(cw, message); err != nil {
		return err
	}

	// Write the checksum
	if err := cw.WriteSum(); err != nil {
		return err
	}
	return nil
}

func ReadMessage(r io.Reader) (any, error) {
	cr := NewChecksumReader(r)

	var typ [1]byte
	if _, err := io.ReadFull(cr, typ[:]); err != nil {
		return nil, err
	}

	// Read the length of the packet
	var length uint32
	if err := serialization.ReadValue(cr, &length); err != nil {
		return nil, err
	}
	if length < 6 || length > maxMessageLength {
		return nil, errors.New("bad message")
	}

	var result any

	switch typ[0] {
	case MessageOk:
		var msg OkMessageType
		if length != 6 {
			return nil, errors.New("bad message")
		}
		result = msg
	case MessageTargetPopulations:
		var msg TargetPopulationsMessage
		if err := serialization.ReadValue(cr, &msg); err != nil {
			return nil, err
		}
		result = msg
	case MessagePolicyResult:
		var msg PolicyResultMessage
		if err := serialization.ReadValue(cr, &msg); err != nil {
			return nil, err
		}
		result = msg
	case MessageSiteVisit:
		var msg SiteVisitMessage
		if err := serialization.ReadValue(cr, &msg); err != nil {
			return nil, err
		}
		result = msg
	case MessageHello:
		var msg HelloMessageType
		if length != 25 {
			return nil, errors.New("bad message")
		}
		var buf [19]byte
		if _, err := io.ReadFull(cr, buf[:]); err != nil {
			return nil, err
		}
		if string(buf[:]) != HelloMessage[5:len(HelloMessage)-1] {
			return nil, errors.New("bad message")
		}
		result = msg
	default:
		return nil, errors.New("invalid message type")
	}

	if err := cr.VerifySum(); err != nil {
		return nil, err
	}

	return result, nil
}
