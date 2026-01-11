/** Exercise 3-2. Write a function escape(s,t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies the
 * string t to s. Use a switch. Write a function for the other direction as
 * well, converting escape sequences into the real characters. */
#include <assert.h>
#include <stdio.h>
void escape(char s[], char t[], int destSize)
{
    int i = 0, j = 0;
    while (s[i] != '\0') {
        if (j >= (destSize - 2)) {
            // Example:
            // For buffer size of 4096
            // Array:   |     |     |  \0  |
            // Index:    4093  4094  4095
            // if the index is 4094 (in this example), the program can store
            // at most one char, but if the char has to be expanded, it can
            // cause a buffer overflow.
            break;
        }
        switch (s[i]) {
            case '\n':
                assert(j < (destSize - 1));
                t[j++] = '\\';
                assert(j < (destSize - 1));
                t[j] = 'n';
                break;
            case '\t':
                assert(j < (destSize - 1));
                t[j++] = '\\';
                assert(j < (destSize - 1));
                t[j] = 't';
                break;
            default:
                assert(j < (destSize - 1));
                t[j] = s[i];
                break;
        }
        j++;
        i++;
    }
    assert(j <= (destSize - 1));
    t[j] = '\0';
}
int main()
{
    char *str = "this is a sample string\n a newline here\n one more\t a tab";
    char buff[256];
    escape(str, buff, 256);
    printf("%s", buff);
}
