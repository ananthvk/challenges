// https://projecteuler.net/problem=9
/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a2 + b2 = c2
For example, 32 + 42 = 9 + 16 = 25 = 52.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.

*/
#include <stdio.h>
int main()
{
    int i = 1, j = 1, k = 1;
    /* Bruteforce solution */
    for (i = 1; i < 1000; i++) {
        for (j = 1; j < 1000; j++) {
            for (k = 1; k < 1000; k++) {
                if (((i + j + k) == 1000) && ((((i * i) + (j * j)) == (k * k)) || (((j * j) + (k * k)) == (i * i)) || (((k * k) + (i * i)) == (j * j))))
                    goto found;
            }
        }
    }
    return -1;
found:
    printf("%d %d %d\n", i, j, k);
    printf("Product:%d", i*j*k);
}
