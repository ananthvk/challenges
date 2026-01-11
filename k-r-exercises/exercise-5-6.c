/* Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities include
 * getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3,
 * and 4), reverse (Chapter 3), and strindex and getop (Chapter 4). */
#include <ctype.h>
#include <stdio.h>
size_t getline(char *buffer, size_t bufferSize)
{
    if (!buffer) return 0;
    char *buffOrig = buffer;
    int ch;

    while ((buffer - buffOrig) < (unsigned)(bufferSize - 1)) {
        ch = getchar();
        if (ch == EOF) break;
        *buffer++ = (char)ch;
        if (ch == '\n') break;
    }
    *buffer = '\0';
    return (size_t)(buffer - buffOrig);
}
int main()
{
    size_t length;
    char buffer[128];
    while ((length = getline(buffer, 128))) {
        printf("%zu - %s\n", length, buffer);
    }
}
