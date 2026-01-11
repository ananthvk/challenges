// Exercise 7-6. Write a program to compare two files, printing the first line
// where they differ.

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define INIT_BUFFER_SIZE 8
// Algorithm / Pseudocode
// 1. Read one line from both the files
// 2. If the lines are not identical, display the line number, line and exit

char *getaline(FILE *fp, int *length)
{
    // Function for getting a dynamically growable line from the given stream.
    int ch;
    char *buffer = malloc(sizeof(char) * INIT_BUFFER_SIZE);
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

int main(int argc, char *argv[])
{
    int line_length_file1 = 0;
    int line_length_file2 = 0;
    char *line_file1 = NULL;
    char *line_file2 = NULL;

    if(argc != 3)
    {
        printf("Usage: %s file1 file2\n", argv[0]);
        exit(1);
    }


    FILE *file_1 = fopen(argv[1], "r");
    FILE *file_2 = fopen(argv[2], "r");

    if(!file_1)
    {
        printf("Error: Could not open file %s\n", argv[1]);
        exit(2);
    }

    if(!file_2)
    {
        printf("Error: Could not open file %s\n", argv[2]);
        exit(2);
    }

    while ((line_file1 = getaline(file_1, &line_length_file1)) && (line_file2 = getaline(file_2, &line_length_file2))) {
        if (line_length_file1 == 0 || line_length_file2 == 0) {
            if(line_length_file1 == 0)
            {
                printf("%s", line_file2);
            }

            else if(line_length_file2 == 0)
            {
                printf("%s", line_file1);
            }

            else 
            {
                printf("IDENTICAL\n");
            }

            free(line_file1);
            free(line_file2);

            fclose(file_1);
            fclose(file_2);
            exit(0);
        }

        if(strcmp(line_file1, line_file2) != 0)
        {
            printf("%s: %s", argv[1], line_file1);
            printf("%s: %s", argv[2], line_file2);
            exit(0);
        }

            free(line_file1);
            free(line_file2);
    }
}