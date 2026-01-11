/* Exercise 3-6. Write a version of itoa that accepts three arguments instead of
 * two. The third argument is a minimum field width; the converted number must
 * be padded with blanks on the left if necessary to make it wide enough. */
#include <limits.h>
#include <stdio.h>
#include <string.h>
void itoa(int n, char s[], int w)
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

    // i is the length of the number.
    // Option 1
    /*
    for(int j = (i < w)?(w-i):0; j > 0; j--)
    {
        s[i++] = ' ';
    }
    */
    // Option 2
    while (i < w)
        // This works here because i is essentialy the length of the number.
        s[i++] = ' ';
    s[i] = '\0';
    strrev(s);
}
int main()
{
    char buffer[64];
    // printf("The value of INT_MIN: %d\n", INT_MIN);
    // printf("The value of INT_MAX: %d\n", INT_MAX);
    // itoa(INT_MIN, buffer, 8);
    itoa(3112, buffer, 0);
    printf("%s\n", buffer);
    itoa(3112, buffer, 1);
    printf("%s\n", buffer);
    itoa(3112, buffer, 2);
    printf("%s\n", buffer);
    itoa(3112, buffer, 3);
    printf("%s\n", buffer);
    itoa(3112, buffer, 4);
    printf("%s\n", buffer);
    itoa(3112, buffer, 5);
    printf("%s\n", buffer);
    itoa(3112, buffer, 6);
    printf("%s\n", buffer);
    itoa(-3112, buffer, 0);
    printf("%s\n", buffer);
    itoa(-3112, buffer, 1);
    printf("%s\n", buffer);
    itoa(-3112, buffer, 2);
    printf("%s\n", buffer);
    itoa(-3112, buffer, 3);
    printf("%s\n", buffer);
    itoa(-3112, buffer, 4);
    printf("%s\n", buffer);
    itoa(-3112, buffer, 5);
    printf("%s\n", buffer);
    itoa(-3112, buffer, 6);
    printf("%s\n", buffer);
}
