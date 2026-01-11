// Write a function reverse(s) that reverses the character string s. Use it to
// write a program that reverses its input a line at a time.
// This version of the program has a fixed max line length constraint, as I have
// used no dynamic memory allocation, it is not possible to reverse and print
// if the line is split into multiple buffers.
#include <stdio.h>
// Arbitary max line length
#define MAX_LINE_LENGTH 32768

int getline(char buffer[], int bufferSize);

int main()
{
    int length;
    char buffer[MAX_LINE_LENGTH] = {'\0'};
    while ((length = getline(buffer, MAX_LINE_LENGTH))) {
        // getline() returns the size of the string
        // For example: Hello
        // Size: 7
        // H e l l 0 \n \0
        // 1 2 3 4 5  6  7
        // So the program has to print backwards from index 5
        // hence length - 2
        for (int i = length - 2; i >= 0; i--) {
            putchar(buffer[i]);
        }
        putchar('\n');
    }
}

int getline(char buffer[], int bufferSize)
{
    int ch, bufferIndex = 0;
    // Characters are stored in the buffer, leaving
    // one space vacant for the null character.
    while (bufferIndex < (bufferSize - 1)) {
        ch = getchar();
        if (ch == EOF) break;

        buffer[bufferIndex] = ch;
        // bufferIndex is the index for the next character to be read.
        bufferIndex++;

        if (ch == '\n') {
            break;
        }
    }
    buffer[bufferIndex] = '\0';
    return bufferIndex;
}
