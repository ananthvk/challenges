package isl

import (
	"errors"
	"fmt"
	"net"
)

const (
	opEnd         = 0x00
	opReverseBits = 0x01
	opXorN        = 0x02
	opXorPos      = 0x03
	opAddN        = 0x04
	opAddPos      = 0x05
)

type operation struct {
	opcode  byte
	operand byte
}

type Cipherspec struct {
	ops []operation
}

func ParseCipherspec(b []byte) (Cipherspec, error) {
	if len(b) == 0 {
		return Cipherspec{}, errors.New("empty cipherspec")
	}
	if b[len(b)-1] != 0 {
		return Cipherspec{}, errors.New("last byte of cipherspec should be 0x0")
	}
	var cipherspec Cipherspec
	for idx := 0; idx < len(b); idx++ {
		switch b[idx] {
		case opEnd:
			if idx != (len(b) - 1) {
				panic("encountered a 0x0 byte before the end of the cipherspec")
			}
		case opReverseBits:
			cipherspec.ops = append(cipherspec.ops, operation{opcode: opReverseBits})
		case opXorN:
			idx++
			if idx >= (len(b) - 1) {
				return Cipherspec{}, errors.New("insufficient bytes for opcode's operand")
			}
			operand := b[idx]
			cipherspec.ops = append(cipherspec.ops, operation{opcode: opXorN, operand: operand})
		case opXorPos:
			cipherspec.ops = append(cipherspec.ops, operation{opcode: opXorPos})
		case opAddN:
			idx++
			// Check if it's greater than or equal to len(b) - 1 since the last byte should be 0x0
			if idx >= (len(b) - 1) {
				return Cipherspec{}, errors.New("insufficient bytes for opcode's operand")
			}
			operand := b[idx]
			cipherspec.ops = append(cipherspec.ops, operation{opcode: opAddN, operand: operand})
		case opAddPos:
			cipherspec.ops = append(cipherspec.ops, operation{opcode: opAddPos})
		default:
			return Cipherspec{}, fmt.Errorf("invalid byte %x at position %d", b[idx], idx)
		}
	}
	return cipherspec, nil
}

func MustParseCipherspec(b []byte) Cipherspec {
	cipherspec, err := ParseCipherspec(b)
	if err != nil {
		panic("parse cipherspec failed")
	}
	return cipherspec
}

// IsCipherspecNoOp returns true if the cipherspec is a no-op, i.e. it leaves every byte of the input unchanged
// This function executes encryptByte for all 256 bytes
func IsCipherspecNoOp(cipherspec *Cipherspec) bool {
	xorPosCount := 0
	for _, op := range cipherspec.ops {
		if op.opcode == opAddPos {
			return false
		}
		if op.opcode == opXorPos {
			xorPosCount++
		}
	}
	// If there are even number of xorPos, they get cancelled out, so we still need to perform all the checks
	// If there are odd number of xorPos, it can never be a no-op
	if xorPosCount%2 != 0 {
		return false
	}
	for i := range 256 {
		// Atleast one byte has been changed
		if encryptByte(cipherspec, byte(i), 0) != byte(i) {
			return false
		}
	}
	return true
}

// readCipherSpecBuffer reads the data from the connection byte by byte until a 0x0 byte is encountered
func readCipherSpecBuffer(conn net.Conn) ([]byte, error) {
	buf := make([]byte, 0, 80) // max cipher spec length ≤ 80 bytes
	var one [1]byte

	for {
		n, err := conn.Read(one[:])
		if err != nil {
			return nil, err
		}
		if n == 0 {
			continue
		}
		b := one[0]
		buf = append(buf, b)
		if b == 0x00 {
			return buf, nil
		}
		if len(buf) > 80 {
			return nil, errors.New("cipherspec too long")
		}
	}
}

// ReadCipherSpec reads the cipherspec from the connection, this function should be called at the start of a connection
func ReadCipherSpec(conn net.Conn) (*Cipherspec, error) {
	cipherspecBuffer, err := readCipherSpecBuffer(conn)
	if err != nil {
		return nil, err
	}
	cipherspec, err := ParseCipherspec(cipherspecBuffer)
	if err != nil {
		return nil, err
	}
	if IsCipherspecNoOp(&cipherspec) {
		return nil, errors.New("no-op cipher")
	}
	return &cipherspec, nil
}
