all: build
build: dcl.c getinput.h getinput.c
	gcc -Wall -Wextra -pedantic -O0 -ggdb3 dcl.c getinput.c -o dcl

run: build
	dcl