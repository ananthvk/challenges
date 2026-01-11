/** Exercise 3-3. Write a function expand(s1,s2) that expands shorthand
 * notations like a-z in the string s1 into the equivalent complete list
 * abc...xyz in s2. Allow for letters of either case and digits, and be prepared
 * to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or
 * trailing - is taken literally. */
/*
 * Procedure
 * ===========
 * Let s1 be a null terminated char array of size n
 * Let mode = COPY_MODE
 * Let lastChar = ""
 * Let j = 0
 * s1 - s1[0] s1[1] ...... s1[n-1], where s1[n-1] = '\0'
 * For i = 0 to n-2
 *     IF mode = COPY_MODE
 *         IF s1[i] == '-'
 *              mode = EXPAND_MODE
 *         ELSE
 *              s2[j++] = s1[i]
 *              lastChar = s1[i]
 *     ELSE IF mode = EXPAND_MODE
 *         IF s1[i] > lastChar
 *              For every character between lastChar and s[i]
 *                  s2[j++] = char
 *              lastChar = s1[i]
 *              mode = COPY_MODE
 *         IF s1[i] == lastChar
 *              mode = COPY_MODE
 *         ELSE
 *              s2[j++] = -
 *              s2[j++] = s1[i]
 *              lastChar = s1[i]
 *              mode = COPY_MODE
 *  IF mode = EXPAND_MODE
 *     # implies that there was a trailing -
 *     s[j++] = '-'
 *  s[j] = '\0'
 *
 */
#include <ctype.h>
#include <stdio.h>
enum Mode { COPY_MODE, EXPAND_MODE };
#define BUFFER_SIZE 4096

void expand(char s1[], char s2[], int destSize)
{
    // Assumes that s1 is null terminated.
    enum Mode mode = COPY_MODE;
    int i = 0, j = 0;
    char lastChar = '\0';

    while (s1[i] != '\0') {
        if (!(j < (destSize - 2))) break;
        switch (mode) {
            case COPY_MODE:
                if (s1[i] == '-') {
                    mode = EXPAND_MODE;
                }
                else {
                    s2[j++] = s1[i];
                    lastChar = s1[i];
                }
                break;
            case EXPAND_MODE:
                if (lastChar == '\0') {
                    // Leading -
                    // Example: -abc
                    // Output: -abc
                    s2[j++] = '-';
                    s2[j++] = s1[i];
                    lastChar = s1[i];
                    mode = COPY_MODE;
                }
                else if (s1[i] > lastChar) {
                    // printf("%s %c-%c\n", "Expanding", lastChar, s1[i]);
                    // printf("%c-%c\n", lastChar+1, s1[i]);
                    for (int k = lastChar + 1; k <= s1[i]; k++) {
                        // I made a mistake of taking the loop variable as i
                        // here which caused a conflict with the outer loop i.
                        s2[j++] = k;
                    }
                    lastChar = s1[i];
                    mode = COPY_MODE;
                }
                else if (s1[i] == lastChar)
                    mode = COPY_MODE;
                else {
                    s2[j++] = '-';
                    s2[j++] = s1[i];
                    lastChar = s1[i];
                    mode = COPY_MODE;
                }
                break;
        }
        i++;
    }
    if (mode == EXPAND_MODE) {
        s2[j++] = '-';
    }
    s2[j] = '\0';
}
int getline(char buffer[], int bufferSize)
{
    // This implementation of getline does not include the newline char
    // in the buffer.
    int bufferIndex = 0;
    int ch;
    while (bufferIndex < (bufferSize - 1)) {
        ch = getchar();
        if (ch == EOF || ch == '\n') break;
        buffer[bufferIndex++] = ch;
    }
    buffer[bufferIndex] = '\0';
    return bufferIndex;
}
int main()
{
    char buffer[BUFFER_SIZE];
    /* char *str = "-a-a-zThe mystery of b-b-b-b A-K the universe a-d is 0-9
     * what does it z-m-ean-z-a-z-a-z0-9-a-z0-9 here is one more example
     * a-z0-99'"; */
    char str[BUFFER_SIZE];
    while (getline(str, BUFFER_SIZE)) {
        expand(str, buffer, BUFFER_SIZE);
        printf("%s\n", buffer);
    }
}
