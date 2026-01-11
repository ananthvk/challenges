// https://projecteuler.net/problem=6
/* By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
 *
 * What is the 10 001st prime number?
 *  */

// For this challenge, I am going to use the Sieve of Eranthoses.
//

// I am using char array instead of int as char uses only 1 byte of storage.
// So 1 million chars use 1 MB
/* #define MAX_N 1000000 */
 #define MAX_N 1000000 /* 1 million */
// Finds the first 78498 primes
//
// #define MAX_N 1000000000 /*1 billion*/
// Finds the first 50847534 primes
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
char soe[MAX_N] = { 0 };
// uint_fast8_t soe[MAX_N] = {0};
// int soe[MAX_N] = {0};
int main()
{
    // char* soe;
    // soe = malloc(sizeof(char) * MAX_N);
    int count = 1;
    int i = 2;
    while (i <= sqrt(MAX_N)) {
        //for (int j = 2 * i; j < MAX_N; j += i) {
        for (int j = i * i; j < MAX_N; j += i) {
            soe[j] = 1;
        }
        while (soe[++i])
            ;
    }
    for (int k = 2; k < MAX_N; k++) {
        if (!soe[k]) {
            if (count == 10001)
                printf("%d ", k);
            count++;
        }
    }
    // Displays one more than the actual count
    printf("Count: %d \n", count);
    // printf("\n");
    // free(soe);
}
