// https://projecteuler.net/problem=10
/*
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 *
 * Find the sum of all the primes below two million. */
// Reusing the code from the previous prime problem 6

// I am using char array instead of int as char uses only 1 byte of storage.
// So 1 million chars use 1 MB
/* #define MAX_N 1000000 */
#define MAX_N 2000000 /* 1 million */
// Finds the first 78498 primes
//
// #define MAX_N 1000000000 /*1 billion*/
// Finds the first 50847534 primes
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
char soe[MAX_N] = {0};
// uint_fast8_t soe[MAX_N] = {0};
// int soe[MAX_N] = {0};
int main()
{
    // char* soe;
    // soe = malloc(sizeof(char) * MAX_N);
    unsigned long long int sum = 0;
    int count = 1;
    int i = 2;
    while (i <= sqrt(MAX_N)) {
        for (int j = 2 * i; j < MAX_N; j += i) {
            soe[j] = 1;
        }
        while (soe[++i])
            ;
    }
    for (unsigned int k = 2; k < MAX_N; k++) {
        if (!soe[k]) {
            sum += k;
        }
    }
    printf("%llu\n", sum);
    // free(soe);
}
