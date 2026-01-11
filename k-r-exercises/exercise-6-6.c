/* Exercise 6-6. Implement a simple version of the #define processor (i.e., no
 * arguments) suitable for use with C programs, based on the routines of this
 * section. You may also find getch and ungetch helpful */
// Author: Shankar
// Date: 17-September-2022
// +-----------------------------------------------------------------+
// |                                                                 |
// |  Requirements                                                   |
// |  --------------                                                 |
// |                                                                 |
// |  The program should replace all occurrences of the macro NAME   |
// |  with the VALUE, while ignoring strings, characters and comments|
// |                                                                 |
// |  1. Preprocessor directives are of the form #define NAME VALUE  |
// |  2. NAME must be a character from [A-Za-z0-9_]                  |
// |  3. NAME must not start with a digit.                           |
// |  4. Both NAME and VALUE must be present on the same line.       |
// |  5. In case of any errors, the program should report it along   |
// |     with the line number on which the error occured.            |
// |  6. The program must not replace complex #defines, such as      |
// |     define with args.                                           |
// +-----------------------------------------------------------------+

// +------------------------------------------------------+
// |                                                      |
// |  Overview                                            |
// |  ------------                                        |
// |                                                      |
// |  1. Get all the words from the file/stdin            |
// |  2. A word is a group of alphanumeric characters     |
// |     including underscore or a special character      |
// |  3. For example, the below line will be interpreted  |
// |     as # define MAX_LINES 1 0 0 0 \n                 |
// |     #define MAX_LINES 1000                           |
// |  4. Check if the line is a preprocessor directiveon. |
// |  5. Add the NAME and VALUE to the hash table.        |
// |  6. For each word, replace the word if it is present |
// |     in the hash table.                               |
// +------------------------------------------------------+

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_BUFFER_SIZE 16

void *safe_malloc(size_t size);
void *safe_realloc(void *mem, size_t size);
char *get_a_line(size_t *size);
void exit_handler(const char *message, int exit_code);
char *tokenize(const char *line, size_t *size);
#define TABLE_SIZE 5  // 100003  // Nearest prime around 100k

struct h_list {
    struct h_list *next;
    struct h_list *prev;
    char *key;
    char *value;
};

typedef struct h_list h_list;

h_list *hash_table[TABLE_SIZE] = {NULL};

h_list *h_list_create(const char *key, const char *value);
h_list *h_list_append(h_list *parent, const char *key, const char *value);
// Frees a single node
void h_list_free_single(h_list *hl);
// Frees the entire list starting from root
void h_list_free(h_list *root);

void table_store(const char *key, const char *value);
// Look up the key in the table
h_list *table_lookup(const char *key);
// Really inefficient, TODO: Create a slab/arena allocator
void table_free(void);
// Removes the entry in the table (if present). Returns 1 if removal is
// successful
int table_remove(const char *key);
unsigned int hash(const char *s);


char *duplicatestr(const char *s)
{
    // +1 for the \0 character
    char *buffer = safe_malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(buffer, s);
    return buffer;
}

void *safe_malloc(size_t n)
{
    void *ptr = malloc(n);
    if (!ptr) {
        printf(
            "Memory allocation failed! Check if your PC ran out of memory\n");
        exit(2);
    }
    return ptr;
}

void *safe_realloc(void *memory, size_t new_size)
{
    void *ptr = realloc(memory, new_size);
    if (!ptr) {
        printf(
            "Memory reallocation failed! Check if your PC ran out of memory\n");
        free(memory);
        exit(2);
    }
    return ptr;
}

h_list *h_list_create(const char *key, const char *value)
{
    h_list *new_node = safe_malloc(sizeof(h_list));
    new_node->key = duplicatestr(key);
    new_node->value = duplicatestr(value);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}
