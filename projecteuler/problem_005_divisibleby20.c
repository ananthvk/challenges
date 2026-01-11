// https://projecteuler.net/problem=5
// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

// Prime factorizing 2520
// 2^3 * 3^2 * 5^1 * 7
//
// Prime factorization of 10!
// 2^8 × 3^4 × 5^2 × 7
#include <math.h>
#include <stdio.h>
typedef unsigned long long int ul_int;
int isPrime(ul_int n)
{
    if (n == 2 || n == 3)
        return 1;
    int rem = n % 6;
    // All prime numbers except 2 or 3 are of the form 6k +- 1
    if (rem != 1) {
        if (rem != 5)
            return 0;
    }
    if (rem != 5) {
        if (rem != 1)
            return 0;
    }
    for (ul_int i = 2; i <= sqrt(n); i++) { if (n % i == 0)
            return 0;
    }
    return 1;
}

ul_int gcd(ul_int a, ul_int b)
{
    ul_int t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}
ul_int largestDivUptoN(ul_int n)
{
    ul_int num = 1;
    for (ul_int i = 2; i <= n; i++) {
        if (isPrime(i)) {
            // printf("%d ", i);
            // If the number is prime, the resultant number should be divisible by it.
            num *= i;
        } else {
            // This number is not a prime and is a product of prime numbers
            // gcd(num, i) finds the greatest common divisor between the factor and the number.
            // For example: gcd(840, 9) = 3
            // To find a number x, which when multiplied by 840, gives a number divisible by 9
            // To find x, divide 9 by 3.
            // Q: What must be multiplied with 840 to make it divisible by 23?
            // 23 is a prime number, so we know that 840 has to be multiplied by 23.
            // Finding the gcd of (840, 23), we get 1, which means 840 does not have any factor of 23.
            // On multiplying 840 by 23/1, (the greatest factor), we get the least number divisible by 23.
            num *= i / gcd(num, i);
        }
    }
    // printf("\n");
    return num;
}
int main()
{
    for(ul_int i = 1; i <= 20; i++)
        printf("%llu - %llu\n", i, largestDivUptoN(i));
    ul_int a = 32ull;
    printf("%llu\n", largestDivUptoN(a));
}
