/*
Exercise 7-2. Write a program that will print arbitrary input in a sensible way.
As a minimum, it should print non-graphic characters in octal or hexadecimal
according to local custom, and break long text lines.
*/

// 1. If the character is not printable (using isgraph() function), print its
// hexadecimal value.
// 2. If the non printable character is ' ' or '\n', print it, for all other
// character such as tab, print its escaped form
// 3. If the line is too long, defined as 80 and can be set through command line
// arguments, break it as in the fold program from exercise 1.

#include <ctype.h>
#include <stdio.h>
#define HEX_SIZE 4
#define MAX_LINE_SIZE 80

void print_escape_char(int ch) { 
    printf("\\%c ", ch); 
}

int main()
{
    int ch;
    // To open stdin in binary mode
    freopen(NULL, "rb", stdin);
    int line_ptr = 0;

    while ((ch = getchar()) != EOF) {
        if(line_ptr >= MAX_LINE_SIZE)
        {
            printf("\n");
            line_ptr = 0;
        }
        if (isprint(ch))
        {
            printf("%c", ch);
            line_ptr++;
        }
        else if (ch == '\n') {
            // print_escape_char('n');
            printf("\n");
            line_ptr = 0;
        }
        else if (ch == '\r') {
            print_escape_char('r');
            line_ptr++;
        }
        else if (ch == '\t') {
            print_escape_char('t');
            line_ptr++;
        }
        else if (ch == '\a') {
            print_escape_char('a');
            line_ptr++;
        }
        else if (ch == '\b') {
            print_escape_char('b');
            line_ptr++;
        }
        else if (ch == '\f') {
            print_escape_char('f');
            line_ptr++;
        }
        else if (ch == '\v') {
            print_escape_char('v');
            line_ptr++;
        }
        else {
            // Print the hex version of the character
            printf("%0*x ", HEX_SIZE, ch);
            line_ptr += HEX_SIZE;
        }
    }
}