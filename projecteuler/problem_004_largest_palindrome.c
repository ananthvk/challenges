/* https://projecteuler.net/problem=4
 * A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers. */
/* Naive brute force algorithm */
/*
 *
Brute force python solution
===========================
Time: n^2

max_num = 0
for i in range(999, 0, -1):
    for j in range(999, 0, -1):
        if str(i*j) == str(i*j)[::-1] and i*j > max_num:
            max_num = i*j
*/

int isPalindrome(int num)
{
    while((num = num/10) != 0)
}
