// Exercise 7-8. Write a program to print a set of files, starting each new one
// on a new page, with a title and a running page count for each file.
#include <stdio.h>
#include <string.h>
#define INIT_BUFFER_SIZE 8
/*
void repeatchar(char ch, int width)
{
    for (int i = 0; i < width; i++) {
        putc(ch, stdin);
    }
}

void centerpad(const char *str, int width)
{
    int string_length = strlen(str);
    if (width <= 0) return;
    if (string_length >= width) {
        // Print the truncated title

        printf("%.*s~", width - 1, str);
    }
    else {
        int pad_width_l = (width - string_length) / 2;
        int pad_width_r = (width - string_length) - pad_width_l;

        // Padding on left
        printf("%*s", pad_width_l, "");

        // Display the string
        printf("%.*s", width, str);

        // Padding on right
        printf("%*s", pad_width_r, "");
    }
}

void rightpad(const char *str, int width)
{
    int string_length = strlen(str);
    if (width <= 0) return;
    if (string_length >= width) {
        // Print the truncated title

        printf("%.*s~", width - 1, str);
    }
    else {
        int pad_width = (width - string_length);

        printf("%.*s", width, str);

        // Padding on right
        printf("%*s", pad_width, "");
    }
}

void vert_border_print(char end_ch, char fill_ch, int width)
{
    if (width >= 2) {
        putc(end_ch, stdout);
        width--;
        for (int i = 0; i < (width - 1); i++) {
            putc(fill_ch, stdout);
        }
        putc(end_ch, stdout);
        putc('\n', stdout);
    }
}

void display_line(const char *line, int width)
{
    if (width < 2) return;
    printf("|");
    rightpad(line, width - 2);
    printf("|\n");
}
*/
/*
void display_page_header(const char *header, int width,
                         int n_blank_after_header)
{
    vert_border_print('+', '-', width);
    printf("|");
    centerpad(header, width - 2);
    printf("|\n");
    for (int i = 0; i < n_blank_after_header; i++) {
        display_line("", width);
    }
}

void display_page_footer(const char *footer, int width,
                         int n_blank_before_footer)
{
    for (int i = 0; i < n_blank_before_footer; i++) {
        display_line("", width);
    }
    printf("|");
    centerpad(footer, width - 2);
    printf("|\n");
    vert_border_print('+', '-', width);
}

#define LINE_WIDTH 80
#define LINES_IN_PAGE 60
#define N_BLANK_LINES_AFTER_TITLE 3
#define N_BLANK_LINES_BEFORE_END 2
*/
/*
int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    int line_len = 0;
    int line_no = 1;
    char *line = NULL;
    int page_no = 1;
    if (argc <= 1) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (!fp) {
            fprintf(stderr, "%s: Error while opening file %s", argv[0],
                    argv[i]);
            continue;
        }
        // Display the header
        display_page_header(argv[i], LINE_WIDTH, N_BLANK_LINES_AFTER_TITLE);
        int to_print = 1;

        // Read each line and print it
        while ((line = getaline(fp, &line_len)) != NULL) {
            if (line_len == 0) {
                free(line);
                break;
            }
            to_print = 1;
            line[line_len - 1] = '\0';
            if (line_no > (LINES_IN_PAGE - N_BLANK_LINES_BEFORE_END -
                           N_BLANK_LINES_AFTER_TITLE)) {
                // If there are no more empty lines, start printing on new page
                line_no = 1;
                size_t req_buffer = snprintf(NULL, 0, "Page %d", page_no);
                char *buffer = malloc(sizeof(char) * (req_buffer + 1));
                if (!buffer) {
                    fprintf(stderr, "%s: Error - ran out of memory", argv[0]);
                    exit(1);
                }
                sprintf(buffer, "Page %d", page_no);
                display_page_footer(buffer, LINE_WIDTH,
                                    N_BLANK_LINES_BEFORE_END);
                page_no++;
                display_page_header(argv[i], LINE_WIDTH,
                                    N_BLANK_LINES_AFTER_TITLE);
                to_print = 0;
            }
            display_line(line, LINE_WIDTH);
            line_no++;
            free(line);
        }
        if (line == NULL) {
            fprintf(stderr, "%s: Error while reading file %s", argv[0],
                    argv[i]);
        }
        if (!to_print) {
            page_no++;
            continue;
        }
        // Display the footer
        size_t req_buffer = snprintf(NULL, 0, "Page %d", page_no);
        char *buffer = malloc(sizeof(char) * (req_buffer + 1));
        if (!buffer) {
            fprintf(stderr, "%s: Error - ran out of memory", argv[0]);
            exit(1);
        }
        // Blank out the remaining lines so that the next file starts on a new
        // page
        for (; line_no < (LINES_IN_PAGE - N_BLANK_LINES_AFTER_TITLE -
                          N_BLANK_LINES_BEFORE_END);
             line_no++) {
            display_line("", LINE_WIDTH);
        }
        sprintf(buffer, "Page %d", page_no);
        display_page_footer(buffer, LINE_WIDTH, N_BLANK_LINES_BEFORE_END);
        page_no++;
    }
}
*/

