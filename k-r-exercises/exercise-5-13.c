/* Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is set to 10, let us say, but it can be changed by an
 * optional argument so that tail -n prints the last n lines. The program should
 * behave rationally no matter how unreasonable the input or the value of n.
 * Write the program so it makes the best use of available storage; lines should
 * be stored as in the sorting program of Section 5.6, not in a two-dimensional
 * array of fixed size. */

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 8
char *getline(size_t *size)
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

typedef struct node {
    char *line;
    struct node *next;
    struct node *prev;
} node;


int main(int argc, char *argv[])
{
    if(argc !=2)
    {
        printf("Usage: ./exercise-5-13 -n\n");
        exit(12);
    }
    if(argv[1][0] != '-')
    {
        printf("Usage: ./exercise-5-13 -n\n");
        printf("Example: ./exercise-5-13 -5\n");
        exit(12);
    }
    char *end;
    int numStations = strtol(&argv[1][1], &end, 10);

    if (end == &argv[1][1]) {
        printf("%s\n", "Please enter a valid number");
        exit(2);
    }
    if (numStations < 0) {
        printf("%s\n", "Please enter a valid number");
        exit(1);
    }
    size_t buff_length = 0;
    char *buff;
    node *head = NULL, *sen = NULL;
    for (;;) {
        buff = getline(&buff_length);
        if(!buff_length)
            break;
        if (!head) {
            head = malloc(sizeof(node));
            if (!head) exit(10);
            head->next = NULL;
            head->prev = NULL;
            head->line = buff;
            sen = head;
        }
        else {
            sen->next = malloc(sizeof(node));
            if (!sen->next) exit(11);
            sen->next->next = NULL;
            sen->next->prev = sen;
            sen->next->line = buff;
            sen = sen->next;
        }
    }
    int i = 0;
    node *s2 = NULL;
    while(sen)
    {
        if(i < numStations) 
        {
            s2 = sen;
            sen = sen->prev;
        }
        else
            break;
        i++;
    }
    while(s2)
    {
        printf("%s", s2->line);
        s2 = s2->next;
    }
    node *tmp;
    // Free the allocated memory
    while(head)
    {
        tmp = head;
        head = head->next;
        free(tmp->line);
        free(tmp);
    }
}
