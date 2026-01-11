#include <stdio.h>

int main()
{
    int ch;
    int isLastCharSpace = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == ' ')
            isLastCharSpace = 1;
        else {
            if (isLastCharSpace) putchar(' ');
            putchar(ch);
            isLastCharSpace = 0;
        }
    }
    return 0;
}
