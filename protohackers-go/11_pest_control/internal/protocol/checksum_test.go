package protocol

import (
	"bytes"
	"testing"
)

func TestChecksumReader(t *testing.T) {
	payload := []byte{
		0x50,
		0x00, 0x00, 0x00, 0x19,
		0x00, 0x00, 0x00, 0x0b,
		'p', 'e', 's', 't', 'c', 'o', 'n', 't', 'r', 'o', 'l',
		0x00, 0x00, 0x00, 0x01,
	}

	r := NewChecksumReader(bytes.NewReader(payload))
	buf := make([]byte, len(payload))
	n, err := r.Read(buf)
	if err != nil && n != len(payload) {
		t.Fatalf("Read error: %v", err)
	}
	if n != len(payload) {
		t.Fatalf("expected read %d bytes, got %d", len(payload), n)
	}
	if got := r.Sum(); got != 0xCE {
		t.Fatalf("unexpected checksum: got 0x%02x want 0xCE", got)
	}
}

func TestChecksumWriter(t *testing.T) {
	data := []byte{
		0x50,
		0x00, 0x00, 0x00, 0x19,
		0x00, 0x00, 0x00, 0x0b,
		'p', 'e', 's', 't', 'c', 'o', 'n', 't', 'r', 'o', 'l',
		0x00, 0x00, 0x00, 0x01,
	}

	var buf bytes.Buffer
	w := NewChecksumWriter(&buf)
	n, err := w.Write(data)
	if err != nil {
		t.Fatalf("Write error: %v", err)
	}
	if n != len(data) {
		t.Fatalf("expected wrote %d bytes, wrote %d", len(data), n)
	}
	if got := w.Sum(); got != 0xCE {
		t.Fatalf("unexpected checksum: got 0x%02x want 0xCE", got)
	}
}

func TestWriteSum(t *testing.T) {
	data := []byte{
		0x50,
		0x00, 0x00, 0x00, 0x19,
		0x00, 0x00, 0x00, 0x0b,
		'p', 'e', 's', 't', 'c', 'o', 'n', 't', 'r', 'o', 'l',
		0x00, 0x00, 0x00, 0x01,
	}

	var buf bytes.Buffer
	w := NewChecksumWriter(&buf)
	_, err := w.Write(data)
	if err != nil {
		t.Fatalf("Write error: %v", err)
	}
	err = w.WriteSum()
	if err != nil {
		t.Fatalf("WriteSum error: %v", err)
	}
	if buf.Len() != len(data)+1 {
		t.Fatalf("expected buffer length %d, got %d", len(data)+1, buf.Len())
	}
	if buf.Bytes()[len(data)] != 0xCE {
		t.Fatalf("unexpected checksum written: got 0x%02x want 0xCE", buf.Bytes()[len(data)])
	}
}

func TestVerifySum(t *testing.T) {
	data := []byte{
		0x50,
		0x00, 0x00, 0x00, 0x19,
		0x00, 0x00, 0x00, 0x0b,
		'p', 'e', 's', 't', 'c', 'o', 'n', 't', 'r', 'o', 'l',
		0x00, 0x00, 0x00, 0x01,
		0xCE, // valid checksum
	}

	r := NewChecksumReader(bytes.NewReader(data))
	buf := make([]byte, len(data)-1)
	_, err := r.Read(buf)
	if err != nil {
		t.Fatalf("Read error: %v", err)
	}
	err = r.VerifySum()
	if err != nil {
		t.Fatalf("VerifySum error: %v", err)
	}
}

func TestVerifySumInvalid(t *testing.T) {
	data := []byte{
		0x50,
		0x00, 0x00, 0x00, 0x19,
		0x00, 0x00, 0x00, 0x0b,
		'p', 'e', 's', 't', 'c', 'o', 'n', 't', 'r', 'o', 'l',
		0x00, 0x00, 0x00, 0x01,
		0xFF, // invalid checksum
	}

	r := NewChecksumReader(bytes.NewReader(data))
	buf := make([]byte, len(data)-1)
	_, err := r.Read(buf)
	if err != nil {
		t.Fatalf("Read error: %v", err)
	}
	err = r.VerifySum()
	if err == nil {
		t.Fatalf("expected error, got nil")
	}
}
