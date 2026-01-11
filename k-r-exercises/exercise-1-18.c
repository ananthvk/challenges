// COMMAND: exercise-1-18.exe < ttext\strip_spaces_end.txt | exercise-1-10.exe
// This mostly works.... but it does not work when a non empty line has more
// spaces than what the buffer can hold. The previous buffer will not know
// whether to print or not print those spaces. For example: (dots are spaces
// here) Hello..............................
//               | (say buffer splits here)
// Hello..........
// ....................
// Now the line containing hello does not know whether to print those spaces or
// not.

// It can also be like this
// Hello..........
// .............3......
// So when processing the Hello line, it is not known whether this line is
// trailing or not.
//
// The question has asked only to remove trailing blanks, while this solution
// strips both preceeding and trailing blanks.

// One solution is to use dynamic memory allocation to store the entire text in
// memory.
#define BUFFER_SIZE 65
#define LINE_BEG 0
#define LINE_MID 1
#define LINE_END 2

#include <assert.h>
#include <stdio.h>
int getline(char buffer[], int bufferSize);
void _strncpy(char from[], char to[], int size);

int main()
{
    char buffer[BUFFER_SIZE] = {'\0'};
    int state = LINE_BEG, length, nonBlankIndex;

    while ((length = getline(buffer, BUFFER_SIZE))) {
        // Ignore blank or empty lines
        if ((length == 1 && buffer[0] == '\n') || length == 0) continue;
        nonBlankIndex = length;

        // Find the position of the last non-blank character of the line.
        for (int j = length - 2; j >= 0; j--) {
            if (!(buffer[j] == ' ' || buffer[j] == '\t')) {
                nonBlankIndex = j;
                break;
            }
        }

        for (int i = 0; i < length; i++) {
            if (state == LINE_BEG && buffer[i] != ' ' && buffer[i] != '\t') {
                state = LINE_MID;
            }
            if (buffer[length - 1] == '\n' && i >= nonBlankIndex) {
                putchar('\n');
                break;
            }
            if (state == LINE_MID) putchar(buffer[i]);
        }

        // The last non null character of the current buffer is a newline
        // so the line is complete.
        if (buffer[length - 1] == '\n') {
            // printf("#%c#\n", buffer[length-1]);
            state = LINE_BEG;
        }
        if (buffer[length - 1] != '\n') {
            // printf("*%c*\n", buffer[length-1]);
            state = LINE_MID;
        }
    }
}

void _strncpy(char from[], char to[], int size)
{
    // Copies n characters from from array to to array.
    // Assumed that the destination array is big enough and size is valid.
    for (int i = 0; i < (size - 1); i++) {
        if (from[i] == '\0') break;
        to[i] = from[i];
    }
    to[size - 1] = '\0';
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

        if (ch == '\n') {
            bufferIndex++;
            break;
        }

        bufferIndex++;
    }
    buffer[bufferIndex] = '\0';
    return bufferIndex;
}
