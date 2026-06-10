package serialization

import (
	"bytes"
	"reflect"
	"testing"
)

func TestUint32ReadWrite(t *testing.T) {
	tests := []struct {
		name string
		val  uint32
	}{
		{"zero", 0},
		{"max", 0xFFFFFFFF},
		{"42", 42},
	}

	for _, tc := range tests {
		t.Run(tc.name, func(t *testing.T) {
			var buf bytes.Buffer
			if err := writeUint32(&buf, tc.val); err != nil {
				t.Fatalf("WriteUint32 error: %v", err)
			}
			got, err := readUint32(&buf)
			if err != nil {
				t.Fatalf("ReadUint32 error: %v", err)
			}
			if got != tc.val {
				t.Fatalf("got %v want %v", got, tc.val)
			}
		})
	}
}

func TestStringReadWrite(t *testing.T) {
	tests := []struct {
		name  string
		input string
	}{
		{"empty", ""},
		{"simple", "hello world"},
		{"unicode", "こんにちは世界"},
	}

	for _, tc := range tests {
		t.Run(tc.name, func(t *testing.T) {
			var buf bytes.Buffer
			if err := writeString(&buf, tc.input); err != nil {
				t.Fatalf("WriteString error: %v", err)
			}
			got, err := readString(&buf)
			if err != nil {
				t.Fatalf("ReadString error: %v", err)
			}
			if got != tc.input {
				t.Fatalf("got %q want %q", got, tc.input)
			}
		})
	}
}

func TestReadStringInsufficientData(t *testing.T) {
	// Write a length prefix larger than available bytes
	var buf bytes.Buffer
	// write length = 10 but only provide 3 bytes
	if err := writeUint32(&buf, 10); err != nil {
		t.Fatalf("WriteUint32 error: %v", err)
	}
	buf.Write([]byte{1, 2, 3})

	_, err := readString(&buf)
	if err == nil {
		t.Fatalf("expected error reading insufficient data")
	}
}

func TestUint32Fixed(t *testing.T) {
	tests := []struct {
		name  string
		val   uint32
		bytes []byte
	}{
		{"32", 32, []byte{0x00, 0x00, 0x00, 0x20}},
		{"4677", 4677, []byte{0x00, 0x00, 0x12, 0x45}},
		{"2796139879", 2796139879, []byte{0xA6, 0xA9, 0xB5, 0x67}},
	}

	for _, tc := range tests {
		t.Run(tc.name, func(t *testing.T) {
			var buf bytes.Buffer
			if err := writeUint32(&buf, tc.val); err != nil {
				t.Fatalf("WriteUint32 error: %v", err)
			}

			if !reflect.DeepEqual(buf.Bytes(), tc.bytes) {
				t.Fatalf("serialized bytes mismatch: got % X want % X", buf.Bytes(), tc.bytes)
			}

			got, err := readUint32(bytes.NewReader(tc.bytes))
			if err != nil {
				t.Fatalf("ReadUint32 error: %v", err)
			}
			if got != tc.val {
				t.Fatalf("deserialized value mismatch: got %v want %v", got, tc.val)
			}
		})
	}
}

func TestStringFixed(t *testing.T) {
	tests := []struct {
		name  string
		val   string
		bytes []byte
	}{
		{"empty", "", []byte{0x00, 0x00, 0x00, 0x00}},
		{"foo", "foo", []byte{0x00, 0x00, 0x00, 0x03, 0x66, 0x6F, 0x6F}},
		{"Elbereth", "Elbereth", []byte{0x00, 0x00, 0x00, 0x08, 0x45, 0x6C, 0x62, 0x65, 0x72, 0x65, 0x74, 0x68}},
	}

	for _, tc := range tests {
		t.Run(tc.name, func(t *testing.T) {
			var buf bytes.Buffer
			if err := writeString(&buf, tc.val); err != nil {
				t.Fatalf("WriteString error: %v", err)
			}

			if !reflect.DeepEqual(buf.Bytes(), tc.bytes) {
				t.Fatalf("serialized bytes mismatch: got % X want % X", buf.Bytes(), tc.bytes)
			}

			got, err := readString(bytes.NewReader(tc.bytes))
			if err != nil {
				t.Fatalf("ReadString error: %v", err)
			}
			if got != tc.val {
				t.Fatalf("deserialized value mismatch: got %q want %q", got, tc.val)
			}
		})
	}
}

