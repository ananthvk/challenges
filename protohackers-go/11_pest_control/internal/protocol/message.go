package protocol

const (
	MessageHello             = 0x50 // W, R
	MessageError             = 0x51 // W
	MessageOk                = 0x52 // R
	MessageDialAuthority     = 0x53 // W
	MessageTargetPopulations = 0x54 // R
	MessageCreatePolicy      = 0x55 // W
	MessageDeletePolicy      = 0x56 // W
	MessagePolicyResult      = 0x57 // R
	MessageSiteVisit         = 0x58 // R
)

const (
	PolicyCull     = 0x90
	PolicyConserve = 0xa0
)

type Message any

// 0x50 Hello (Sent & Received by server)
const HelloMessage = "\x50" +
	"\x00\x00\x00\x19" +
	"\x00\x00\x00\x0b" +
	"\x70\x65\x73\x74" +
	"\x63\x6f\x6e\x74" +
	"\x72\x6f\x6c" +
	"\x00\x00\x00\x01" +
	"\xce"

type HelloMessageType struct {
}

// 0x51 Error (Response from server)
type ErrorMessage struct {
	Message string
}

// 0x53 DialAuthority (Request to authority)
type DialAuthorityMessage struct {
	Site uint32
}

type PopulationRange struct {
	Species string
	Min     uint32
	Max     uint32
}

// 0x54 TargetPopulations (Response from authority)
type TargetPopulationsMessage struct {
	Site        uint32
	Populations []PopulationRange
}

// 0x55 CreatePolicy (Request to authority)
type CreatePolicyMessage struct {
	Species string
	Action  uint8
}

// 0x57 PolicyResult (Response from authority)
type PolicyResultMessage struct {
	Policy uint32
}

// 0x56 DeletePolicy (Request to authority)
type DeletePolicyMessage struct {
	Policy uint32
}

// 0x52 OK (Response from authority)
const OkMessage = "\x52" +
	"\x00\x00\x00\x06" +
	"\xa8"

type OkMessageType struct {
}

type PopulationCount struct {
	Species string
	Count   uint32
}

// 0x58 SiteVisit (Request from client)
type SiteVisitMessage struct {
	Site       uint32
	Population []PopulationCount
}
