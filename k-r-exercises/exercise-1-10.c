#include <stdio.h>

int main()
{
    int ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '\\') {
            putchar('\\');
            putchar('\\');
        }
        if (ch == '\n') {
            putchar('\\');
            putchar('n');
        }
        if (ch == '\t') {
            putchar('t');
        }
        if (ch == '\b') {
            putchar('\\');
            putchar('b');
        }
        if (ch == ' ') {
            putchar('.');
        }
        else
            putchar(ch);
    }
    return 0;
}
