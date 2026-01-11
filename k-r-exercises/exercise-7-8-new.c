#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_BUFFER_SIZE 8
#define PAGE_WIDTH 100
#define PAGE_BLANK_LINES_AFTER_HEADER 3
#define PAGE_BLANK_LINES_BEFORE_FOOTER 2
#define PAGE_LENGTH_ABSOLUTE 50

#define PAGE_LINE_END_CHAR "|"
#define PAGE_HEAD_FOOT_FILL_CHAR "-"
#define PAGE_TOP_LEFT_CHAR "+"
#define PAGE_TOP_RIGHT_CHAR "+"
#define PAGE_BOTTOM_LEFT_CHAR "+"
#define PAGE_BOTTOM_RIGHT_CHAR "+"

#define PAGE_LENGTH                                        \
    PAGE_LENGTH_ABSOLUTE - PAGE_BLANK_LINES_AFTER_HEADER - \
        PAGE_BLANK_LINES_BEFORE_FOOTER

#define PRINT_BLANK()                                                   \
    fprintf(stdout, "%s%-*.*s%s\n", PAGE_LINE_END_CHAR, PAGE_WIDTH - 2, \
            PAGE_WIDTH - 2, "", PAGE_LINE_END_CHAR)

#define LEFT_ALIGN(content)                                             \
    fprintf(stdout, "%s%-*.*s%s\n", PAGE_LINE_END_CHAR, PAGE_WIDTH - 2, \
            PAGE_WIDTH - 2, content, PAGE_LINE_END_CHAR)

#define CENTER_ALIGN(content)                                               \
    {                                                                       \
        int pad_width_l = (PAGE_WIDTH - 2 - strlen(content)) / 2;           \
        int pad_width_r = (PAGE_WIDTH - 2 - strlen(content)) - pad_width_l; \
        printf("%s", PAGE_LINE_END_CHAR);                                   \
        printf("%*s", pad_width_l, "");                                     \
        printf("%.*s", PAGE_WIDTH - 2, content);                            \
        printf("%*s", pad_width_r, "");                                     \
        printf("%s\n", PAGE_LINE_END_CHAR);                                 \
    };

// https://en.wikipedia.org/wiki/Box-drawing_character#Unicode
/*
#define PAGE_LINE_END_CHAR "\u2502"
#define PAGE_HEAD_FOOT_FILL_CHAR "\u2500"
#define PAGE_TOP_LEFT_CHAR "\u250c"
#define PAGE_TOP_RIGHT_CHAR "\u2510"
#define PAGE_BOTTOM_LEFT_CHAR "\u2514"
#define PAGE_BOTTOM_RIGHT_CHAR "\u2518"
*/

int current_line = 1;
int current_page = 1;
char *current_file_name = NULL;

char *getaline(FILE *fp, int *length)
{
    // Function for getting a dynamically growable line from the given stream.
    int ch;
    if (fp == NULL) return NULL;
    char *buffer = malloc(sizeof(char) * INIT_BUFFER_SIZE);
    if (!buffer) return NULL;

    int buffer_size = INIT_BUFFER_SIZE;
    int buffer_index = 0;

    while ((ch = getc(fp)) != EOF)
    {
        if (ferror(fp))
        {
            free(buffer);
            return NULL;
        }
        if (buffer_index >= (buffer_size - 1))
        {
            // Expand the buffer
            buffer_size *= 2;
            char *ptr = realloc(buffer, buffer_size);
            if (!ptr)
            {
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

typedef void (*print_ptr)();

void printline(char *line, print_ptr header_function, print_ptr footer_function)
{
    if (current_line >= PAGE_LENGTH)
    {
        // Print on a new page
        if (footer_function) footer_function();
        current_page++;
        current_line = 1;
        if (header_function) header_function();
    }
    line[strcspn(line, "\n")] = 0;
    LEFT_ALIGN(line);
    current_line++;
}

void printpage(FILE *stream, print_ptr header_function,
               print_ptr footer_function)
{
    int line_size = 0;
    char *line = NULL;
    if (header_function) header_function();
    while ((line = getaline(stream, &line_size)))
    {
        if (line_size == 0)
        {
            free(line);
            break;
        }
        printline(line, header_function, footer_function);
        free(line);
    }
    // Make the rest of the lines in the current page as blank
    for (; current_line < PAGE_LENGTH; current_line++)
    {
        PRINT_BLANK();
    }
    if (footer_function) footer_function();
    current_line = 1;
    current_page++;
}

void print_header()
{
    char *content =
        (current_file_name != NULL) ? current_file_name : "---Empty file---";
    // Print the top border
    printf("%s", PAGE_TOP_LEFT_CHAR);
    for (int i = 0; i < (PAGE_WIDTH - 2); i++)
    {
        printf("%s", PAGE_HEAD_FOOT_FILL_CHAR);
    }
    printf("%s", PAGE_TOP_RIGHT_CHAR);
    putchar('\n');

    CENTER_ALIGN(content);
    // Display blank lines
    for (int i = 0; i < PAGE_BLANK_LINES_AFTER_HEADER; i++)
    {
        PRINT_BLANK();
    }
}

void print_footer()
{
    size_t required_size = snprintf(NULL, 0, "Page %d", current_page);
    char *content = malloc(sizeof(char) * (required_size + 1));
    if (!content)
    {
        fprintf(stderr, "Error - ran out of memory");
        exit(1);
    }
    sprintf(content, "Page %d", current_page);

    // Display blank lines
    for (int i = 0; i < PAGE_BLANK_LINES_BEFORE_FOOTER; i++)
    {
        PRINT_BLANK();
    }

    CENTER_ALIGN(content);

    // Print the bottom border
    printf("%s", PAGE_BOTTOM_LEFT_CHAR);
    for (int i = 0; i < (PAGE_WIDTH - 2); i++)
    {
        printf("%s", PAGE_HEAD_FOOT_FILL_CHAR);
    }
    printf("%s", PAGE_BOTTOM_RIGHT_CHAR);
    putchar('\n');
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "Usage %s <file1> <file2> ...\n", argv[0]);
        exit(1);
    }
    if (argc == 0)
    {
        fprintf(stderr, "No args\n");
        exit(2);
    }
    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (!fp)
        {
            fprintf(stderr, "%s: Error - Unable to open file %s\n", argv[0],
                    argv[i]);
            exit(1);
        }
        current_file_name = argv[i];
        printpage(fp, print_header, print_footer);
        current_page = 1;
        current_line = 1;
        fclose(fp);
    }
}