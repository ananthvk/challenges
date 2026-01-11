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
            num *= i;
        } else {
            num *= i / gcd(num, i);
        }
    }
    return num;
}
int main()
{
    printf("%llu\n", largestDivUptoN(20));
}
