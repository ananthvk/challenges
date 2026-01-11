#include "getinput.h"

#define BUFFER_SIZE 8
char *get_dyn_line(size_t *size)
{
    int ch;
    size_t buffer_size = 0;
    size_t index = 0;
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    if (!buffer) {
        if (size) {
            *size = 0;
        }
        return NULL;
    }
    buffer_size = BUFFER_SIZE;
    while ((ch = getchar()) != EOF) {
        if (!(index < (buffer_size - 1))) {
            // Buffer is not wide enough, expand it
            buffer_size *= 2;
            char *tmp = realloc(buffer, buffer_size);
            if (!tmp) {
                printf("Couldn't realloc buffer\n");
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[index++] = (char)ch;
        if (ch == '\n') break;
    }
    buffer[index] = '\0';
    if (size) *size = index;
    return buffer;
}