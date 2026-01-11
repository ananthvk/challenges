/* Exercise 6-4. Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence. Precede each word by
 * its count. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 512
// My method
// 1. Get all the words from the input
// 2. Store all the words and it's frequency in a binary tree
// 3. When adding a node in the binary tree, also add the node to a global
// linked list
// 4. Sort the linked list in non-increasing order
// 5. Display the linked list
//
struct Node {
    char *word;         // Pointer to a word
    int count;          // To count the occurrences of the word
    struct Node *next;  // For the linked list
    struct Node *prev;  // For the linked list

    // Pointer in the binary tree
    struct Node *left;
    struct Node *right;
};

typedef struct Node Node;

Node *node_llist = NULL;
Node *node_head = NULL;

int is_word_separator(const int ch)
{
    if (ch == EOF) return 0;
    return !isalnum(ch);
}

int get_word(char *buffer, int n, int *line_number)
{
    int buffer_index = 0;
    int ch;
    static int line_number__ = 1;  // Since lines start from 1

    // Check if size is 0
    if (n == 0) {
        if (line_number) *line_number = line_number__;
        return 0;
    }
    // Skip all word separators
    while (is_word_separator(ch = getchar()))
        if (ch == '\n') line_number__++;

    if (ch == EOF) {
        buffer[buffer_index] = '\0';
        if (line_number) *line_number = line_number__;
        return EOF;
    }
    buffer[buffer_index++] = (char)ch;

    while (buffer_index < (n - 1)) {
        ch = getchar();
        if (ch == EOF) break;
        if (ch == '\n') line_number__++;
        if (is_word_separator(ch)) break;
        buffer[buffer_index++] = (char)ch;
    }
    buffer[buffer_index] = '\0';
    if (line_number) *line_number = line_number__;
    return buffer_index;
}

Node *node_create(void)
{
    // Creates a new node, initialize it to default values and then return it
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory error\n");
        exit(0x128);
    }
    new_node->word = NULL;
    new_node->count = 0;

    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void node_insert(Node *first, Node *second)
{
    // appends second to first i.e. sets first->next to second
    first->next = second;
}

Node *tree_create(Node *root, char *word)
{
    // Adds the word to the binary tree and returns the the pointer root, or if
    // root is null, returns the pointer to the newly created node
    int cmp = 0;
    if (root == NULL) {
        root = node_create();

        root->word = malloc(sizeof(char) * (strlen(word) + 1));
        if (!root->word) {
            printf("Memory error\n");
            exit(0x256);
        }
        root->count = 1;
        strcpy(root->word, word);
        if (!node_llist) {
            node_llist = root;
            node_head = root;
            node_llist->next = NULL;
            node_llist->prev = NULL;
        }
        else {
            node_llist->next = root;
            node_llist->prev = node_llist;
            node_llist = root;
        }
    }
    else if ((cmp = strcmp(word, root->word)) > 0) {
        // Add to the right as word is greater than root
        root->right = tree_create(root->right, word);
    }
    else if (cmp < 0) {
        root->left = tree_create(root->left, word);
    }
    else {
        root->count++;
    }
    return root;
}

void tree_print(Node *root)
{
    if (root) {
        tree_print(root->left);
        if (root->count) printf("%d: %s\n", root->count, root->word);
        tree_print(root->right);
    }
}

void tree_free(Node *root)
{
    if (root) {
        tree_free(root->left);
        tree_free(root->right);
        free(root->word);
        free(root);
    }
    node_llist = NULL;
    node_head = NULL;
    // Frees the tree
}

void print_words_in_desc_order(Node *list_head)
{
    if (!list_head) return;
    Node *in_sentry = list_head;
    Node *out_sentry = list_head;
    Node *max_val = NULL;

    int tmp_count = 0;
    char *tmp_word = NULL;

    while(out_sentry)
    {
        in_sentry = out_sentry;
        max_val = in_sentry;

        while(in_sentry)
        {
            if(in_sentry->count > max_val->count)
                max_val = in_sentry;

            in_sentry = in_sentry->next;
        }
        // Swap
        printf("%d: %s\n", max_val->count, max_val->word);
        tmp_count = max_val->count;
        tmp_word = max_val->word;

        max_val->count = out_sentry->count;
        max_val->word = out_sentry->word;

        out_sentry->count = tmp_count;
        out_sentry->word = tmp_word;
        
        out_sentry = out_sentry->next;
    }
}

int main()
{
    int length;
    char buffer[MAX_WORD_LENGTH];
    int line_no = 0;
    Node *root = NULL;
    while ((length = get_word(buffer, MAX_WORD_LENGTH, &line_no)) != EOF) {
        root = tree_create(root, buffer);
    }
    // tree_print(root);
    /* while(node_head)
     * {
     *
     *     printf("%d: %s\n", node_head->count, node_head->word);
     *     node_head = node_head->next;
     * } */
    print_words_in_desc_order(node_head);
    /*
    while(node_head)
    {

        printf("%d: %s\n", node_head->count, node_head->word);
        node_head = node_head->next;
    }
    */
    tree_free(root);
}
