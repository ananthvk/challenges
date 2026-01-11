#include "sorting_algorithms.h"
void bubble_sort(void *arr[], int n, compare_fptr cmp, swap_fptr swp)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < (n-1); j++)
        {
            if((*cmp)(arr[j], arr[j+1])> 0)
            {
                (*swp)(arr, j, j+1);
            }
        }
    }
}