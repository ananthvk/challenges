#include<stdio.h>
#define INIT_BUFFER_SIZE 8
#define PAGE_WIDTH 100
#define PAGE_LENGTH 50
#define PAGE_LINE_END_CHAR '|'

int current_line = 1;
int current_page = 1;

char *getaline(FILE *fp, int *length)
{
    // Function for getting a dynamically growable line from the given stream.
    int ch;
    if (fp == NULL) return NULL;
    char *buffer = malloc(sizeof(char) * INIT_BUFFER_SIZE);
    if(!buffer) return NULL;

    int buffer_size = INIT_BUFFER_SIZE;
    int buffer_index = 0;


    while ((ch = getc(fp)) != EOF) {
        if(ferror(fp))
        {
            free(buffer);
            return NULL;
        }
        if (buffer_index >= (buffer_size - 1)) {
            // Expand the buffer
            buffer_size *= 2;
            char *ptr = realloc(buffer, buffer_size);
            if (!ptr) {
                free(buffer);
                return NULL;
            }
            buffer = ptr;
        }
        buffer[buffer_index++] = ch;
        if (ch == '\n') break;
    }
    buffer[buffer_index] = '\0';

    if (length) *length = buffer_index;
    return buffer;
}


typedef void (*print_ptr)(void);

void fprintline(FILE *out, const char *line, print_ptr header_function, print_ptr footer_function)
{
    printf("%c%c", PAGE_LINE_END_CHAR, PAGE_LINE_END_CHAR);
}

void fprintpage(FILE *out, FILE *stream, print_ptr header_function, print_ptr footer_function)
{
    int line_size = 0;
    char *line = NULL;
    while((line = getaline(stream, &line_size)))
    {
        if(line_size == 0)
        {
            free(line);
            break;
        }
        fprintline(out, line, header_function, footer_function);
        free(line);
    }
}