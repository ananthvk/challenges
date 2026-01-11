/*
 * Rewrite the below code without using && and ||
 * for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 *      s[i] = c;
 */

#include <stdio.h>
#define BUFFER_SIZE 64
int main()
{
    char buffer[BUFFER_SIZE];
    int bufferIndex = 0, ch;
    while (bufferIndex < (BUFFER_SIZE - 1)) {
        ch = getchar();
        if (ch == EOF) break;
        buffer[bufferIndex] = ch;
        bufferIndex++;
        if (ch == '\n') break;
    }
    buffer[bufferIndex] = '\0';
    printf("%s", buffer);
}
