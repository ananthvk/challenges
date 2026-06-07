# Some general observations (using nc)

1. It sends READY (caps) after every message, after connect READY, then after every command READY
2. If a command that's not known is sent, it returns ERR [illegal method]: [method name]
3. Disconnects the connection incase of wrong method
4. Looks like line oriented, i.e. each command is newline terminated
5. HELP command:

```
    OK usage: HELP|GET|PUT|LIST
    READY
```

6. LIST dir
7. Doesn't disconnect if usage of the command is wrong (but disconnects when invalid method name is used)

```
    ERR usage: LIST dir
    READY
```

```
LIST x
ERR illegal dir name
```

No ready after this, no termination too

```
LIST /
OK 0
READY
```

Looks like unix paths, and 0 means no files here

```
PUT /foo/bar/x
ERR usage: PUT file length newline data
READY
```

```
PUT /foo/bar/baz 10
this
hello          
OK r1
READY
ERR illegal method:
```
So after the hello the `\n` became the illegal character, so that means empty commands are not allowed here

Also the file can contain any data, I guess it's stored length prefixed, so no need for it to be terminated by newline, after that the next command is entered by the user

```
READY
PUT /foo/bar/baz 10 
this
hell
OK r1
READY
```

So any whitespace char after the length, followed by length chars

`this\nhell\n` is exactly 10 chars

also it doesn't matter if the directory doesn't exist

```
LIST /
OK 1
foo/ DIR
READY
```

```
LIST /foo/bar
OK 1
baz r1
READY
LIST /foo/bar/
OK 1
baz r1
READY
```

Directories can have trailing slash

dirs have a DIR on the right, while files have the revision - r1, r2, r3 etc on the right

```
GET 
ERR usage: GET file [revision]
READY
```

```
GET /foo/bar 
ERR no such file
READY
```

```
LIST /xaa
OK 0
READY
LIST ha
ERR illegal dir name
```

So any path starting with `/` is legal, and if the dir doesn't exist, it returns 0. (along with READY)

```
GET baz
ERR illegal file name
```

After illegal file name / illegal dir name, no READY

And LIST returns 0 when the path is a file

```
GET /foo/bar/baz 
OK 10
this
hell
READY
```

Optional revision can be specified
```
GET /foo/bar/baz  r1
OK 10
this
hell
READY
```

```
GET /foo/bar/baz   r1
ERR usage: GET file [revision]
READY
GET /foo/bar/baz r1
OK 10
this
hell
READY
```
Extra spaces are not allowed

```
PUT /foo/bar/baz/ha 10
this
bell
OK r1
READY
```
Okay this is weird, but `baz` is a file, so it can act as both a file and a dir, and can have sub dirs / paths under it too

```
LIST /foo/bar/baz
OK 1
ha r1
READY
```

After PUT again for the path
```
LIST /foo/bar
OK 1
baz r2
READY
```

So here, paths are like identifiers, like in an object storage

```
LIST /$$
ERR illegal dir name
LIST /xx
OK 0
READY
LIST /11
OK 0
READY
```
Special chars are probably not allowed

```
READY
PUT /😭 10
ERR illegal file name
PUT /x 10
😭😭😭😭ERR text files only
READY
```

No emojis in file name, probably only ascii

```
READY
PUT /x 10
this
hell
OK r1
READY
PUT /x/y 10
haha
blah
OK r1
READY
PUT /x/z 10
hehe
blah
OK r1
READY
LIST /x/z
OK 0
READY
LIST /x
OK 2
y r1
z r1
READY
PUT /x/y/g/h 10
this
wool
OK r1
READY
LIST /x
OK 2
y r1
z r1
READY
PUT /x/k/g/h 10
HAHA
meow
OK r1
READY
LIST /x
OK 3
k/ DIR
y r1
z r1
READY
PUT /x/k 10
GAHH
RAHH
OK r1
READY
LIST /x
OK 3
k r1
y r1
z r1
READY
GET /x/k/g/h
OK 10
HAHA
meow
READY
```

file overrides dir (even though the dir and sub files still exist)

## Summary

- Connection
  - Send `READY` on connect
  - Send `READY` after every successful command and usage error
  - Unknown/empty command : `ERR illegal method: <name>` and disconnect

- Commands
  - Supported: `HELP`, `LIST`, `GET`, `PUT`
  - Parsing is strict; extra spaces can cause usage errors
  - Trailing spaces are allowed, but leading spaces, and spaces between the command are not allowed
  - Case insensitive

- HELP
  - Return: `OK usage: HELP|GET|PUT|LIST`

- Path validation
  - Must start with `/`
  - ASCII path only
  - Invalid file/dir name : `ERR illegal file name` / `ERR illegal dir name` (no `READY` observed)
  - Multiple slashes are not allowed
  - File paths are case sensitive

- Storage model
  - Treat paths like an object store, not a normal filesystem.
  - A path can be both a file and have children

- PUT
  - Syntax: `PUT <file> <length>` + whitespace + exactly `<length>` bytes
  - Data is length-prefixed, not newline-terminated
  - Reject non-text content (`ERR text files only`)
  - Each write creates a new revision (`r1`, `r2`, ...)
  - If length is negative or zero, an empty file is created (length 0)

- GET
  - Syntax: `GET <file> [revision]`
  - Missing file : `ERR no such file`
  - Success : `OK <length>` + file contents
  - Support fetching specific revisions

- LIST
  - Syntax: `LIST <dir>`
  - Nonexistent dir : `OK 0`
  - Trailing slash allowed
  - Return immediate children only
  - Files shown as `<name> rN`
  - Directories shown as `<name>/ DIR`
  - Also supports listing `/` (other methods return error for root path)

- File/dir precedence
  - If a path is both a file and a directory, LIST shows it as a file
  - Descendants under that path remain accessible