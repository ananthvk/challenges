/* Exercise 5-1. As written, getint treats a + or - not followed by a digit as a
 * valid representation of zero. Fix it to push such a character back on the
 * input. */
#include <ctype.h>
#include <stdio.h>
#define getch() (cp > 0) ? (charbuffer[--cp]) : getchar()
#define ungetch(ch)                                                 \
    if (cp >= CHARBUFFSIZE)                                         \
        printf("Temporary buffer stack is full, cant push back\n"); \
    else                                                            \
        charbuffer[cp++] = (char)ch;

#define CHARBUFFSIZE 100
int cp = 0;
char charbuffer[CHARBUFFSIZE] = {'\0'};
// cp is the index for the next free space in the stack
// The other way to implement this is to set cp to -1 when the stack is empty.

int getint(int *pn)
{
    int ch, sign = 1, ch2;
    // Skip spaces
    while (isspace(ch = getch()))
        ;

    // Check if the current char is part of a number
    if (!(isdigit(ch) || ch == '+' || ch == '-' || ch == '.')) {
        ungetch(ch) return 0;
    }

    sign = (ch == '-') ? -1 : 1;
    if (ch == '-' || ch == '+') {
        ch2 = getch();
        if (!isdigit(ch2)) {
            // Example +a, This program uses it as valid representation of 0.
            ungetch(ch2) ungetch(ch) return 0;
        }
        ch = ch2;
    }

    for (*pn = 0; isdigit(ch); ch = getch()) {
        *pn = 10 * *pn + (ch - '0');
    }
    *pn *= sign;
    if (ch != EOF) {
        ungetch(ch)
    }
    return ch;
}
int main()
{
    int var = 0;
    // int var2 = 0;
    int i = getint(&var);
    // int j = getint(&var2);
    printf("%c\n", getch());
    printf("%d\n", var);
    // printf("%d\n", var2);
}
