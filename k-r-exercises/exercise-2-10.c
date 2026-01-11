/** Exercise 2-10. Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expression instead of if-else.
 */

#include <stdio.h>
/*
 * NOTE: This program does not work on all charsets
 * Only works on ascii
 */
int toLower(int ch) { return ((ch >= 'A') && (ch <= 'Z')) ? (ch + 32) : ch; }
int main()
{
    int ch;
    while ((ch = getchar()) != EOF) {
        putchar(toLower(ch));
    }
}
