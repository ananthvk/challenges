package isl

import "math/bits"

// encrypt encodes the buffer in place using the given cipherspec. cipherspec must not be nil, pos is the position of the start of the buffer
func encrypt(cipherspec *Cipherspec, buffer []byte, pos int64) {
	for i := range buffer {
		buffer[i] = encryptByte(cipherspec, buffer[i], pos+int64(i))
	}
}

// decrypt decodes the buffer in place using the given cipherspec. cipherspec must not be nil, pos is the position of the start of the buffer
func decrypt(cipherspec *Cipherspec, buffer []byte, pos int64) {
	for i := range buffer {
		buffer[i] = decryptByte(cipherspec, buffer[i], pos+int64(i))
	}
}

// encryptByte encodes a single byte using the given cipherspec, pos is the position of the byte in the stream, and starts from 0
func encryptByte(cipherspec *Cipherspec, b byte, pos int64) byte {
	encrypted := b
	for _, op := range cipherspec.ops {
		switch op.opcode {
		case opReverseBits:
			encrypted = bits.Reverse8(encrypted)
		case opXorN:
			encrypted = encrypted ^ op.operand
		case opXorPos:
			encrypted = encrypted ^ byte(pos)
		case opAddN:
			encrypted = encrypted + op.operand
		case opAddPos:
			encrypted = encrypted + byte(pos)
		default:
			panic("logic_error: invalid byte in cipherspec")
		}
	}
	return encrypted
}

// decryptByte dencodes a single byte using the given cipherspec, pos is the position of the byte in the stream, and starts from 0
func decryptByte(cipherspec *Cipherspec, b byte, pos int64) byte {
	decrypted := b
	// Apply the operations in reverse
	for i := len(cipherspec.ops) - 1; i >= 0; i-- {
		op := cipherspec.ops[i]
		switch op.opcode {
		case opReverseBits:
			decrypted = bits.Reverse8(decrypted)
		case opXorN:
			decrypted = decrypted ^ op.operand
		case opXorPos:
			decrypted = decrypted ^ byte(pos)
		case opAddN:
			decrypted = decrypted - op.operand
		case opAddPos:
			decrypted = decrypted - byte(pos)
		default:
			panic("logic_error: invalid byte in cipherspec")
		}
	}
	return decrypted
}
