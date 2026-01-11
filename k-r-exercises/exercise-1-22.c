/*
 * My algorithm to fold lines as specified by the given fold width.
 * Create a character array (buffer) of the required fold width + 1 (for the
 * null char) Set rem = 0 While EOF is not yet reached. Read upto a newline or
 * fold width - rem characters, whichever is smaller into the buffer If the
 * number of characters read are less than fold width Print buffer Else Find the
 * index of the last space, hyphen or tab from the buffer. If no such position
 * was found Set index to fold width - 1
 *
 *          Print buffer until this index (not inclusive)
 *          Print a newline
 *
 *          Set rem to the number of remaining characters.
 *          Print remaining characters of the buffer.
 *  ^^^
 *  For some reason, the above algorithm does not work correctly.
 *
 *  New and improvised algorithm
 *  =============================
 *  Set used_space = 0
 *  While EOF is not yet reached
 *      Read (FOLD_WIDTH - used_space) characters from the input or till a
 * newline, whichever is smaller into buffer.
 * If the last character of the buffer(string) is a newline
 *      Print the buffer
 *      Set used_space = 0
 *  Else Find the index of the last space, tab or hyphen (break character) from
 * then end. If no space was found Print the buffer completely Print a newline
 *      Set used_space = 0
 *  Else Print the buffer till the last break character (excluding the break
 * character). Print a newline Print characters after the last break character
 * till the end of the buffer. Set used_space = Number of characters after the
 * last break character.
 */
#include <assert.h>
#include <stdio.h>
#define FOLD_WIDTH 80

int getline(char buffer[], int bufferSize)
{
    int ch, bufferIndex = 0;
    while (bufferIndex < (bufferSize - 1)) {
        ch = getchar();
        if (ch == EOF) break;
        buffer[bufferIndex] = ch;

        bufferIndex++;
        if (ch == '\n') break;
    }
    buffer[bufferIndex] = '\0';
    return bufferIndex;
}

int main()
{
    char buffer[FOLD_WIDTH + 1] = {'\0'};
    int usedSpace = 0, j, length;
    while ((length = getline(buffer, (FOLD_WIDTH + 1 - usedSpace)))) {
        if (buffer[length - 1] == '\n') {
            printf("%s", buffer);
            usedSpace = 0;
        }
        else {
            int i;
            for (i = length - 1; i >= 0; i--) {
                if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '-') {
                    break;
                }
            }
            // No whitespace or tab or hyphen was found, Break exactly at fold
            // width.
            if (i == -1) {
                printf("%s", buffer);
                printf("%s", "\n");
                usedSpace = 0;
            }
            else {
                for (j = 0; j < i; j++) putchar(buffer[j]);
                putchar('\n');
                for (j = i + 1; j < length; j++) putchar(buffer[j]);
                usedSpace = length - i - 1;
            }
        }
    }
}
