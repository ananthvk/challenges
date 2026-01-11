// https://projecteuler.net/problem=1
/* If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23. */
/* Find the sum of all the multiples of 3 or 5 below 1000. */
#include<stdio.h>
int solution(int n)
{
    int sum = 0;
    for(int i = 1; i < n; i++)
    {
        sum += (i % 3 == 0 || i % 5 == 0)?i:0;
    }
    return sum;
}
int main()
{
    int s = solution(1000);
    printf("%d\n", s);
}
