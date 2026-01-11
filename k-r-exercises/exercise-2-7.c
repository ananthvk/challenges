/** Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits
 * that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged. */
/*
 * SOLUTION:
 * ===========
 * In this example, let p = 4 and n = 3
 * 9 8 7 6 5 4 3 2 1 0
 * x x x x x x x x x x
 *
 * So the result has to be
 * 9 8 7 6 5 4 3 2 1 0
 * x x x a b c x x x x
 *
 * Create a mask
 * (1 << n) - 1
 * Here n = 3.
 * 0 0 0 0 0 0 0 1 1 1
 * Left shift by p
 * 0 0 0 1 1 1 0 0 0 0 ---------- (2)
 * Combine x and (2) using logical XOR.
 *
 */
/*
Python 3 implementation for experimenting
===================================
f = lambda x, p, n: print(bin(x), '\n', bin(x ^ (((1 << n) - 1) << p)), sep='')
f(2**24 - 1,5,6)
f(2**24,5,6)
*/
#include <stdio.h>
typedef unsigned int uint;
uint invert(uint x, uint p, uint n) { return x ^ (((1 << n) - 1) << p); }
int main() { printf("%d\n", invert(40, 3, 3)); }
