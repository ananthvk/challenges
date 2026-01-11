/** Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
 * bits that begin at position p set to the rightmost n bits of y, leaving the
 * other bits unchanged. */
/*
 * I had difficulty in understanding the problem as it was not clear which
 * side should position be considered from.
 *
 * Got clarification from
 * https://stackoverflow.com/questions/1415854/kr-c-exercise-help
 *
 * Position starts from 0 at the right.
 *
 * For example:
 * 9 8 7 6 5 4 3 2 1 0
 * x x x x x x x x x x
 *
 * If p = 6 and n = 4
 *
 * 9 8 7 6 5 4 3 2 1 0
 * x x x x x x x x x x
 *       ^ ^ ^ ^
 * The marked positions have to be replaced with the rightmost n bits of y.
 *
 * 9 8 7 6 5 4 3 2 1 0
 * y y y y y y a b c d
 *
 * Result
 * ======
 *
 * 9 8 7 6 5 4 3 2 1 0
 * x x x a b c d x x x
 *
 * High level algorithm
 * ===========
 * 1 - Set the n bits in x from position p to 0
 * 9 8 7 6 5 4 3 2 1 0
 * x x x 0 0 0 0 x x x
 *
 * 2 - Extract rightmost n bits from y
 * 9 8 7 6 5 4 3 2 1 0
 * 0 0 0 0 0 0 a b c d
 *
 * 3 - Left shift the extracted bits from y so that they align with the bit
 * fields of x. (In this example, left shift by 3 ( p - n + 1) 9 8 7 6 5 4 3 2 1
 * 0 0 0 0 a b c d 0 0 0
 *
 * 4 - Perform logical OR between x and y
 * 9 8 7 6 5 4 3 2 1 0
 * x x x a b c d x x x
 *
 * Details
 * ========
 * Note: The program uses n+1 instead of n, as the position starts from 0.
 *
 * To set the n bits in x from position p to 0.
 * --------------------------------------------
 *
 * Right shift x by p+1, x >> 7, to get the left most bits
 * x x x
 * Left shift this result by p+1, x << 7 to get
 * x x x 0 0 0 0 0 0 0       -------------- (1)
 *
 * Get the right most bits of x which have to remain unchanged.
 * Perform (1 << (p-n+1)) - 1
 * (1 << (6 - 4 + 1)) - 1
 * Gives the mask
 * 0 0 0 0 0 0 0 1 1 1
 * Apply this mask to x to get
 * 0 0 0 0 0 0 0 x x x        -----------------(2)
 *
 * Combine (1) & (2) using logical OR
 * x x x 0 0 0 0 x x x
 *
 * Extracting right most n bits from y
 * -----------------------------------
 * Create the mask to extract the rightmost n bits from y
 * (1 << n) - 1
 * 0 0 0 0 0 0 1 1 1 1
 * Apply this mask using logical AND to y
 * 0 0 0 0 0 0 a b c d  --------------------- (3)
 *
 * Alignment of the extracted bits
 * -----------------------------------
 * To (3), apply left shift of (p - n + 1)
 * In this example, (6 - 4 + 1 = 3)
 * 0 0 0 a b c d 0 0 0 ------------------------ (4)
 *
 * Merging the numbers and getting the result
 * ------------------------------------------
 * Perform logical OR between  (4) and (2)
 * x x x a b c d x x x
 */

// Python solution for experimenting
/** f = lambda x, p, n: ((x>>(p+1))<<(p+1)) | (((1 << (p-n+1)) - 1) & x)
 * g = lambda x, p, n : print(bin(x),'\n',bin(f(x, p ,n)), sep = '') */

#include <stdio.h>
unsigned int setbits(unsigned int x, unsigned int p, unsigned int n,
                     unsigned int y)
{
    unsigned int x_m =
        ((x >> (p + 1)) << (p + 1)) | (((1 << (p - n + 1)) - 1) & x);
    unsigned int y_m = (((1 << n) - 1) & y) << (p - n + 1);
    return x_m | y_m;
}
int main()
{
    // TODO: Add checks for negative shifts
    // For example if position is 5 and n = 6, it can result in undefined
    // behaviour. Assumed that p > n
    printf("%d\n", setbits(2551, 8, 5, 3998));
}
