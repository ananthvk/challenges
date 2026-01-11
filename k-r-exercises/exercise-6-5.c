// I am going to implement a hash table in this program

// Algorithm:
// 1. Generate a hash for the given word
// 2. In the internal array, place the string as a node at the hash position
// 3. If that index is non empty, add the new string to the end of that list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// A safer version of malloc which causes the program to exit if memory cannot
// be allocated
void *safe_malloc(size_t n);
// Works like the strdup() function
char *duplicatestr(const char *s);

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

int main()
{
    table_store("Hello", "world");
    table_store("this", "is");
    table_store("the", "quick");
    table_store("brown", "fox");
    table_store("Hello earth",
                "This string is about the great planet called earth");
    table_store("This is earth", "what is the earth");
    table_store("foo", "ffjskflskafdljas");

    table_find("Hello");
    table_find("brown");
    table_find("the");
    table_find("this");
    printf("===============\n");

    table_remove("Hello");
    table_remove("this");
    table_remove("the");
    table_remove("brown");
    table_remove("Hello earth");
    table_remove("This is earth");
    table_remove("foo");

    table_find("Hello");
    table_find("brown");
    table_find("the");
    table_find("this");

    table_remove("Hello");
    table_remove("this");
    table_remove("the");
    table_remove("brown");
    table_remove("Hello earth");
    table_remove("This is earth");
    table_remove("foo");

    table_store("Hello", "world");
    table_store("this", "is");
    table_store("the", "quick");
    table_store("brown", "fox");
    table_store("Hello earth",
                "This string is about the great planet called earth");
    table_store("This is earth", "what is the earth");
    table_store("foo", "ffjskflskafdljas");

    table_find("This does not");
    table_find("Hello earth");
    table_find("BA BA BA");
    table_find("Hello");
    table_find("brown");
    table_find("the");
    table_find("this");
    printf("===============\n");
    table_store("Abcd", "The first four letters of the alphabet");
    table_find("Abcd");

    table_store("Abcd", "Some more chars now");
    table_find("Abcd");

    table_store("Abcd", "Third attempt at repetition");
    table_find("Abcd");

    table_remove("Abcd");
    table_find("Abcd");

    table_store("Abcd", "Something totally different");
    table_find("Abcd");

    table_free();
}
