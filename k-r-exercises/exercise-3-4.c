/* Exercise 3-4. In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n
 * equal to -(2^(wordsize-1)). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs. */
/*
 * The value of INT_MIN: -2147483648
 * The value of INT_MAX: 2147483647
 *
 * Answer
 * =========
 * The value of INT_MIN is -(2^(word_size - 1), while the value of INT_MAX is
 * 2^(word_size - 1)
 *
 * NOTE: Here '^' indicates power, not XOR, 2^5 implies 2 to the power 5
 *
 * In two's complement number representation, the most significant bit is the
 * sign bit. So the number of available bits are one less than the total number
 * of bits. | SIGN-BIT |    |    |    |    |    |    | ...... |   |    | 2^31
 * 2^30 2^29 2^28 2^27 2^26 2^25  ......  2^1  2^0
 *
 * So the largest positive number which can be stored is all ones from the 0th
 * bit upto the 30th bit. In this case, the maximum value of such a number is 1
 * + 2^1 + 2^2 + ..... 2^30 Using the formula for sum of geometric progression,
 * S = a(r^n - 1)
 *     ----------
 *        r - 1
 * S = 1(2^31 - 1)
 *     ------------
 *          1
 * n = number of terms and is equal to 31 because 1 is also a term in the sum.
 *
 * So maximum value is 2^31 - 1 = 2147483647
 *
 * In case of the least value of a signed int in two's complement
 * The sign bit is set to 1
 * So the minimum value is -2^31 = -2147483648
 *
 * In case of unsigned int, The max value is 2^0 + 2^1 + 2^2 ..... 2^31 or 2^32
 * - 1 And the minimum value is 0.
 *
 * In this program, when the largest negative number is entered, we make it
 * positive if(n < 0) n = -n; But 2147483648 is larger than INT_MAX (4 bytes)
 * which is 2147483647. So the program gives a wrong output.
 *
 * The solution is to check if the number is INT_MIN, then convert INT_MIN + 1
 * to ascii, then decrease the last digit by 1. For example: Input: -2147483648
 *  Add 1, it becomes -2147483647 and 2147483647 fits in int (INT_MAX).
 *  Convert it, The char array is 8 4 6 3 8 . . . 1 2 -
 *  Increase the first char by by 1 (to make it 8)
 */
#include <limits.h>
#include <stdio.h>
#include <string.h>
void itoa(int n, char s[])
{
    // Store the sign of the number.
    int carry = 0;
    int sign = (n < 0) ? -1 : 1;
    // Makes n positive if it is negative so that it works correctly with the
    // modulus operator (%)
    if (n == INT_MIN) {
        n = n + 1;
        carry = 1;
    }
    if (n < 0) n = -n;
    int i = 0;
    do {
        // printf("(%d)",n%10);
        s[i++] = (n % 10) + '0';
        n = n / 10;
    } while (n != 0);
    if (s[0] != '\0' && carry) s[0] += carry;
    if (sign == -1) s[i++] = '-';
    s[i] = '\0';
    strrev(s);
}
int main()
{
    char buffer[64];
    // printf("The value of INT_MIN: %d\n", INT_MIN);
    // printf("The value of INT_MAX: %d\n", INT_MAX);
    itoa(INT_MIN, buffer);
    printf("%s\n", buffer);
}
