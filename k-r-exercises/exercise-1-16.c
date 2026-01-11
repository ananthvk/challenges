#define MAX_LINE_LENGTH 501

// TODO: If the file is an empty file, the program prints some other chars
// Rectify this issue.
// Sample:
// Longest line:   0 characters
// ♦☺ <---- These chars are printed instead of nothing.
// The fix was to initialize the longest line array to 0, otherwise the printf
// function used to keep printing until a null char was found.
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
int kr_getline(char buffer[], int bufferSize);
void kr_strncpy(char src[], char dest[], int destSize);

int main()
{
    char buffer[MAX_LINE_LENGTH] = {0}, buffer2[MAX_LINE_LENGTH] = {0};
    char longestLine[MAX_LINE_LENGTH] = {0};
    int bufferLength, maxLength = 0, lineLength = 0;

    while ((bufferLength = kr_getline(buffer, MAX_LINE_LENGTH))) {
        // The last character of the buffer (excepting the null character), is
        // not a newline, which means that the buffer is partial.
        if ((bufferLength == (MAX_LINE_LENGTH - 1)) &&
            (buffer[MAX_LINE_LENGTH - 2] != '\n')) {
            if (lineLength == 0) {
                // This is the first section of the line.
                kr_strncpy(buffer, buffer2, MAX_LINE_LENGTH);
            }
            lineLength += bufferLength;
        }
        // The buffer is partially filed and has a newline or it is completely
        // filled with a newline at the end.
        else {
            if (lineLength > 0) {
                // This means that before this line, there are some incomplete
                // lines. So do  not overwrite the buffer.
                lineLength += bufferLength;
                if (lineLength > maxLength) {
                    maxLength = lineLength;
                    kr_strncpy(buffer2, longestLine, MAX_LINE_LENGTH);
                }
                lineLength = 0;
            }
            else {
                // There are no other incomplete lines before this line.
                if (bufferLength > maxLength) {
                    maxLength = bufferLength;
                    kr_strncpy(buffer, longestLine, MAX_LINE_LENGTH);
                }
            }
        }
    }
    printf("Longest line:%4d characters\n", maxLength);
    printf("%s\n", longestLine);
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
