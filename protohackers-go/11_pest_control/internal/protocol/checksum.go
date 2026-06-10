package protocol

import (
	"errors"
	"io"
)

type ChecksumWriter struct {
	w   io.Writer
	sum byte
}

func NewChecksumWriter(w io.Writer) *ChecksumWriter {
	return &ChecksumWriter{
		w:   w,
		sum: 0,
	}
}

func (c *ChecksumWriter) Write(p []byte) (int, error) {
	for i := range p {
		c.sum += p[i]
	}
	return c.w.Write(p)
}

// WriteSum writes the checksum to the stream
func (c *ChecksumWriter) WriteSum() error {
	var p [1]byte
	p[0] = c.Sum()
	_, err := c.w.Write(p[:])
	return err
}

func (c *ChecksumWriter) Sum() byte {
	return 0xFF - c.sum + 1
}

func (c *ChecksumWriter) Reset() {
	c.sum = 0
}

type ChecksumReader struct {
	r   io.Reader
	sum byte
}

func NewChecksumReader(r io.Reader) *ChecksumReader {
	return &ChecksumReader{
		r:   r,
		sum: 0,
	}
}

func (c *ChecksumReader) Read(p []byte) (int, error) {
	n, err := c.r.Read(p)
	if n > 0 {
		for i := range n {
			c.sum += p[i]
		}
	}
	return n, err
}

func (c *ChecksumReader) Sum() byte {
	return 0xFF - c.sum + 1
}

// VerifySum reads the next byte from the stream and returns true
// if the checksum is valid
func (c *ChecksumReader) VerifySum() error {
	var sum [1]byte
	if _, err := io.ReadFull(c.r, sum[:]); err != nil {
		return err
	}
	if (c.sum + sum[0]) == 0 {
		return nil
	}
	return errors.New("checksum mismatch")
}

func (c *ChecksumReader) Reset() {
	c.sum = 0
}
