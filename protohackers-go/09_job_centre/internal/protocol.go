package internal

import (
	"bytes"
	"encoding/json"
	"errors"
	"io"
)

type Request struct {
	RequestType string          `json:"request"`
	Queue       *string         `json:"queue"`
	Job         json.RawMessage `json:"job"`
	Priority    *int            `json:"pri"`
	Queues      []string        `json:"queues"`
	Wait        *bool           `json:"wait"`
	Id          *int            `json:"id"`
	WaitParsed  bool
}

type Response struct {
	Status   string          `json:"status"`
	Id       int             `json:"id,omitempty"`
	Job      json.RawMessage `json:"job,omitempty"`
	Priority int             `json:"pri,omitempty"`
	Queue    string          `json:"queue,omitempty"`
	Error    string          `json:"error,omitempty"`
}

func ParseRequest(request []byte) (Request, error) {
	decoder := json.NewDecoder(bytes.NewReader(request))
	decoder.DisallowUnknownFields()

	var req Request
	err := decoder.Decode(&req)
	if err != nil {
		return Request{}, err
	}
	err = decoder.Decode(&struct{}{})
	if err != io.EOF {
		return Request{}, errors.New("request contains extra data after JSON object")
	}

	// Perform validation to ensure that all the required fields are present (according to request)
	switch req.RequestType {
	case "put":
		if req.Queue == nil || len(*req.Queue) == 0 {
			return Request{}, errors.New("put request: missing queue")
		}
		if req.Priority == nil || *req.Priority < 0 {
			return Request{}, errors.New("put request: invalid priority")
		}
		if len(req.Job) == 0 || !isJSONObject(req.Job) {
			return Request{}, errors.New("put request: invalid job")
		}
	case "get":
		if len(req.Queues) == 0 {
			return Request{}, errors.New("get request: missing queues")
		}
		if req.Wait != nil {
			req.WaitParsed = *req.Wait
		}
	case "delete":
		if req.Id == nil {
			return Request{}, errors.New("delete request: missing id")
		}
	case "abort":
		if req.Id == nil {
			return Request{}, errors.New("abort request: missing id")
		}
	default:
		return Request{}, errors.New("invalid request type")
	}
	return req, nil
}

func SerializeResponse(resp Response) string {
	data, err := json.Marshal(resp)
	if err != nil {
		panic("error while marshalling response")
	}
	return string(data) + "\n"
}

func isJSONObject(raw json.RawMessage) bool {
	for i := 0; i < len(raw); i++ {
		b := raw[i]
		if b == ' ' || b == '\t' || b == '\n' || b == '\r' {
			continue
		}
		return b == '{'
	}
	return false
}
