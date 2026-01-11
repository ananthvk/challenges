#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This program prints the count of all words in the given text
// I have used a tree like structure to store and find words, more specifically
// a binary search tree Where the value of the left node is smaller than the
// parent node and the value of the right node is greater than the parent node

typedef struct node {
    char *word;
    struct node *left;
    struct node *right;
    int count;
} node;
typedef enum status { END_OF_FILE, NULL_BUFFER, WORD } status;

#define MAX_WORD_SIZE 100

// Get a single word into the given buffer
status get_word(char *buffer, size_t buffer_size);
node *add_tree(node *root, char *word);
void print_tree(node *root);
void free_tree(node *root);

int main(void)
{
    struct node *root = NULL;
    status s;
    char buffer[MAX_WORD_SIZE] = {'\0'};
    for (;;) {
        s = get_word(buffer, MAX_WORD_SIZE);
        if (s == END_OF_FILE) break;
        if (s == WORD) {
            root = add_tree(root, buffer);
        }
    }
    print_tree(root);
    free_tree(root);
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
        ;
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

node *add_tree(node *root, char *word)
{
    int val;
    if (root == NULL) {
        root = malloc(sizeof(node));
        if (!root) {
            printf("Couldn't allocate memory for node");
            // May be due to some memory issue
            return NULL;
        }
        // +1 for storing the null character
        root->word = malloc(sizeof(char) * (strlen(word) + 1));
        if (!root) {
            printf("Couldn't allocate memory for word in node");
            return NULL;
        }
        strcpy(root->word, word);
        root->count = 1;
        root->left = NULL;
        root->right = NULL;
    }
    /*
    if (!root->word) {
        // The node does not have a valid word
        return NULL;
    }
    */
    else if ((val = strcmp(word, root->word)) > 0) {
        // The new word is greater than the old word
        root->right = add_tree(root->right, word);
    }
    else if (val < 0) {
        // The new word is smaller than the old word
        root->left = add_tree(root->left, word);
    }
    else {
        // The word is same as this node's word
        // increase count
        root->count++;
    }
    return root;
}

void print_tree(node *root)
{
    if (root) {
        // print the left half first
        print_tree(root->left);
        // print the contents of this node
        printf("%3d %s\n", root->count, root->word);
        // print the right half next
        print_tree(root->right);
    }
}

void free_tree(node *tree)
{
    if (tree) {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree->word);
        free(tree);
    }
}
