#include <stdio.h>
/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
/*
int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;

    while (low <= high)
    {
        printf("(%d, %d, %d)\n", low, mid, high);
        mid = (low+high)/2;
        if (x == v[mid])
            return mid;
        if (x < v[mid])
            high = mid + 1;
        if (x > v[mid])
            low = mid + 1;

    }
    return -1;
}
*/
#include <assert.h>
int binsearch(int x, int v[], int n)
{
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (v[mid] == x) return mid;
        if (v[mid] < x) low = mid + 1;
        if (v[mid] > x) high = mid - 1;
    }
    return -1;
}

int main()
{
    int arr[] = {3, 7, 11, 16, 21, 23, 321, 441, 719, 1288, 1387, 41223};
    printf("%d\n", binsearch(1288, arr, 12));
}
