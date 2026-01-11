#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE_SIZE 1000

int s_atoi(char *s, int *var)
{
    char *beg = s;
    while (*s) {
        if (!isdigit(*s)) return 0;
        s++;
    }
    *var = atoi(beg);
    return 1;
}

int rotate(char ch, int pos)
{
    // Rotates the character pos times
    // If the character is not an alphabet, return the character
    if(!isalpha(ch))
        return ch;

    if(isupper(ch))
    {
        return 'A' + ((ch - 'A' + pos)%26);
    }
    else
    {
        return 'a' + ((ch - 'a' + pos)%26);
    }
}

size_t getline(char *buffer, size_t n)
{
    char *beg = buffer;
    int ch;
    while((size_t)(buffer - beg) < (n-1))
    {
        ch = getchar();
        if(ch == EOF)
            break;
        *buffer++ = (char)ch;
        if(ch == '\n')
            break;
    }
    *buffer = '\0';
    return (size_t)(buffer - beg);
}

int main(int argc, char *argv[])
{
    // Pseudocode
    // 1. Check if there only one argument and it is a valid number (exluding
    // the program name)
    //    If not, display the usage of the program
    //    Exit
    // 2. Get the plaintext from the user
    // 3. For each character of the plain text
    //          If the character is an alphabet, rotate it accordingly according
    //          to its case.
    // 4. Display the cipher text
    //
    char buffer[MAX_LINE_SIZE] = {'\0'};
    int key = 0;

    // Check if there is only one argument
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (!s_atoi(argv[1], &key)) {
        printf("Invalid key, key must be a valid positive integer\n");
        printf("Usage: ./caesar key\n");
        return 1;
    }

    printf("plaintext:  ");

    // Get a single line from the input
    getline(buffer, MAX_LINE_SIZE);
    printf("ciphertext: ");

    char *buff = buffer;
    while(*buff)
    {
        putchar(rotate(*buff, key));
        buff++;
    }
}
