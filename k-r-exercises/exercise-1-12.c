#include <stdio.h>
// To print the input, one word per line,
// Whenever the program encounters a blank, tab or newline, print a newline
// character.
int main()
{
    int ch;
    int lastCharWasSpace = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t') {
            lastCharWasSpace = 1;
        }
        else {
            if (lastCharWasSpace) putchar('\n');
            putchar(ch);
            lastCharWasSpace = 0;
        }
    }
}