h_list *h_list_append(h_list *parent, const char *key, const char *value)
{
    // This is a modified version of append to list
    // This function creates a new node if the key does not appear in the list
    // otherwise it updates that node
    if (parent) {
        // Go to the last node
        while (parent->next) {
            if (strcmp(key, parent->key) == 0) {
                parent->value = safe_realloc(parent->value, strlen(value) + 1);
                strcpy(parent->value, value);
                return parent;
            }
            parent = parent->next;
        }

        // To test if the first node has the same key as the given key
        if (strcmp(key, parent->key) == 0) {
            parent->value = safe_realloc(parent->value, strlen(value) + 1);
            strcpy(parent->value, value);
            return parent;
        }
        h_list *created_node = h_list_create(key, value);
        parent->next = created_node;
        created_node->prev = parent;
        return created_node;
    }
    else {
        return h_list_create(key, value);
    }
}
void h_list_free_single(h_list *hl)
{
    if (hl) {
        free(hl->key);
        free(hl->value);
        hl->key = NULL;
        hl->value = NULL;
        free(hl);
    }
}
void h_list_free(h_list *root)
{
    h_list *tmp;
    while (root) {
        tmp = root;
        root = root->next;
        h_list_free_single(tmp);
    }
}

void table_store(const char *key, const char *value)
{
    unsigned int hash_val = hash(key);
    h_list *ins_pos = hash_table[hash_val];
    if (!ins_pos) {
        hash_table[hash_val] = h_list_create(key, value);
    }
    else {
        h_list_append(hash_table[hash_val], key, value);
    }
}


void table_store_fixed(const char *key, size_t m, const char *value, size_t n)
{
    // Stores the first m characters of key and first n characters of value
    char *ky = duplicatestr(key); 
    char *val = duplicatestr(value); 

    if(m <= strlen(key))
        ky[m] = '\0';
    if(n <= strlen(value))
        val[n] = '\0';

    unsigned int hash_val = hash(ky);
    h_list *ins_pos = hash_table[hash_val];
    if (!ins_pos) {
        hash_table[hash_val] = h_list_create(ky, val);
    }
    else {
        h_list_append(hash_table[hash_val], ky, val);
    }
    free(ky);
    free(val);
}

h_list *table_lookup(const char *key)
{
    if (key == NULL) return NULL;
    unsigned int hash_val = hash(key);
    h_list *node = hash_table[hash_val];
    while (node) {
        if (strcmp(key, node->key) == 0) return node;
        node = node->next;
    }
    return NULL;
}

unsigned int hash(const char *s)
{
    // The djb2 hash function
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned int hash_val = 5381;
    while (*s) {
        hash_val = hash_val * 33 + (unsigned)*s;
        s++;
    }
    return hash_val % TABLE_SIZE;
}

void table_free(void)
{
    // Really inefficient :/ Use a slab allocator
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i]) h_list_free(hash_table[i]);
    }
}

void table_find(const char *key)
{
    h_list *node = table_lookup(key);
    if (!node)
        printf("%-12s : %s\n", key, "Key Error: Such a key does not exist");
    else
        printf("%-12s : %s\n", key, node->value);
}

int table_remove(const char *key)
{
    unsigned int calc_hash = hash(key);
    h_list *node = table_lookup(key);
    if (!node) return 0;
    // Unlink the node
    h_list *next_node = node->next;
    h_list *prev_node = node->prev;

    if (next_node == NULL && prev_node == NULL) {
        // There is a single node in the list
        hash_table[calc_hash] = NULL;
    }

    if (prev_node != NULL) {
        prev_node->next = next_node;
    }
    if (next_node != NULL) {
        if (prev_node == NULL) {
            // This is the first node of the list
            next_node->prev = NULL;
            hash_table[calc_hash] = next_node;
        }
        else {
            next_node->prev = prev_node;
        }
    }
    h_list_free_single(node);
    return 1;
}
 void exit_handler(const char *message, int exit_code)
{
    printf("%s", message);
    exit(exit_code);
}


char *get_a_line(size_t *size)
{
    // Get a single line from standard input into a growable buffer
    char *buffer = safe_malloc(DEFAULT_BUFFER_SIZE);
    size_t allocated_buffer_size = DEFAULT_BUFFER_SIZE;
    size_t buffer_size = 0;
    int ch;
    // Check that size is non zero as unsgined 0-1 wraps around
    if (size == 0) return NULL;

    while (buffer_size < (allocated_buffer_size - 1)) {
        // -1 to hold the \0 character
        ch = getchar();
        if (ch == EOF) {
            break;
        }
        buffer[buffer_size++] = (char)ch;
        if (ch == '\n') break;

        // Double allocated_buffer_size if the next character to be read will
        // overflow it
        if (buffer_size == (allocated_buffer_size - 1)) {
            allocated_buffer_size *= 2;
            buffer = safe_realloc(buffer, allocated_buffer_size);
        }
    }
    buffer[buffer_size] = '\0';
    if (size) *size = buffer_size;
    return buffer;
}

