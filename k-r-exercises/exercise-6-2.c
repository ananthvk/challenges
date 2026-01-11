/*Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be
set from the command line.*/

// Algorithm
// =========
// 1. Get all identifiers from the program (exclude strings and comments)
// 2. Check if the identifier is a variable.
//      I have simplified this part and considered a variable as any word other than keywords
//      This means that function names, structure names and others will be considered as variable names
// 3. Create a node with the word and add it to the BST
// 4. If the word is a substring of the root node to which this word is to be inserted, insert the node to another tree

// Example:
// ┌─────────────────────────────────────────────────────────────────┐
// │                                                                 │
// │                                    │  fish  │                   │
// │                                    │        │                   │
// │   N = 3                            │        │                   │
// │   https://asciiflow.com/#/         │        │                   │
// │                                    │        │                   │
// │                                    │        │                   │
// │                                    │        │                   │
// │                                    │        │                   │
// │                                    │        │                   │
// │                                    │        │                   │
// │                  │ dogg│   ────────┘        └─────────  goat    │
// │                  │     │                                        │
// │                  │  │  │                                        │
// │                  │  │  │                                        │
// │                  │  │  │                                        │
// │                  │  │  │                                        │
// │                  │  │  │                                        │
// │                  │  │  │                                        │
// │    cat    ───────┘  │  └────── eat                              │
// │                     │                                           │
// │                     │                                           │
// │                     ├────────┐                                  │
// │                     │        │                                  │
// │                     │        │                                  │
// │                     │        │                                  │
// │           doga──────┘        └───────dogi                       │
// │              │                       │ │                        │
// │              │                       │ │                        │
// │              │                       │ │                        │
// │              │                       │ │                        │
// │              │               dogd ───┘ └──────dogj              │
// │              └──────dogb                                        │
// │                                                                 │
// │                                                                 │
// │                                                                 │
// └─────────────────────────────────────────────────────────────────┘

// In short, if the word in the node to be inserted has that many same chars as its parent node, insert it into another tree

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
int n;

typedef struct Node
{
    char *word;
    struct Node *left;
    struct Node *right;
    // struct Node *subtree_left;
    // struct Node *subtree_right;
    struct Node *sub_left;
    struct Node *sub_right;
} Node;

int are_first_n_chars_identical(const char *s, const char *t, int n_chars)
{
    for(int i = 0; i < n_chars; i++)
    {
        if(s[i] != t[i])
            return 0;
        if(s[i] == '\0' || t[i] == '\0')
            return 0;
    }
    return 1;
}

Node *add_subtree(struct Node *node, char *word)
{
    int expr;
    // Adds the word to the tree and returns the node which was passed
    // or if node is null, it returns the new node.
    if(node == NULL)
    {
        node = malloc(sizeof(struct Node));
        if(!node)
        {
            printf("Error while creating subtree node ! memory error\n");
            return NULL;
        }
        node->word = malloc(sizeof(char) * (strlen(word)+1)); // +1 is to accomodate the null character
        if(!node->word)
        {
            printf("Error while copying the word to subtree");
            return NULL;
        }
        node->right = NULL;
        node->left = NULL;
        strcpy(node->word, word);
        return node;
    }
    // TODO: Check that the word is not NULL
    else if((expr = strcmp(word, node->word)) > 0)
    {
        // Check if the word is bigger than that of the subtree node
        node->right = add_subtree(node->right, word);
    }
    else if(expr < 0)
    {
        // Check if the word is smaller than that of the subtree node
        node->left = add_subtree(node->left, word);
    }
    // No need to check if the word is same as that of the node
    return node;
}

