#ifndef DEFS_H_
#define DEFS_H_
typedef int (*compare_fptr)(void *a, void *b);
typedef void (*swap_fptr)(void *arr, int i, int j);
typedef void (*sort_fptr)(void *arr[], int n, compare_fptr, swap_fptr);
#endif