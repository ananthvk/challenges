package job

import (
	"encoding/json"
)

type Job struct {
	Id       int
	Payload  json.RawMessage
	Priority int
	Queue    string
	Running  bool
}
