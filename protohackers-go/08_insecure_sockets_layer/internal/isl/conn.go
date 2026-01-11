package isl

import (
	"net"
	"time"
)

type ISLConn struct {
	conn       net.Conn // The underlying TCP connection
	readPos    int64    // The position of the read stream
	writePos   int64    // The position of the write stream
	cipherspec *Cipherspec
}

// Wraps the connection with ISL protocol, encoding and decoding all Reads/Writes
func WrapConn(conn net.Conn, cipherspec *Cipherspec) net.Conn {
	return &ISLConn{
		conn:       conn,
		cipherspec: cipherspec,
	}
}

// Note: Concurrent Read is prohibited
func (islConn *ISLConn) Read(b []byte) (int, error) {
	n, err := islConn.conn.Read(b)
	if err != nil {
		return n, err
	}

	// Decode the data before passing it to the application
	decrypt(islConn.cipherspec, b[:n], islConn.readPos)
	islConn.readPos += int64(n)
	return n, err
}

// Note: Concurrent Write is prohibited
func (islConn *ISLConn) Write(b []byte) (int, error) {
	// Encode the data before writing
	tmp := append([]byte(nil), b...)
	encrypt(islConn.cipherspec, tmp, islConn.writePos)
	n, err := islConn.conn.Write(tmp)
	if err != nil {
		return n, err
	}
	islConn.writePos += int64(n)
	return n, err
}
func (islConn *ISLConn) Close() error {
	return islConn.conn.Close()
}
func (islConn *ISLConn) LocalAddr() net.Addr {
	return islConn.conn.LocalAddr()
}
func (islConn *ISLConn) RemoteAddr() net.Addr {
	return islConn.conn.RemoteAddr()
}
func (islConn *ISLConn) SetDeadline(t time.Time) error {
	return islConn.conn.SetDeadline(t)
}
func (islConn *ISLConn) SetReadDeadline(t time.Time) error {
	return islConn.conn.SetReadDeadline(t)
}
func (islConn *ISLConn) SetWriteDeadline(t time.Time) error {
	return islConn.conn.SetWriteDeadline(t)
}
