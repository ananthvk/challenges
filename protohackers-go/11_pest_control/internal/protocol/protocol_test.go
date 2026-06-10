package protocol

import (
	"bytes"
	"testing"
)

func TestReadMessageHello(t *testing.T) {
	data := []byte{
		0x50,
		0x00, 0x00, 0x00, 0x19,
		0x00, 0x00, 0x00, 0x0b,
		0x70, 0x65, 0x73, 0x74,
		0x63, 0x6f, 0x6e, 0x74,
		0x72, 0x6f, 0x6c,
		0x00, 0x00, 0x00, 0x01,
		0xce,
	}

	msg, err := ReadMessage(bytes.NewReader(data))
	if err != nil {
		t.Fatalf("ReadMessage failed: %v", err)
	}
	_, ok := msg.(HelloMessageType)
	if !ok {
		t.Fatalf("got %T, want HelloMessageType", msg)
	}
}

func TestReadMessageOk(t *testing.T) {
	data := []byte{0x52, 0x00, 0x00, 0x00, 0x06, 0xa8}

	msg, err := ReadMessage(bytes.NewReader(data))
	if err != nil {
		t.Fatalf("ReadMessage failed: %v", err)
	}
	_, ok := msg.(OkMessageType)
	if !ok {
		t.Fatalf("got %T, want OkMessageType", msg)
	}
}

func TestReadMessageTargetPopulations(t *testing.T) {
	data := []byte{
		0x54,
		0x00, 0x00, 0x00, 0x2c,
		0x00, 0x00, 0x30, 0x39,
		0x00, 0x00, 0x00, 0x02,
		0x00, 0x00, 0x00, 0x03,
		0x64, 0x6f, 0x67,
		0x00, 0x00, 0x00, 0x01,
		0x00, 0x00, 0x00, 0x03,
		0x00, 0x00, 0x00, 0x03,
		0x72, 0x61, 0x74,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x0a,
		0x80,
	}

	msg, err := ReadMessage(bytes.NewReader(data))
	if err != nil {
		t.Fatalf("ReadMessage failed: %v", err)
	}
	tp, ok := msg.(TargetPopulationsMessage)
	if !ok {
		t.Fatalf("got %T, want TargetPopulationsMessage", msg)
	}
	if tp.Site != 12345 || len(tp.Populations) != 2 {
		t.Fatalf("got %#v", tp)
	}
}

func TestReadMessagePolicyResult(t *testing.T) {
	data := []byte{0x57, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x7b, 0x24}

	msg, err := ReadMessage(bytes.NewReader(data))
	if err != nil {
		t.Fatalf("ReadMessage failed: %v", err)
	}
	pr, ok := msg.(PolicyResultMessage)
	if !ok {
		t.Fatalf("got %T, want PolicyResultMessage", msg)
	}
	if pr.Policy != 123 {
		t.Fatalf("got %#v", pr)
	}
}

func TestReadMessageSiteVisit(t *testing.T) {
	data := []byte{
		0x58,
		0x00, 0x00, 0x00, 0x24,
		0x00, 0x00, 0x30, 0x39,
		0x00, 0x00, 0x00, 0x02,
		0x00, 0x00, 0x00, 0x03,
		0x64, 0x6f, 0x67,
		0x00, 0x00, 0x00, 0x01,
		0x00, 0x00, 0x00, 0x03,
		0x72, 0x61, 0x74,
		0x00, 0x00, 0x00, 0x05,
		0x8c,
	}

	msg, err := ReadMessage(bytes.NewReader(data))
	if err != nil {
		t.Fatalf("ReadMessage failed: %v", err)
	}
	sv, ok := msg.(SiteVisitMessage)
	if !ok {
		t.Fatalf("got %T, want SiteVisitMessage", msg)
	}
	if sv.Site != 12345 || len(sv.Population) != 2 {
		t.Fatalf("got %#v", sv)
	}
}

