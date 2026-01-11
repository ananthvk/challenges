#define BUFFER_SIZE 82
#define IN_LINE 1
#define OUT_LINE 0
// Buffer size is defined as 82 so that 80 characters and a new line can be
// stored along with one null character at the end.

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

int kr_getline(char buffer[], int bufferSize);
void kr_strncpy(char src[], char dest[], int destSize);

int main()
{
    int length;
    char buffer[BUFFER_SIZE] = {0};
    int state = OUT_LINE;
    while ((length = kr_getline(buffer, BUFFER_SIZE))) {
        if (length == (BUFFER_SIZE - 1)) {
            if (buffer[length - 1] != '\n') state = IN_LINE;
            printf("%s", buffer);
        }
        else if (state == IN_LINE) {
            state = OUT_LINE;
            printf("%s", buffer);
        }
        // printf("(%d)[%s]", length, buffer);
    }
}

void kr_strncpy(char src[], char dest[], int destSize)
{
    // Copies characters from source array to destination array.
    // Also null terminates the destination array.

    int i = 0;
    while (1) {
        assert(i <= (destSize - 1));
        dest[i] = src[i];
        if (src[i] == '\0') return;

        i++;
        if (i == (destSize - 1)) {
            // No more room to copy another character, destSize-2 location is
            // already filled, set character at index destSize-1 to null
            // character.
            dest[i] = '\0';
            return;
        }
    }
}

int kr_getline(char buffer[], int bufferSize)
{
    int ch, bufferIndex = 0, lineLength = 0;
    // lineLength also counts the newline character(if any)
    while (1) {
        ch = getchar();

        if (ch == EOF) {
            // The code to check for End of file is placed here, so that the
            // program does not add the EOF to the buffer, and also does not
            // inrease the line length.
            assert(bufferIndex <= (bufferSize - 1));
            buffer[bufferIndex] = '\0';
            return lineLength;
        }
        assert(bufferIndex <= (bufferSize - 1));

        buffer[bufferIndex] = ch;
        lineLength++;
        bufferIndex++;

        if (ch == '\n') {
            // The below code guarantees that there is one vacant position at
            // the end of the buffer, So it is not necessary to check
            // overflow condition here.
            assert(bufferIndex <= (bufferSize - 1));
            buffer[bufferIndex] = '\0';
            return lineLength;
        }

        if (bufferIndex == (bufferSize - 1)) {
            // Here, bufferIndex is the index for the next character to be read.
            // So if there is only one more location which is vacant in the
            // buffer, set that to null character and return the string.
            assert(bufferIndex <= (bufferSize - 1));
            buffer[bufferIndex] = '\0';
            return lineLength;
        }
    }
}
