package isl

import "testing"

func TestEncrypt(t *testing.T) {
	tests := []struct {
		cipherspec Cipherspec
		in         []byte
		want       []byte
	}{
		{
			cipherspec: MustParseCipherspec([]byte{0x2, 0x1, 0x1, 0x0}),
			in:         []byte{'h', 'e', 'l', 'l', 'o'},
			want:       []byte{0x96, 0x26, 0xb6, 0xb6, 0x76},
		},
		{
			cipherspec: MustParseCipherspec([]byte{0x05, 0x05, 0x00}),
			in:         []byte{'h', 'e', 'l', 'l', 'o'},
			want:       []byte{0x68, 0x67, 0x70, 0x72, 0x77},
		},
	}
	for _, test := range tests {
		got := make([]byte, len(test.in))
		copy(got, test.in)
		encrypt(&test.cipherspec, got, 0)
		if string(got) != string(test.want) {
			t.Errorf("Encrypt(%q) = %q, want %q", string(test.in), string(got), string(test.want))
		}
	}
}

func TestDecrypt(t *testing.T) {
	tests := []struct {
		cipherspec Cipherspec
		in         []byte
		want       []byte
	}{
		{
			cipherspec: MustParseCipherspec([]byte{0x2, 0x1, 0x1, 0x0}),
			in:         []byte{0x96, 0x26, 0xb6, 0xb6, 0x76},
			want:       []byte{'h', 'e', 'l', 'l', 'o'},
		},
		{
			cipherspec: MustParseCipherspec([]byte{0x05, 0x05, 0x00}),
			in:         []byte{0x68, 0x67, 0x70, 0x72, 0x77},
			want:       []byte{'h', 'e', 'l', 'l', 'o'},
		},
	}
	for _, test := range tests {
		got := make([]byte, len(test.in))
		copy(got, test.in)
		decrypt(&test.cipherspec, got, 0)
		if string(got) != string(test.want) {
			t.Errorf("Decrypt(%q) = %q, want %q", string(test.in), string(got), string(test.want))
		}
	}
}

func TestEncryptDecrypt(t *testing.T) {
	tests := []struct {
		cipherspec Cipherspec
		in         []byte
		want       []byte
	}{
		{
			cipherspec: MustParseCipherspec([]byte{0x2, 0x1, 0x1, 0x0}),
			in:         []byte("hello"),
		},
		{
			cipherspec: MustParseCipherspec([]byte{0x05, 0x05, 0x00}),
			in:         []byte("this is a message"),
		},
	}
	for _, test := range tests {
		got := make([]byte, len(test.in))
		copy(got, test.in)
		encrypt(&test.cipherspec, got, 0)
		decrypt(&test.cipherspec, got, 0)
		if string(got) != string(test.in) {
			t.Errorf("Encrypt/Decrypt does not match in = %q, out = %q", string(test.in), string(got))
		}
	}
}

func TestEncryptDecryptWithPos(t *testing.T) {
	tests := []struct {
		name       string
		cipherspec Cipherspec
		in         []byte
		encrypted  []byte
		pos        int64
	}{
		{
			name:       "xor(123),addpos,reversebits with pos 0",
			cipherspec: MustParseCipherspec([]byte{0x02, 0x7b, 0x05, 0x01, 0x00}),
			in:         []byte("4x dog,5x car\n"),
			encrypted:  []byte{0xf2, 0x20, 0xba, 0x44, 0x18, 0x84, 0xba, 0xaa, 0xd0, 0x26, 0x44, 0xa4, 0xa8, 0x7e},
			pos:        0,
		},
		{
			name:       "xor(123),addpos,reversebits with pos 14",
			cipherspec: MustParseCipherspec([]byte{0x02, 0x7b, 0x05, 0x01, 0x00}),
			in:         []byte("3x rat,2x cat\n"),
			encrypted:  []byte{0x6a, 0x48, 0xd6, 0x58, 0x34, 0x44, 0xd6, 0x7a, 0x98, 0x4e, 0x0c, 0xcc, 0x94, 0x31},
			pos:        14,
		},
	}

	for _, test := range tests {
		t.Run(test.name+" encrypt", func(t *testing.T) {
			got := make([]byte, len(test.in))
			copy(got, test.in)
			encrypt(&test.cipherspec, got, test.pos)
			for i := range got {
				if got[i] != test.encrypted[i] {
					t.Errorf("Encrypt byte %d: got 0x%02x, want 0x%02x", i, got[i], test.encrypted[i])
				}
			}
		})

		t.Run(test.name+" decrypt", func(t *testing.T) {
			got := make([]byte, len(test.encrypted))
			copy(got, test.encrypted)
			decrypt(&test.cipherspec, got, test.pos)
			if string(got) != string(test.in) {
				t.Errorf("Decrypt: got %q, want %q", string(got), string(test.in))
			}
		})

		t.Run(test.name+" roundtrip", func(t *testing.T) {
			got := make([]byte, len(test.in))
			copy(got, test.in)
			encrypt(&test.cipherspec, got, test.pos)
			decrypt(&test.cipherspec, got, test.pos)
			if string(got) != string(test.in) {
				t.Errorf("Roundtrip: got %q, want %q", string(got), string(test.in))
			}
		})
	}
}
