/** Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
 * integer x rotated to the right by n positions */
/*
 * Example
 * ========
 * Let a = x x x x y y y
 * n = 3
 * y y y x x x x
 * n = 3
 * x x x y y y x
 * n = 1
 * x x x x y y y
 * n = 3
 * y y y x x x x
 *
 *
 * Algorithm
 * ============
 * Let x be the integer to be right rotated.
 * Let n be the number of positions to rotate.
 * temp = x >> n
 * Let len = 0
 *
 * [Find the number of significant bits in x]
 * [NOTE: Negative numbers cause an issue here]
 * while temp != 0
 *      temp = temp >> 1
 *      len = len + 1
 *
 * [mask to extract the contents which were right shifted]
 * mask = (1 << n) - 1
 * y = mask & x
 * result = (y << len) | (x >> n)
 *
 */
#include <stdio.h>
/*
 * NOTE: This was my understanding of right rotate shift.
 * But according to various sources, you have to also shift the zeros according
 * to the datatype.
 * For example:
 * 0 0 0 x x x y y
 * Right rotate shift by 2 results in
 * y y 0 0 0 x x x
 * Instead of
 *       y y x x x
 */
unsigned int rightrot(unsigned int x, unsigned int n)
{
    unsigned int temp = x >> n, len = 0, y;
    while (temp != 0) {
        temp >>= 1;
        len++;
    }
    y = ((1 << n) - 1) & x;
    return (y << len) | (x >> n);
}
unsigned int rightrot2(unsigned int x, unsigned int n)
{
    // Range of n must be between 1 and 31.
    // As 32 bit shifts are undefined(for 4 byte int implementations).
    if (n < 1) n = 1;
    if (n > 31) n = 31;
    unsigned int y = ((1 << n) - 1) & x;
    return (y << (sizeof(unsigned int) * 8 - n)) | (x >> n);
}
int main()
{
    printf("%u\n", rightrot2(32, 5));
    printf("%u\n", rightrot2(2489, 10));
    printf("%u\n", rightrot2(12, 2));
    printf("%u\n", rightrot2(14, 2));
    printf("%u\n", rightrot2(16, 2));
    printf("%u\n", rightrot2(18, 2));
    printf("%u\n", rightrot2(0, 5));
}
