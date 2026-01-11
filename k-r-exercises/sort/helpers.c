#include "helpers.h"
#include "defs.h"
#include<math.h>
#include<string.h>
void swapstr(void *arr[], int i, int j)
{
    void *tmp;
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int numcmp(void *a, void *b)
{
    if(!a || !b)
        return 0;
    double d1 = atof(a);
    double d2 = atof(b);
    if(d1 > d2)
        return 1;
    else if(d1 < d2)
        return -1;
    else
        return 0;
}

int dircmp(char *a, char *b)
{
    // Compares the two items according to the dictionary
    int i;
    for(i = 0; ; i++)
    {
        if(isalpha(a[i]) && isalpha(b[i]) && a[i]!=b[i])
            break;
        if(a[i] == 0)
            return 0;
    }
    return a[i] - b[i];
}

int numcmp_rev(void *a, void *b)
{
    return -numcmp(a, b);
}
int strcmp_rev(void *a, void *b)
{
    return -strcmp(a, b);
}
int stricmp_rev(void *a, void *b)
{
    return -stricmp(a, b);
}

int dircmp_rev(void *a, void *b)
{
    return -dircmp(a, b);
}

int dircmp_f(char *a, char *b)
{   
     // Compares the two items according to the dictionary
    int i;
    for(i = 0; ; i++)
    {
        if(isalpha(a[i]) && isalpha(b[i]) && tolower(a[i])!=tolower(b[i]))
            break;
        if(a[i] == 0)
            return 0;
    }
    return tolower(a[i]) - tolower(b[i]);

}
int dircmp_rev_f(char *a, char *b)
{
    return -dircmp_f(a, b);
}