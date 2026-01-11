/*Exercise 6-2. Write a program that reads a C program and prints in
alphabetical order each group of variable names that are identical in the first
6 characters, but different somewhere thereafter. Don't count words within
strings and comments. Make 6 a parameter that can be set from the command
line.*/

// Algorithm
// =========
// 1. Get all identifiers from the program (exclude strings and comments)
// 2. Check if the identifier is a variable.
//      I have simplified this part and considered a variable as any word other
//      than keywords This means that function names, structure names and others
//      will be considered as variable names
// 3. Create a node with the word and add it to the BST
// 4. If the word is a substring of the root node to which this word is to be
// inserted, insert the node to another tree

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

// In short, if the word in the node to be inserted has that many same chars as
// its parent node, insert it into another tree

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utest.h"
int n = 0;

typedef struct Node {
    char *word;
    struct Node *left;
    struct Node *right;
    struct Node *subtree_left;
    struct Node *subtree_right;
} Node;

int are_first_n_chars_identical(const char *s, const char *t, int n_chars)
{
    for (int i = 0; i < n_chars; i++) {
        if (s[i] != t[i]) return 0;
        if (s[i] == '\0' || t[i] == '\0') return 0;
    }
    return 1;
}

Node *add_subtree(Node *node, char *word)
{
    int expr;
    // Adds the word to the tree and returns the node which was passed
    // or if node is null, it returns the new node.
    if (node == NULL) {
        node = malloc(sizeof(Node));
        if (!node) {
            printf("Error while creating subtree node ! memory error\n");
            return NULL;
        }
        node->word = malloc(
            sizeof(char) *
            (strlen(word) + 1));  // +1 is to accomodate the null character
        if (!node->word) {
            printf("Error while copying the word to subtree");
            return NULL;
        }
        node->right = NULL;
        node->left = NULL;
        node->subtree_right = NULL;
        node->subtree_left = NULL;
        strcpy(node->word, word);
        return node;
    }
    // TODO: Check that the word is not NULL
    else if ((expr = strcmp(word, node->word)) > 0) {
        // Check if the word is bigger than that of the subtree node
        node->subtree_right = add_subtree(node->subtree_right, word);
    }
    else if (expr < 0) {
        // Check if the word is smaller than that of the subtree node
        node->subtree_left = add_subtree(node->subtree_right, word);
        // ERROR: Change this line to make this program work
         //node->subtree_left = add_subtree(node->subtree_left, word);
    }
    // No need to check if the word is same as that of the node
    return node;
}

Node *add_tree(Node *node, char *word)
{
    int expr = 0;
    // Adds the word to the tree and returns the node which was passed
    // or if node is null, it returns the new node.
    if (node == NULL) {
        node = malloc(sizeof(Node));
        if (!node) {
            printf("Error while creating node ! memory error\n");
            return NULL;
        }
        node->word = malloc(
            sizeof(char) *
            (strlen(word) + 1));  // +1 is to accomodate the null character
        if (!node->word) {
            printf("Error while copying the word");
            return NULL;
        }
        node->right = NULL;
        node->left = NULL;
        node->subtree_right = NULL;
        node->subtree_left = NULL;
        strcpy(node->word, word);
        return node;
    }
    // Check that the word is not NULL
    else if (are_first_n_chars_identical(node->word, word, n)) {
        // Check if the first n characters of the word are same as that of the
        // node
        if (strcmp(word, node->word) > 0) {
            node->subtree_right = add_subtree(node->subtree_right, word);
        }
        if (strcmp(word, node->word) < 0) {
            node->subtree_left = add_subtree(node->subtree_left, word);
        }
    }
    else if ((expr = strcmp(word, node->word)) > 0) {
        // Check if the word is bigger than that of the node
        node->right = add_tree(node->right, word);
    }
    else if (expr < 0) {
        node->left = add_tree(node->left, word);
        // Check if the word is smaller than that of the node
    }
    // No need to check if the word is same as that of the node
    return node;
}
/*
Node *add_tree(Node *root, char *word)
{
    int val;
    if (root == NULL) {
        root = malloc(sizeof(Node));
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
        root->left = NULL;
        root->right = NULL;
    }
    else if(are_first_n_chars_identical(root->word, word, n))
    {
        // Check if the first n characters of the word are same as that of the
node printf("Contains: %s\n",word);
    }
    // if (!root->word) {
    //    // The node does not have a valid word
    //    return NULL;
    //}
    else if ((val = strcmp(word, root->word)) > 0) {
        // The new word is greater than the old word
        root->right = add_tree(root->right, word);
    }
    else if (val < 0) {
        // The new word is smaller than the old word
        root->left = add_tree(root->left, word);
    }
    return root;
}
*/

