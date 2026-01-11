/*
 * Program to replace tabs with multiple spaces.
 *
 * TODO: Apparently this code is incorrect as it replaces any tab with tabstop
 * number of spaces, but according to the question, tabstop was present in
 * typewriters and a tab adds that many spaces to the text so that the text is
 * aligned to a tabstop. For example: Hello \tworld |    |    | Let the tabstops
 * be 4 characters wide. So it should get printed as Hello   world |    |    |
 *  (So two spaces are added in this example)
 *  The program I have written is expanding tabs to spaces, like many editors.
 */
#include <assert.h>
#include <stdio.h>
#define TABSTOP 4
#define BUFFER_SIZE 4096
void detab(char str[]);
void detab2(char str[], char op[]);
int getline(char buffer[], int bufferSize);

int main()
{
    char buffer[BUFFER_SIZE] = {'\0'};
    // To be on the safer side, add few more extra spaces for null and other
    // chars.
    char outputBuffer[(BUFFER_SIZE * 4) + 1] = {'\0'};
    while (getline(buffer, BUFFER_SIZE)) {
        // detab(buffer);
        detab2(buffer, outputBuffer);
        printf("%s", outputBuffer);
    }
}

void printChars(char ch, int count)
{
    for (int i = 0; i < count; i++) putchar(ch);
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

void detab(char str[])
{
    int i = 0;
    while (str[i] != '\0') {
        /*printf("<i=%d> <%c>\n", i, str[i]);*/
        if (str[i] == '\t')
            printChars(' ', TABSTOP);
        else
            putchar(str[i]);
        i++;
    }
}

void detab2(char str[], char op[])
{
    /** Converts spaces from a single line (buffer) to tabs and spaces.
     * str - The input character array.
     * op - The output character array (has to be atleast TABSTOP times big
     * enough to store the characters incase the string is completely tabs) It
     * is assumed that str is null terminated and op array is big enough.*/
    int i;
    while (*str != '\0') {
        if (*str == '\t') {
            for (i = 0; i < TABSTOP; i++) *op++ = ' ';
        }
        else
            *op++ = *str;
        str++;
    }
    *op = '\0';
}
