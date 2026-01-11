// https://projecteuler.net/problem=6
/* The sum of the squares of the first ten natural numbers is,
 *
 * The square of the sum of the first ten natural numbers is,
 *
 * Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is .
 *
 * Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
 *  */
#include <math.h>
#include <stdio.h>
int main()
{
    // This is a really easy problem, just use the formula for sum of squares and sum of first n natural numbers.
    //
    long int n, sum_of_squares, sum_of_n, square_of_sum, diff;
    n = 100;
    sum_of_squares = n * (n + 1) * (2 * n + 1) / 6;
    sum_of_n = n * (n + 1) / 2;
    square_of_sum = sum_of_n * sum_of_n;
    diff = square_of_sum - sum_of_squares;
    diff = (diff >= 0) ? diff : -1 * diff;
    printf("%ld\n", diff);
}