func TestReadMessageErrors(t *testing.T) {
	tests := []struct {
		name string
		data []byte
	}{
		{name: "bad hello protocol", data: []byte{0x50, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0b, 0x70, 0x65, 0x73, 0x74, 0x63, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x78, 0x00, 0x00, 0x00, 0x01, 0xce}},
		{name: "bad length", data: []byte{0x52, 0x00, 0x00, 0x00, 0x07, 0xa8}},
		{name: "invalid type", data: []byte{0x00, 0x00, 0x00, 0x00, 0x06, 0x00}},
	}

	for _, tc := range tests {
		t.Run(tc.name, func(t *testing.T) {
			_, err := ReadMessage(bytes.NewReader(tc.data))
			if err == nil {
				t.Fatal("expected error, got nil")
			}
		})
	}
}

func TestWriteMessageError(t *testing.T) {
	// Error message with "bad" string
	// Expected hex: 51 00 00 00 0d 00 00 00 03 62 61 64 78
	buf := &bytes.Buffer{}
	msg := ErrorMessage{Message: "bad"}
	err := WriteMessage(buf, msg)
	if err != nil {
		t.Fatalf("WriteMessage failed: %v", err)
	}

	expected := []byte{0x51, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x03, 0x62, 0x61, 0x64, 0x78}
	if !bytes.Equal(buf.Bytes(), expected) {
		t.Errorf("got %x, want %x", buf.Bytes(), expected)
	}
}

func TestWriteMessageDialAuthority(t *testing.T) {
	// DialAuthority with site 12345
	// Expected hex: 53 00 00 00 0a 00 00 30 39 3a
	buf := &bytes.Buffer{}
	msg := DialAuthorityMessage{Site: 12345}
	err := WriteMessage(buf, msg)
	if err != nil {
		t.Fatalf("WriteMessage failed: %v", err)
	}

	expected := []byte{0x53, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x30, 0x39, 0x3a}
	if !bytes.Equal(buf.Bytes(), expected) {
		t.Errorf("got %x, want %x", buf.Bytes(), expected)
	}
}

func TestWriteMessageCreatePolicy(t *testing.T) {
	// CreatePolicy with species "dog" and conserve action (0xa0)
	// Expected hex: 55 00 00 00 0e 00 00 00 03 64 6f 67 a0 c0
	buf := &bytes.Buffer{}
	msg := CreatePolicyMessage{Species: "dog", Action: PolicyConserve}
	err := WriteMessage(buf, msg)
	if err != nil {
		t.Fatalf("WriteMessage failed: %v", err)
	}

	expected := []byte{0x55, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x03, 0x64, 0x6f, 0x67, 0xa0, 0xc0}
	if !bytes.Equal(buf.Bytes(), expected) {
		t.Errorf("got %x, want %x", buf.Bytes(), expected)
	}
}

func TestWriteMessageDeletePolicy(t *testing.T) {
	// DeletePolicy with policy 123 (0x7b)
	// Expected hex: 56 00 00 00 0a 00 00 00 7b 25
	buf := &bytes.Buffer{}
	msg := DeletePolicyMessage{Policy: 123}
	err := WriteMessage(buf, msg)
	if err != nil {
		t.Fatalf("WriteMessage failed: %v", err)
	}

	expected := []byte{0x56, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x7b, 0x25}
	if !bytes.Equal(buf.Bytes(), expected) {
		t.Errorf("got %x, want %x", buf.Bytes(), expected)
	}
}

func TestWriteMessageHello(t *testing.T) {
	// Test with HelloMessage constant
	buf := &bytes.Buffer{}
	err := WriteMessage(buf, HelloMessage)
	if err != nil {
		t.Fatalf("WriteMessage failed: %v", err)
	}

	if !bytes.Equal(buf.Bytes(), []byte(HelloMessage)) {
		t.Errorf("got %x, want %x", buf.Bytes(), HelloMessage)
	}
}

func TestWriteMessageOk(t *testing.T) {
	// Test with OkMessage constant
	buf := &bytes.Buffer{}
	err := WriteMessage(buf, OkMessage)
	if err != nil {
		t.Fatalf("WriteMessage failed: %v", err)
	}

	if !bytes.Equal(buf.Bytes(), []byte(OkMessage)) {
		t.Errorf("got %x, want %x", buf.Bytes(), OkMessage)
	}
}