func TestArrays(t *testing.T) {
	type person struct {
		unexported  uint32
		Name        string
		Age         uint32
		unexported2 string
	}

	values := []person{{Name: "alice", Age: 21}, {Name: "bob", Age: 22}, {Name: "charlie", Age: 23}}

	var buf bytes.Buffer
	if err := WriteValue(&buf, values); err != nil {
		t.Fatalf("WriteArray error: %v", err)
	}

	var got []person
	if err := ReadValue(&buf, &got); err != nil {
		t.Fatalf("ReadArray error: %v", err)
	}

	if !reflect.DeepEqual(got, values) {
		t.Fatalf("array mismatch: got %#v want %#v", got, values)
	}
}

func TestArraysFixed(t *testing.T) {
	type sighting struct {
		Species string
		Count   uint32
	}

	values := []sighting{
		{Species: "rat", Count: 10},
		{Species: "dog", Count: 15},
	}

	expected := []byte{
		0x00, 0x00, 0x00, 0x02,
		0x00, 0x00, 0x00, 0x03, 0x72, 0x61, 0x74,
		0x00, 0x00, 0x00, 0x0a,
		0x00, 0x00, 0x00, 0x03, 0x64, 0x6f, 0x67,
		0x00, 0x00, 0x00, 0x0f,
	}

	t.Run("serialize fixed bytes", func(t *testing.T) {
		var buf bytes.Buffer
		if err := WriteValue(&buf, values); err != nil {
			t.Fatalf("WriteArray error: %v", err)
		}

		if !reflect.DeepEqual(buf.Bytes(), expected) {
			t.Fatalf("serialized bytes mismatch: got % X want % X", buf.Bytes(), expected)
		}
	})

	t.Run("deserialize fixed bytes", func(t *testing.T) {
		var got []sighting
		if err := ReadValue(bytes.NewReader(expected), &got); err != nil {
			t.Fatalf("ReadArray error: %v", err)
		}

		if !reflect.DeepEqual(got, values) {
			t.Fatalf("array mismatch: got %#v want %#v", got, values)
		}
	})
}

func TestSerializationTableDriven(t *testing.T) {
	type mixed struct {
		unexported uint32
		Name       string
		Count      uint32
		hidden     string
	}

	s1 := mixed{Name: "alpha", Count: 7}
	s2 := mixed{Name: "beta", Count: 13}

	tests := []struct {
		name string
		val  any
		want any
	}{
		{"uint32_zero", uint32(0), uint32(0)},
		{"uint32_max", uint32(0xFFFFFFFF), uint32(0xFFFFFFFF)},
		{"string_simple", "hello", "hello"},
		{"struct_single", mixed{Name: "solo", Count: 1}, mixed{Name: "solo", Count: 1}},
		{"struct_multiple", []mixed{s1, s2, {Name: "gamma", Count: 21}}, []mixed{s1, s2, {Name: "gamma", Count: 21}}},
		{"array_uint32", []uint32{1, 2, 3, 4}, []uint32{1, 2, 3, 4}},
		{"array_string", []string{"a", "bb", "ccc"}, []string{"a", "bb", "ccc"}},
		{"array_struct", []mixed{{Name: "x", Count: 9}, {Name: "y", Count: 10}}, []mixed{{Name: "x", Count: 9}, {Name: "y", Count: 10}}},
	}

	for _, tc := range tests {
		t.Run(tc.name, func(t *testing.T) {
			var buf bytes.Buffer
			if err := WriteValue(&buf, tc.val); err != nil {
				t.Fatalf("WriteValue error: %v", err)
			}

			// prepare a destination of the correct type
			var dst any
			switch want := tc.want.(type) {
			case uint32:
				dst = new(uint32)
			case string:
				dst = new(string)
			case []uint32:
				dst = new([]uint32)
			case []string:
				dst = new([]string)
			case mixed:
				dst = new(mixed)
			case []mixed:
				dst = new([]mixed)
			default:
				t.Fatalf("unsupported type %T", want)
			}

			if err := ReadValue(&buf, dst); err != nil {
				t.Fatalf("ReadValue error: %v", err)
			}

			// dereference pointer for comparison
			var got any
			switch v := dst.(type) {
			case *uint32:
				got = *v
			case *string:
				got = *v
			case *[]uint32:
				got = *v
			case *[]string:
				got = *v
			case *mixed:
				got = *v
			case *[]mixed:
				got = *v
			}

			if !reflect.DeepEqual(got, tc.want) {
				t.Fatalf("mismatch: got %#v want %#v", got, tc.want)
			}
		})
	}
}
