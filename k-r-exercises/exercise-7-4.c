#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Grammar - EBNF
========
format specifier = "%", [{digit} | "*"], character;
digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
character = "s" | "f" | "d" | "c";
*/

int consume_character(char ch, int *err_occured)
{
    // ch - character to be compared with.
    // err_occured - pointer to int which serves as a flag to check if error
    // occured. Function returns the character if the same character is read
    // from the input, else 0 and err_occured flag is set accordingly.
    int inp_ch = getchar();
    if (inp_ch == ch) {
        if (err_occured) *err_occured = 0;
        return inp_ch;
    }
    else {
        ungetc(inp_ch, stdin);
        if (err_occured) *err_occured = 1;
        return 0;
    }
}
int consume_number(int *err_occured)
{
    // err_occured - pointer to int which serves as a flag to check if error
    // occured.
    int ch = 0;
    int converted = 0;
    // Skip whitespaces when reading a number
    while (isspace(ch = getchar()))
        ;
    // A non-whitespace char was read, push it back so that it can be read in
    // next call to getchar
    ungetc(ch, stdin);

    while (isdigit(ch = getchar())) {
        converted = converted * 10 + (ch - '0');
    }
    // Push back the non numeric character
    ungetc(ch, stdin);
    if (err_occured) *err_occured = 0;
    return converted;
}

int my_scanf(const char *fmt, ...)
{
    va_list args;
    int ch;
    int to_save = 0;
    int elements_read = 0;
    int errflag;
    char *c_ptr;

    union val {
        int i_val;
        float f_val;
        char c_val;
    } value;
    va_start(args, fmt);

    if (fmt == NULL) {
        va_end(args);
        return 0;
    }
    while (*fmt) {
        if (*fmt == '%') {
            // Found the start of a format specifier
            // Field width is currently not supported
            to_save = 1;
            ch = *(++fmt);

            if (ch == '*') {
                to_save = 0;
                ch = *(++fmt);
            }
            switch (ch) {
                case 's':
                    c_ptr = va_arg(args, char *);

                    break;

                case 'f':
                    break;

                case 'd':
                    value.i_val = consume_number(&errflag);
                    int *d_ptr = va_arg(args, int *);
                    elements_read++;
                    if (d_ptr && to_save) *d_ptr = value.i_val;
                    break;

                case 'c':
                    ch = getchar();
                    if (ch != EOF) {
                        c_ptr = va_arg(args, char *);
                        if (c_ptr && to_save) c_ptr[0] = ch;
                        elements_read++;
                    }
                    else {
                        va_end(args);
                        return elements_read;
                    }
                    break;

                default:
                    printf("Unknown format letter to scanf, %c\n", ch);
                    exit(1);
                    break;
            }
            fmt++;
        }
        else {
            // A literal character
            ch = getchar();
            if (ch != *fmt) {
                // We have read some other character
                ungetc(ch, stdin);
                va_end(args);
                return elements_read;
            }
            fmt++;
        }
    }

    va_end(args);
    return elements_read;
}

int main()
{
    int a;
    char ch;
    int b;
    printf("%d\n", my_scanf("%d-%c-%d", &a, &ch, &b));
    printf("%d %c %d\n", a, ch, b);
}