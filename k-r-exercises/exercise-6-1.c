#include <ctype.h>
#include <stdio.h>
#include <string.h>

// This preprocessor directive makes it possible to not declare the size of the
// keytable as it'll be calculated automatically
#define NUMBER_OF_KEYWORDS (sizeof(keytable) / sizeof(struct key))
// Maximum size of a single word
#define MAX_WORD_SIZE 256

struct key {
    char *word;
    int count;
};

// List of all 32 keywords in C
struct key keytable[] = {
    {"auto", 0},     {"break", 0},    {"case", 0},     {"char", 0},
    {"const", 0},    {"continue", 0}, {"default", 0},  {"do", 0},
    {"double", 0},   {"else", 0},     {"enum", 0},     {"extern", 0},
    {"float", 0},    {"for", 0},      {"goto", 0},     {"if", 0},
    {"int", 0},      {"long", 0},     {"register", 0}, {"return", 0},
    {"short", 0},    {"signed", 0},   {"sizeof", 0},   {"static", 0},
    {"struct", 0},   {"switch", 0},   {"typedef", 0},  {"union", 0},
    {"unsigned", 0}, {"void", 0},     {"volatile", 0}, {"while", 0},
};
// TODO: Handle multiline comments

typedef enum Status{
    NUMBER,
    IDENTIFIER,
    END_OF_FILE,
    ERR_INVALID_BUFFER
} Status;

void print_char(const char *s, int ch)
{
    printf("%s:", s);
    if (ch == '\n') {
        putchar('\\');
        putchar('n');
    }
    else if (ch == '\t') {
        putchar('\\');
        putchar('t');
    }
    else if (ch == '\r') {
        putchar('\\');
        putchar('r');
    }
    else if (ch == ' ') {
        putchar('_');
    }
    else
        putchar(ch);
    printf("\n");
}

Status get_word(char *buffer, size_t wlimit)
{
    // Get a single word into the buffer with max size equal to wlimit-1
    // As one empty space is required for storing a null character
    // A word is defined as a sequence of characters, numbers or underscores
    // beginning with a letter or underscore
    int ch;
    size_t buffer_index= 0;
    if(!buffer)
    {
        printf("Invalid buffer, buffer is NULL\n");
        return ERR_INVALID_BUFFER;
    }

    while ((ch = getchar()) != EOF) {
        // Skip whitespaces and special characters
        // This loop stops when the first non-whitespace, non-special character
        // is found
        // Check for comments
        if(ch == '/')
        {
            ch = getchar();
            if(ch == '/')
            {
                // Found a single line comment
                while((ch = getchar()) !=EOF) if(ch == '\n') break;
                // Ignore till end of line
            }
            else if(ch == '*')
            {
                // Found a multiline comment
                // Ignore till the next /
                while((ch = getchar()) !=EOF) if(ch == '/') break;
            }
            else
            {
                // Something else
                ungetc(ch, stdin);
            }
        }
        if (isspace(ch) || (!isalnum(ch)))
            continue;
        else
            break;
    }
    // We have reached the end of the file, no more words
    if (ch == EOF) {
        buffer[0] = '\0';
        return END_OF_FILE;
    }
    // Check if the first non blank / special character is an underscore or a
    // letter. If the string starts with a digit, it is not a valid identifier
    if (isdigit(ch)) {
        buffer[0] = '\0';
        return NUMBER;
    }
    // Add the current character to the buffer only if it is an underscore / letter
    if(ch == '_' || isalnum(ch))
        buffer[buffer_index++] = ch;
    // Consume the rest of the characters
    while (buffer_index < (wlimit - 1)) {
        ch = getchar();
        if (ch == EOF) break;
        // If the current character is not a number or letter or underscore
        // Unget the character, and don't add it to the word
        if (!isalnum(ch)) {
            if (ch != '_') {
                ungetc(ch, stdin);
                break;
            }
        }
        buffer[buffer_index++] = ch;
    }
    buffer[buffer_index] = '\0';
    return IDENTIFIER;
}

// Performs binary search to find the given word in the table 
// The table must be sorted. This function returns the index of the element which was found
// or -1, if the element was not found
int binary_search(char *word, struct key table[], int n)
{
    int lb = 0, ub = n-1, mid = 0;
    int outcome = 0;
    while(lb <= ub)
    {
        // To prevent integer overflow when both lb and ub are extremely large
        mid = lb + (ub - lb)/2;
        if((outcome = strcmp(word, table[mid].word)) > 0)
        {
            // Word is larger than middle word
            lb = mid + 1;
        }
        else if(outcome < 0)
        {
            // Word is smaller than middle element
            ub = mid - 1;
        }
        else
            // Word matches to the keyword
            return mid;
    }
    // The word was not found in the table
    return -1;
}

int main()
{
    char word[MAX_WORD_SIZE];
    Status status;
    int pos;
    while ((status = get_word(word, MAX_WORD_SIZE)) != END_OF_FILE) {
        if(status != NUMBER)
        {
            if((pos = binary_search(word, keytable, NUMBER_OF_KEYWORDS)) != -1)
            {
                // The word was found
                keytable[pos].count++;
            }
        }
    }
    // Print the count of each keyword
    printf("================ [ COUNT OF KEYWORDS ] ================\n");
    for(size_t i = 0; i < NUMBER_OF_KEYWORDS; i++)
    {
        // Print out only the non zero entries
        if(keytable[i].count)
            printf("%-12s %d\n", keytable[i].word, keytable[i].count);
    }
    printf("================ [ UNUSED KEYWORDS ] ================\n");
    for(size_t i = 0; i < NUMBER_OF_KEYWORDS; i++)
    {
        // Print out the unused keywords
        if(!keytable[i].count)
        {
            printf("%s, ", keytable[i].word);
        }
    }
    printf("\n");
    printf("================================\n");
}
