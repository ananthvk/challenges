#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x, y, t) \
    {                 \
        t tmp = x;    \
        x = y;        \
        y = tmp;      \
    }

#define PRINT_SPACES(n)                                                       \
    for (int z = 0; z < n; z++) putchar((z % INDENT_WIDTH == 0) ? '|' : ' '); \
    putchar('|');                                                             \
    putchar('-')

#define INDENT_WIDTH 3
#define SIZE 10*1000*1000 // 10 MB of storage
int VISUAL = 0;
int OUTPUT = 0;

void displayArray(int *arr, size_t n);

size_t ssort(int *arr, size_t n)
{
    // Performs selection sort on the input array
    // Returns an integer representing the number of times the loop has run
    size_t smallest;
    size_t run = 0;
    for (size_t i = 0; i < n; i++) {
        if (VISUAL) {
            printf("Pass %zu: ", i);
            displayArray(arr, n);
        }

        smallest = i;
        // Find the smallest element in the array
        for (size_t j = i + 1; j < n; j++) {
            ++run;
            if (arr[j] < arr[smallest]) smallest = j;
        }
        // Swap the element at ith position with the smallest element
        int tmp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = tmp;
        if (VISUAL) {
            printf("        ");
            displayArray(arr, n);
            printf("====================\n");
        }
    }
    return run;
}

void bubble_sort(int *arr, size_t n)
{
    // Repeat the loop n times
    for (size_t i = 0; i < n; i++) {
        // Repeat the inner swapping loop upto the penultimate element.
        // NOTE: This can be optimized by noting the fact that after every pass,
        // an element at the end gets sorted.
        for (size_t j = 0; j < (n - 1); j++) {
            if (arr[j + 1] < arr[j]) {
                // Swap the numbers
                SWAP(arr[j + 1], arr[j], int)
            }
        }
    }
}

size_t merge(int *aux, int *arr1, size_t n1, int *arr2, size_t n2)
{
    // Merges elements from two arrays into an auxillary array
    // in a sorted manner
    // Find the pointer to last element of both arrays
    // Returns the number of times the loop has run
    size_t run = 0;

    int *arr1_end = arr1 + n1 - 1;
    int *arr2_end = arr2 + n2 - 1;
    while ((arr1 <= arr1_end) && (arr2 <= arr2_end)) {
        ++run;
        // Put the lower of the two element in the aux array first
        if (*arr1 < *arr2) {
            // Only increase the pointer in the first array
            *aux++ = *arr1++;
        }
        else {
            *aux++ = *arr2++;
        }
    }
    while (arr1 <= arr1_end) {
        ++run;
        // Copy remaining elements
        *aux++ = *arr1++;
    }
    while (arr2 <= arr2_end) {
        ++run;
        // Copy remaining elements
        *aux++ = *arr2++;
    }
    return run;
}
size_t merge_sort(int *arr, size_t n, int *aux, int depth)
{
    // depth parameter for printing appropriate number of spaces
    size_t run = 0;
    if (n < 1) {
        printf("%s\n", "SERIOUS ERROR, n < 1");
        exit(-1);
    }
    // Only one element, it is already sorted
    if (n == 1) return 1;

    size_t l_i = n / 2;
    size_t r_i = n - (n / 2);
    if (VISUAL) {
        PRINT_SPACES(depth * INDENT_WIDTH);
        displayArray(arr, n);
    }

    // merge sort the left half
    run += merge_sort(arr, l_i, aux, depth + 1);
    // merge sort the right half
    run += merge_sort(arr + l_i, r_i, aux, depth + 1);

    // merge the two halves together
    run += merge(aux, arr, l_i, arr + l_i, r_i);
    for (size_t i = 0; i < n; i++) *(arr + i) = *(aux + i);
    // displayArray(aux, n);
    if (VISUAL) {
        PRINT_SPACES(depth * INDENT_WIDTH);
        putchar('-');
        putchar(' ');
        displayArray(arr, n);
    }
    return run;
}
void displayArray(int *arr, size_t n)
{
    // Prints an array
    // Gets the pointer to the last element of the array.
    int *end = arr + n - 1;
    while (arr <= end) {
        printf("%d ", *arr++);
    }
    printf("\n");
}

void get_integers(int *buff, size_t n)
{
    // Get n integers from stdin
    // No input checking done here
    for (size_t i = 0; i < n; i++) {
        // printf("Enter the %zu number: ", i);
        scanf("%d", buff++);
    }
}

int main(int argc, char *argv[])
{
    // Array of SIZE numbers
    // int arr[SIZE] = {1, 11, 7, 8, 2, 0, 3, 16, 4, 9, 3, 5, 12};
    // displayArray(arr, SIZE);
    char *str;
    while (--argc > 0) {
        str = *++argv;
        if(strcmp(str, "-v") == 0)
            VISUAL = 1;
        if(strcmp(str, "-o") == 0)
            OUTPUT = 1;
    }

    // int arr[SIZE] = {0};
    // int arr2[SIZE] = {0};
    // int aux[SIZE] = {0};

    int *arr = (int*)malloc(SIZE*sizeof(int)); 
    int *arr2 = (int*)malloc(SIZE*sizeof(int)); 
    int *aux = (int*)malloc(SIZE*sizeof(int)); 

    size_t n = 0;
    printf("How many numbers? : ");
    scanf("%zu", &n);
    printf("\n");
    get_integers(arr, n);

    memcpy(arr2, arr, n * sizeof(int));

    printf("\n");
    printf("========== MERGE SORT ==========\n");
    printf("%zu\n", merge_sort(arr, n, aux, 0));
    if(OUTPUT)
        displayArray(arr, n);
    printf("========== SELECTION SORT ==========\n");
    printf("%zu\n", ssort(arr, n));
    if(OUTPUT)
        displayArray(arr, n);
}
// TEST
// $ gen_sort_num.py 1000 100000 | sorting_algorithms.exe
// How many numbers? :
// ========== MERGE SORT ==========
// 1768928
// ========== SELECTION SORT ==========
// 4999950000
//
// On calculating n*log to base 2 n, for merge sort the value comes out to
//      1 660 964
// The actual run(excluding thecopying time)
//      1 768 928    
//
// On calculating n^2, for selection sort the value is
//      10^5, or 10 billion
// The actual run value is 
//      4 999 950 000 
//      Which is close to 5 billion
// Finding n*(n-1)/2, which is the predicted running steps of this algorithm
//      4 999 950 000
// 
// The base of log as calculated by me for various inputs on my machine comes out to 1.9334
