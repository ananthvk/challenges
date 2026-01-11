#ifndef HELPERS_H_
#define HELPERS_H_
#include "defs.h"

void swapstr(void *arr[], int i, int j);
int numcmp(void *a, void *b);
int numcmp_rev(void *a, void *b);
int strcmp_rev(void *a, void *b);
int stricmp_rev(void *a, void *b);
int dircmp(char *a, char *b);
int dircmp_rev(void *a, void *b);
int dircmp_f(char *a, char *b);
int dircmp_rev_f(char *a, char *b);
#endif