char *tokenize(const char *line, size_t *size)
{
    // Returns a pointer to the first token of the word and sets size to the
    // size of the token
    static char *internal_line = NULL;

    static char *lastchar = NULL;
    static int unget_required = 0;

    if (line != NULL) {
        internal_line = line;
    }
    if (unget_required) {
        unget_required = 0;
        if(size) *size = 1;
        return lastchar;
    }
    char *beg = internal_line;
    while (*internal_line) {
        if (!isalnum(*internal_line) && *internal_line != '_') {
            if (size) *size = internal_line - beg;

            unget_required = 1;
            lastchar = internal_line;

            internal_line++;
            return beg;
        }
        internal_line++;
    }
    return NULL;
}

void print_tok(char *tok, size_t tok_size)
{
    printf("%.*s", (int)tok_size, tok);
    // for(int i = 0; i < tok_size; i++) putchar(*(tok+i));
}

void process_token(char *token, size_t token_size)
{
    /*
    if (token_size <= 0) return;

    if (*token == '\n')
        printf("[1: \\n]\n");
    else if (*token == '\r')
        printf("[1: \\r]\n");
    else if (*token == '\t')
        printf("[1: \\t]\n");
    else if (*token == ' ')
        printf("[1: SPACE]\n");
    else {
        printf("[%d: ", token_size);
        print_tok(token, token_size);
        printf("]\n");
    }
    */

    // Find the pattern #define NAME VALUE\n
    // There can be any amount of space between define and NAME, NAME and VALUE
    // and VALUE and the newline
    // There should not be any spaces between # and define
    char *token2 = NULL;
    size_t token2_size = 0;

    char *tok = duplicatestr(token);
    if(token_size <= strlen(token))
        tok[token_size] = '\0';
    //printf("<%s>\n", tok);
    h_list *lookup = table_lookup(tok);
    free(tok);

    if(lookup)
    {
        //printf("FOUND\n");
        printf("%s",lookup->value);
        return;
    }

    if(token_size == 1)
    {
        if(*token == '#')
        {
            token = tokenize(NULL, &token_size);
            // if(token_size == 6)
            if(strncmp(token, "define", 6) == 0)
            {
                // Skip whitespace
                tokenize(NULL, NULL);

                // Read name
                token = tokenize(NULL, &token_size);
                //print_tok(token, token_size);

                // Skip whitespace
                tokenize(NULL, NULL);

                // Read value
                token2 = tokenize(NULL, &token2_size);
                //printf(" VALUE:");
                // print_tok(token, token_size);
                table_store_fixed(token, token_size, token2, token2_size);

                printf("#define");
                printf(" ");
                print_tok(token, token_size);
                printf(" ");
                print_tok(token2, token2_size);
            }
            else
            {
                putchar('#');
                print_tok(token, token_size);
            }
        }
        else
        {
            putchar(*token);
        }
    }
    else
    {
        print_tok(token, token_size);
    }
}
int main()
{
    size_t size = 0;
    char *buffer = NULL;
    char *tok;
    size_t tok_size = 0;
    int line_index = 0;
    while (1) {
        buffer = get_a_line(&size);
        line_index++;

        if (size != 0) {
            tok = tokenize(buffer, &tok_size);
            // printf("(%d)", line_index);
            process_token(tok, tok_size);
            while ((tok = tokenize(NULL, &tok_size))) {
                // printf("(%d)", line_index);
                process_token(tok, tok_size);
            }
            /*
            print_tok(tok, tok_size);
            while((tok = tokenize(NULL, &tok_size)))
            {
                print_tok(tok, tok_size);
            }
            */
            free(buffer);
        }
        else {
            free(buffer);
            break;
        }
    }
    table_free();
}
// What I learnt?
// 1. There can be weird bugs such as in the process token function, wherein a
// space or newline character was printed twice
// 2. The fix is to use if-else if-else ladder instead of plain ifs

// TODO:
// This program is not fully complete and there are a few more features which are necessary.
// 1. Does not handle quoted strings/chars in define.
// 2. Does not ignore #define and replacement in comments/strings
// 3. This code can be organized in a much better way
// 4. Display syntax error when the define is not correct as in the middle of lines, not having a single identifier after define, etc
// 5. Fix the bug when define replaces spaces, such as when passing this program source file using <, all spaces are replaced by "such"
//    due to the line #defines, such as
//    Rectify this error