/* https://projecteuler.net/problem=3
 * The prime factors of 13195 are 5, 7, 13 and 29.
 * What is the largest prime factor of the number 600851475143 ? */

// The number is 12 digits long, so I am going to use unsigned long long int
//
#include<stdio.h>
#include<math.h>
typedef  long long int ul_int;

ul_int getLargestPrimeFactor(ul_int n)
{
    ul_int mx =  (ul_int)sqrtl(n);
    ul_int mprime = n % 2 == 0?2: (n%3 == 0)? 3: 1;
    for(int k = 0;6*k + 1 <= mx;k++)
    {
        if(n % (6*k + 1) == 0 && isPrime(6*k + 1))
        {
            mprime = 6 * k + 1;
        }
        if(n % (6*k - 1) == 0 && isPrime(6*k - 1))
        {
            mprime = 6 * k - 1;
        }
    }
    return mprime;
}

int isPrime(ul_int n)
{
    if(n == 2 || n == 3)
        return 1;
    int rem = n % 6;
        // All prime numbers except 2 or 3 are of the form 6k +- 1
    if(rem != 1)
    {
        if(rem != 5)
            return 0;
    }
    if(rem != 5)
    {
        if(rem != 1)
            return 0;
    }
    for(int i = 2; i <= sqrt(n); i++)
    {
        if(n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    // llu format specifier does not work with mingw-gcc, but works with clang on mingw.
    printf("%lld\n", getLargestPrimeFactor(13195));
// problem_003_greatest_primefactor.c|43 col 52| warning: overflow in expression; result is -1226343925 with type 'int' [-Winteger-overflow]
    printf("%lld\n", getLargestPrimeFactor(24324539*1009));

}