// For each file passed as argument
//      Open the file
//          Until there are no more lines in the file
//              Print header
//              Display n lines
//          Fill lines so that the current page can be filled and next file
//          Print footer
//          starts on a new page


struct Page {
    int page_no;
    int current_line_no;
    int max_lines_in_page;
    int width;
};

char *getaline(FILE *fp, int *length)
{
    // Function for getting a dynamically growable line from the given stream.
    int ch;
    char *buffer = malloc(sizeof(char) * INIT_BUFFER_SIZE);
    if(!buffer) return NULL;

    int buffer_size = INIT_BUFFER_SIZE;
    int buffer_index = 0;

    if (!buffer) return NULL;

    if (fp == NULL) return NULL;
    while ((ch = getc(fp)) != EOF) {
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

typedef struct Page Page;

Page Page_create(int width, int page_no, int max_lines_in_page)
{
    Page p;
    p.page_no = page_no;
    p.max_lines_in_page = max_lines_in_page;
    p.current_line_no = 1;
    p.width = width;
    return p;
}

void fprintpageheader(FILE *stream, Page *p, const char *title)
{

}

void fprintpagefooter(FILE *stream, Page *p)
{

}

int fprintpage(FILE *stream, Page *p, const char *line)
{
    // Writes the line to the stream and updates members in p
    // If there is not enough space left in the page and the line can't be
    // printed this function returns 0. If the printing was successful, the
    // function returns the index of the last char which was printed.
    // This function also takes care of text wrapping.
}

#define PAGE_WIDTH 100
#define PAGE_MAXLINES 50

int main(int argc, char *argv[])
{
    // Variables
    FILE *current_file = NULL;
    int current_page_no = 1;
    char *line = NULL;
    int line_length = 0;
    Page current_page = Page_create(PAGE_WIDTH, current_page_no, PAGE_MAXLINES);

    // Checks for argc
    if(argc == 1)
    {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        exit(1);
    }
    else if(argc == 0)
    {
        fprintf(stderr, "No args passed\n");
        exit(1);
    }

    // Open and display each file
    for(int i = 1; i < argc; i++)
    {
        current_file = fopen(argv[i], "r");
        if(!current_file){
            fprintf(stderr, "%s: Error - unable to open file %s", argv[0], argv[i]);
            continue;
        }

        // while ((line = getaline(fp, &line_len)) != NULL) {
        
        while(current_page.current_line_no < current_page.max_lines_in_page)
        {
            line = getaline(current_file, &line_length);
            if(!line)
            {
                fprintf(stderr, "%s: Error - error while reading from file %s\n", argv[0], argv[i]);
            }
            if(line_length == 0)
            {

            }
            while(fprintpage(stdout, &current_page, line) > 0)
            {
                // Means that after wrapping a portion of the line has to be printed

            }
        }
    }
}