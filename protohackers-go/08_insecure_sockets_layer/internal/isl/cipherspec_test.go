package isl

import (
	"testing"
)

func TestParseCipherspec(t *testing.T) {
	tests := []struct {
		name    string
		input   []byte
		want    Cipherspec
		wantErr bool
	}{
		{
			name:    "empty input",
			input:   []byte{},
			want:    Cipherspec{},
			wantErr: true,
		},
		{
			name:    "missing end byte",
			input:   []byte{0x01},
			want:    Cipherspec{},
			wantErr: true,
		},
		{
			name:  "only end byte",
			input: []byte{0x00},
			want:  Cipherspec{ops: []operation{}},
		},
		{
			name:  "reverse bits operation",
			input: []byte{0x01, 0x00},
			want:  Cipherspec{ops: []operation{{opcode: opReverseBits}}},
		},
		{
			name:  "xor with value",
			input: []byte{0x02, 0x42, 0x00},
			want:  Cipherspec{ops: []operation{{opcode: opXorN, operand: 0x42}}},
		},
		{
			name:    "xor with value missing operand",
			input:   []byte{0x02, 0x00},
			want:    Cipherspec{},
			wantErr: true,
		},
		{
			name:    "xor with value no operand",
			input:   []byte{0x02},
			want:    Cipherspec{},
			wantErr: true,
		},
		{
			name:  "xor with position",
			input: []byte{0x03, 0x00},
			want:  Cipherspec{ops: []operation{{opcode: opXorPos}}},
		},
		{
			name:  "add with value",
			input: []byte{0x04, 0x10, 0x00},
			want:  Cipherspec{ops: []operation{{opcode: opAddN, operand: 0x10}}},
		},
		{
			name:    "add with value missing operand",
			input:   []byte{0x04, 0x00},
			want:    Cipherspec{},
			wantErr: true,
		},
		{
			name:    "add with value no operand",
			input:   []byte{0x04},
			want:    Cipherspec{},
			wantErr: true,
		},
		{
			name:  "add with position",
			input: []byte{0x05, 0x00},
			want:  Cipherspec{ops: []operation{{opcode: opAddPos}}},
		},
		{
			name:    "invalid opcode",
			input:   []byte{0xFF, 0x00},
			want:    Cipherspec{},
			wantErr: true,
		},
		{
			name:  "multiple operations",
			input: []byte{0x01, 0x02, 0x42, 0x03, 0x04, 0x10, 0x05, 0x00},
			want: Cipherspec{ops: []operation{
				{opcode: opReverseBits},
				{opcode: opXorN, operand: 0x42},
				{opcode: opXorPos},
				{opcode: opAddN, operand: 0x10},
				{opcode: opAddPos},
			}},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, err := ParseCipherspec(tt.input)
			if (err != nil) != tt.wantErr {
				t.Errorf("ParseCipherspec() error = %v, wantErr %v", err, tt.wantErr)
				return
			}
			if !tt.wantErr {
				if len(got.ops) != len(tt.want.ops) {
					t.Errorf("ParseCipherspec() got %d operations, want %d", len(got.ops), len(tt.want.ops))
					return
				}
				for i, op := range got.ops {
					if op.opcode != tt.want.ops[i].opcode || op.operand != tt.want.ops[i].operand {
						t.Errorf("ParseCipherspec() operation %d = {%x, %x}, want {%x, %x}",
							i, op.opcode, op.operand, tt.want.ops[i].opcode, tt.want.ops[i].operand)
					}
				}
			}
		})
	}
}

func TestIsCipherspecNoOp(t *testing.T) {
	tests := []struct {
		name  string
		input Cipherspec
		want  bool
	}{
		{
			name:  "empty cipherspec",
			input: MustParseCipherspec([]byte{0x0}),
			want:  true,
		},
		{
			name:  "xor(0)",
			input: MustParseCipherspec([]byte{0x2, 0x0, 0x0}),
			want:  true,
		},
		{
			name:  "xor(X), xor(X)",
			input: MustParseCipherspec([]byte{0x2, 0xab, 0x2, 0xab, 0x0}),
			want:  true,
		},
		{
			name:  "reversebits, reversebits",
			input: MustParseCipherspec([]byte{0x1, 0x1, 0x0}),
			want:  true,
		},
		{
			name:  "xor(A), xor(B), xor(C) where A|B=C",
			input: MustParseCipherspec([]byte{0x02, 0xa0, 0x02, 0x0b, 0x02, 0xab, 0x00}),
			want:  true,
		},
		{
			name:  "xor(5)",
			input: MustParseCipherspec([]byte{0x2, 0x5, 0x0}),
			want:  false,
		},
		{
			name:  "reversebits",
			input: MustParseCipherspec([]byte{0x1, 0x0}),
			want:  false,
		},
		{
			name:  "addpos",
			input: MustParseCipherspec([]byte{0x05, 0x0}),
			want:  false,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got := IsCipherspecNoOp(&tt.input)
			if got != tt.want {
				t.Errorf("isCipherspecNoOp() = %v, want %v", got, tt.want)
			}
		})
	}
}
