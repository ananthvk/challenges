all: build

build: helpers.c sort.c sorting_algorithms.c
	gcc -Wall -Wextra -O0 -ggdb3 -W -pedantic helpers.c sort.c sorting_algorithms.c -o sorter

run: build
	sorter

clean:
	rm *.exe
	rm *.o