typedef enum status { END_OF_FILE, NULL_BUFFER, TXTWORD } status;

#define MAX_TXTWORD_SIZE 100

void print_tree(Node *root, int to_print)
{
    if (root) {
        // print the left half first
        print_tree(root->subtree_left, 1);
        print_tree(root->left, 0);
        // print the contents of this node
        if (to_print || root->subtree_right || root->subtree_left)
            printf("%s\n", root->word);
        // print the right half next
        print_tree(root->subtree_right, 1);
        print_tree(root->right, 0);
    }
}

void free_subtree(Node *sub_tree)
{
    // Frees a single subtree
    if (sub_tree) {
        free_subtree(sub_tree->subtree_left);
        free_subtree(sub_tree->subtree_right);

        free(sub_tree->word);
        free(sub_tree);
    }
}

void free_tree(Node *tree)
{
    if (tree) {
        free_tree(tree->right);
        free_tree(tree->left);

        free_subtree(tree->subtree_left);
        free_subtree(tree->subtree_right);

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
    while (is_invalid_char(ch = getchar())) {
        if (ch == '/') {
            ch = getchar();
            if (ch == '/') {
                while ((ch = getchar()))
                    if (ch == '\n') break;
            }
            else {
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
    return TXTWORD;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        if (strcmp("test", argv[1]) == 0) {
            exit(utest_main(argc, argv));
        }
        n = atoi(argv[1]);
    }
    if (argc != 2) {
        printf("Usage: ./exercise-6-2 n\n");
        printf("n is the number of starting chars\n");
        n = 2;
    }
    struct Node *root = NULL;
    status s;
    char buffer[MAX_TXTWORD_SIZE] = {'\0'};
    for (;;) {
        s = get_word(buffer, MAX_TXTWORD_SIZE);
        if (s == END_OF_FILE) break;
        if (s == TXTWORD) {
            root = add_tree(root, buffer);
        }
    }
    // :/ - this does not work as expected --- there are too many memory bugs
    // Rewrite this program again
    print_tree(root, 0);
    free_tree(root);
}

UTEST(test_tree, test_correct_insertion)
{
    n = 3;
    Node *root = NULL;
    root = add_tree(root, "hello");
    ASSERT_STREQ("hello", root->word);

    root = add_tree(root, "zello");
    ASSERT_NE(NULL, root->right);
    ASSERT_STREQ("zello", root->right->word);

    root = add_tree(root, "aello");
    ASSERT_NE(NULL, root->left);
    ASSERT_STREQ("aello", root->left->word);

    ASSERT_EQ(NULL, root->subtree_left);
    ASSERT_EQ(NULL, root->subtree_right);
    free_tree(root);
}

UTEST(test_tree, test_correct_insertion_multiple)
{
    n = 3;
    Node *root = NULL;
    root = add_tree(root, "the");
    ASSERT_STREQ("the", root->word);

    root = add_tree(root, "zuick");
    ASSERT_NE(NULL, root->right);
    ASSERT_STREQ("zuick", root->right->word);

    root = add_tree(root, "brown");
    ASSERT_NE(NULL, root->left);
    ASSERT_STREQ("brown", root->left->word);

    root = add_tree(root, "jumps");
    ASSERT_NE(NULL, root->left->right);
    ASSERT_STREQ("jumps", root->left->right->word);

    ASSERT_EQ(NULL, root->subtree_left);
    ASSERT_EQ(NULL, root->subtree_right);
    free_tree(root);
}

UTEST(test_tree, test_words_with_same_prefix)
{
    n = 3;
    Node *root = NULL;
    root = add_tree(root, "the");
    ASSERT_STREQ("the", root->word);

    root = add_tree(root, "ther");
    ASSERT_NE(NULL, root->subtree_right);
    ASSERT_STREQ("ther", root->subtree_right->word);

    root = add_tree(root, "thea");
    ASSERT_NE(NULL, root->subtree_right->subtree_left);
    ASSERT_STREQ("thea", root->subtree_right->subtree_left->word);

    root = add_tree(root, "thezn");
    ASSERT_NE(NULL, root->subtree_right->subtree_right);
    ASSERT_STREQ("thezn", root->subtree_right->subtree_right->word);

    root = add_tree(root, "thezq");
    ASSERT_NE(NULL, root->subtree_right->subtree_right->subtree_right);
    ASSERT_STREQ("thezq", root->subtree_right->subtree_right->subtree_right->word);

    root = add_tree(root, "theza");
    ASSERT_NE(NULL, root->subtree_right->subtree_right->subtree_left);
    ASSERT_STREQ("theza", root->subtree_right->subtree_right->subtree_left->word);

    ASSERT_EQ(NULL, root->right);
    ASSERT_EQ(NULL, root->left);
    free_tree(root);
}
UTEST_STATE();