Node *add_tree(Node *node, char *word)
{
    int expr = 0;
    // Adds the word to the tree and returns the node which was passed
    // or if node is null, it returns the new node.
    if(node == NULL)
    {
        node = malloc(sizeof(Node));
        if(!node)
        {
            printf("Error while creating node ! memory error\n");
            return NULL;
        }
        node->word = malloc(sizeof(char) * (strlen(word)+1)); // +1 is to accomodate the null character
        if(!node->word)
        {
            printf("Error while copying the word");
            return NULL;
        }
        node->right = NULL;
        node->left = NULL;
        node->sub_right = NULL;
        node->sub_left = NULL;
        strcpy(node->word, word);
        return node;
    }
    // Check that the word is not NULL
    else if(are_first_n_chars_identical(node->word, word, n))
    {
        // Check if the first n characters of the word are same as that of the node
        if(strcmp(word, node->word) > 0)
        {
            node->sub_right = add_subtree(node->sub_right, word);
        }
        if(strcmp(word, node->word) < 0)
        {
            node->sub_left = add_subtree(node->sub_left, word);
        }
    }
    else if((expr = strcmp(word, node->word)) > 0)
    {
        // Check if the word is bigger than that of the node
        node->right = add_tree(node->right, word);

    }
    else if(expr < 0)
    {
        node->left = add_tree(node->left, word);
        // Check if the word is smaller than that of the node
    }
    // No need to check if the word is same as that of the node
    return node;
}

typedef enum status { END_OF_FILE, NULL_BUFFER, WORD } status;

#define MAX_WORD_SIZE 100

void print_subtree(struct Node *node)
{
    if(node){
        print_subtree(node->left);
        printf("%s\n", node->word);
        print_subtree(node->right);
    }
}
void print_tree(Node *root, int to_print)
{
    if (root) {
        // print the left half first
        print_subtree(root->sub_left);
        // print the contents of this node
        if(to_print || root->sub_left || root->sub_right)
            printf("%s\n", root->word);
        // print the right half next
        print_subtree(root->sub_right);

        print_tree(root->left, 0);
        print_tree(root->right, 0);
    }
}

void free_subtree(struct Node *node)
{
    if (node) {
        free_subtree(node->left);
        free_subtree(node->right);
        free(node->word);
        free(node);
    }
}


void free_tree(Node *tree)
{
    if (tree) {
        free_tree(tree->left);
        free_tree(tree->right);

        free_subtree(tree->sub_left);
        free_subtree(tree->sub_right);

        free(tree->word);
        free(tree);
    }
}



int is_invalid_char(int ch)
{
    if (ch == EOF) return 0;
    return ch == ' ' || !isalnum(ch);
}

status get_word(char *buffer, size_t buffer_size)
{
    size_t buffer_index = 0;
    int ch;

    if (!buffer) return NULL_BUFFER;

    // Skip whitespaces and special chars
    while (is_invalid_char(ch = getchar()))
    {
        if(ch == '/')
        {
            ch = getchar();
            if(ch == '/')
            {
                while((ch = getchar())) if(ch == '\n') break;
            }
            else
            {
                ungetc(ch, stdin);
            }
        }
    }
    if (ch == EOF) return END_OF_FILE;
    // Add ch to the buffer
    buffer[buffer_index++] = ch;
    // Get the rest of the word
    // We can read atmost buffer_size-1 chars to make one space free for the
    // null character
    while (buffer_index < (buffer_size - 1)) {
        ch = getchar();
        if (ch == EOF) {
            break;
        }
        if (is_invalid_char(ch)) {
            ungetc(ch, stdin);
            break;
        }
        buffer[buffer_index++] = ch;
    }
    buffer[buffer_index] = '\0';
    return WORD;
}



int main(int argc, char *argv[])
{
    if(argc == 2)
        n = atoi(argv[1]);
    else if(argc != 2)
    {
        printf("Usage: ./exercise-6-2 n\n");
        printf("n is the number of starting chars\n");
        n = 2;
    }
    struct Node *root = NULL;
    status s;
    char buffer[MAX_WORD_SIZE] = {'\0'};
    for (;;) {
        s = get_word(buffer, MAX_WORD_SIZE);
        if (s == END_OF_FILE) break;
        if (s == WORD) {
            root = add_tree(root, buffer);
        }
    }
    // :/ - this does not work as expected --- there are too many memory bugs
    // Rewrite this program again
    print_tree(root, 0);
    free_tree(root);
}