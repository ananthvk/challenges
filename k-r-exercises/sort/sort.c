#include "helpers.h"
#include "sorting_algorithms.h"
#include "defs.h"
#include<stdint.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef uint8_t flag;
int main(int argc, char *argv[]){
    flag numeric = 0;
    flag reverse = 0;
    flag directory = 0;
    flag fold = 0;

    sort_fptr sort_alg = &bubble_sort;
    compare_fptr cmp_func = &strcmp;

    while(--argc>0)
    {
        if(*argv[argc] == '-')
        {
            // Found an option
            while(*++argv[argc])
            {
                switch(*argv[argc])
                {
                    case 'n':
                        numeric = 1;
                        break;
                    case 'r':
                        reverse = 1;
                        break;
                    case 'd':
                        directory = 1;
                        break;
                    case 'f':
                        fold = 1;
                        break;
                    case 'B':
                        sort_alg = &bubble_sort;
                        break;
                    default:
                        printf("Unknown flag -%c\n", *argv[argc]);
                    case 'h':
                        printf("Usage: sorter.exe [-nrdfB]\n");
                        printf("%-12s %s\n", "-n", "Sorts the text numerically");
                        printf("%-12s %s\n", "-d", "Sorts according to directory order(letters, blank and spaces)");
                        printf("%-12s %s\n", "-f", "Does not make distinction between upper and lower case characters");
                        printf("%-12s %s\n", "-r", "Sorts in reverse order");
                        printf("%-12s %s\n", "-B", "Uses bubble sort sorting algorithm");
                        printf("%-12s %s\n", "-h", "Prints this help message");
                        exit(1);
                        break;
                }
            }
        }
    }
    if(reverse)
        cmp_func = &strcmp_rev;
    if(fold)
        cmp_func = &stricmp;
    if(numeric)
        cmp_func = &numcmp;
    if(directory)
        cmp_func = &dircmp;

    if(numeric && reverse)
        cmp_func = &numcmp_rev;
    if(directory && reverse)
        cmp_func = &dircmp_rev;
    if(fold && reverse)
        cmp_func = &stricmp_rev;
    if(fold && reverse && directory)
    {
        cmp_func = &dircmp_rev_f;
    }
    else if(fold && directory)
        cmp_func = &dircmp_f;

    #define MAX_LINES 5000
    char buffer[512];
    char *lines[MAX_LINES] = {NULL};
    size_t index = 0;
    while(fgets(buffer, 512, stdin))
    {
        lines[index] = malloc(sizeof(char)*512);
        strcpy(lines[index++],buffer);
        if(index >= MAX_LINES)
        {
            // We'll not be able to read the next line
            break;
        }
    }
    //printf("=====%u=====\n",index);
    // Sort and display the result
    (*sort_alg)(lines, index, cmp_func, &swapstr);
    for(int i = 0; i < index; i++)
    {
        printf("%s", lines[i]);
        free(lines[i]);
    }
}
// NOTE: A bug
// A single line is not getting printed
/*
Alpha
bravo
alpha
azkaban
arthur
beast
Bear
Bat
zaphod
ford
mouse
Ant
armin
Elret
kazad dum
sauron
*/
// No newlines before or after the first and the last lines
// It was working but because there was no newline after the last line, the program was not printing it correctly