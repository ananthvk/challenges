package serialization

import (
	"encoding/binary"
	"errors"
	"fmt"
	"io"
	"reflect"
)

const maxArrayLength = 8192
const maxStringLength = 64 * 1024

func readUint32(r io.Reader) (uint32, error) {
	var value uint32
	if err := binary.Read(r, binary.BigEndian, &value); err != nil {
		return 0, err
	}
	return value, nil
}

func writeUint32(w io.Writer, value uint32) error {
	if err := binary.Write(w, binary.BigEndian, value); err != nil {
		return err
	}
	return nil
}

func readString(r io.Reader) (string, error) {
	// Read the length of the string
	var length uint32
	if err := binary.Read(r, binary.BigEndian, &length); err != nil {
		return "", err
	}

	if length > maxStringLength {
		return "", errors.New("string too large")
	}

	// Read the string bytes
	buffer := make([]byte, length)
	if _, err := io.ReadFull(r, buffer[:]); err != nil {
		return "", err
	}
	return string(buffer), nil
}

func writeString(w io.Writer, value string) error {
	var stringLength uint32 = uint32(len(value))
	if err := binary.Write(w, binary.BigEndian, stringLength); err != nil {
		return err
	}
	if _, err := w.Write([]byte(value)); err != nil {
		return err
	}
	return nil
}

func writeArray(w io.Writer, value any) error {
	rv := reflect.ValueOf(value)

	if rv.Kind() != reflect.Slice && rv.Kind() != reflect.Array {
		return fmt.Errorf("not array/slice")
	}

	if err := writeUint32(w, uint32(rv.Len())); err != nil {
		return err
	}

	for i := 0; i < rv.Len(); i++ {
		if err := WriteValue(w, rv.Index(i).Interface()); err != nil {
			return err
		}
	}

	return nil
}

// Read array reads from the stream, and stores the output in out
// out must be a pointer, otherwise it panics
func readArray(r io.Reader, out any) error {
	rv := reflect.ValueOf(out)

	if rv.Kind() != reflect.Pointer {
		return errors.New("out must be pointer")
	}

	slice := rv.Elem()
	if slice.Kind() != reflect.Slice {
		return errors.New("out must be pointer to slice")
	}

	size, err := readUint32(r)
	if err != nil {
		return err
	}

	if size > maxArrayLength {
		return errors.New("array too large")
	}

	elemType := slice.Type().Elem()
	result := reflect.MakeSlice(slice.Type(), int(size), int(size))

	for i := 0; i < int(size); i++ {
		elem := reflect.New(elemType).Interface()

		if err := ReadValue(r, elem); err != nil {
			return err
		}

		result.Index(i).Set(reflect.ValueOf(elem).Elem())
	}

	slice.Set(result)
	return nil
}

func writeStruct(w io.Writer, value any) error {
	rv := reflect.ValueOf(value)

	if rv.Kind() == reflect.Pointer {
		rv = rv.Elem()
	}

	if rv.Kind() != reflect.Struct {
		return fmt.Errorf("WriteStruct expects struct, got %v", rv.Kind())
	}

	rt := rv.Type()

	for i := 0; i < rv.NumField(); i++ {
		field := rv.Field(i)

		if !rt.Field(i).IsExported() {
			continue
		}

		if err := WriteValue(w, field.Interface()); err != nil {
			return err
		}
	}

	return nil
}

func readStruct(r io.Reader, out any) error {
	rv := reflect.ValueOf(out)

	if rv.Kind() != reflect.Pointer {
		return errors.New("out must be pointer")
	}

	rv = rv.Elem()

	if rv.Kind() != reflect.Struct {
		return errors.New("out must be pointer to struct")
	}

	rt := rv.Type()

	for i := 0; i < rv.NumField(); i++ {
		field := rv.Field(i)

		if !rt.Field(i).IsExported() {
			continue
		}

		if err := ReadValue(r, field.Addr().Interface()); err != nil {
			return err
		}
	}

	return nil
}

func WriteValue(w io.Writer, v any) error {
	rv := reflect.ValueOf(v)

	switch rv.Kind() {
	case reflect.Slice, reflect.Array:
		return writeArray(w, v)
	case reflect.Uint8:
		var p [1]uint8
		p[0] = v.(uint8)
		_, err := w.Write(p[:])
		return err
	case reflect.Uint32:
		return writeUint32(w, uint32(rv.Uint()))
	case reflect.String:
		return writeString(w, rv.String())
	case reflect.Struct:
		return writeStruct(w, v)
	default:
		return fmt.Errorf("unsupported type %v", rv.Kind())
	}
}

func ReadValue(r io.Reader, out any) error {
	rv := reflect.ValueOf(out)

	if rv.Kind() != reflect.Pointer {
		return errors.New("out must be pointer")
	}

	v := rv.Elem()

	switch v.Kind() {
	case reflect.Slice:
		return readArray(r, out)
	case reflect.Uint32:
		n, err := readUint32(r)
		if err != nil {
			return err
		}
		v.SetUint(uint64(n))
		return nil

	case reflect.String:
		s, err := readString(r)
		if err != nil {
			return err
		}
		v.SetString(s)
		return nil

	case reflect.Struct:
		return readStruct(r, out)

	default:
		return fmt.Errorf("unsupported type %v", v.Kind())
	}
}
