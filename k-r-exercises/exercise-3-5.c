/* Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into
 * a base b character representation in the string s. In particular,
 * itob(n,s,16) formats s as a hexadecimal integer in s. */

// Number-Character mapping. Base-36 is the maximum supported base.
// mapping has to be initialized in main();

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
// char mapping[36] = {'\0'};
// Used the program from exercise-3-3 to generate the chars.
char const mapping[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// NOTE: This also includes the null character.

int itob(int n, char s[], int b, int destSize)
{
    /*
     * n - Number to be converted
     * s - Buffer to store number in converted base
     * b - Base
     * destSize - Size of s[]
     * NOTE: Does not support negative numbers.
     */
    int j = 0;
    if (n < 0) {
        printf(
            "%s\n",
            "Not Implemented (negative numbers) - Number has to be positive");
        // exit(-1);
        return 1;
    }
    if (b > 36) {
        printf("%s\n", "Unsupported - Base has to be less than or equal to 36");
        // exit(-1);
        return 1;
    }
    if (b <= 1) {
        printf("%s\n", "Invalid base - Base has to be greater than 1");
        // exit(-1);
        return 2;
    }
    // I have use a do-while loop instead of while loop to handle the case when
    // n is 0. So that the loop runs atleast once and digit becomes 0 (0 %
    // anything = 0)
    do {
        // -1, because C strings are null terminated.
        if (j >= (destSize - 1)) {
            printf(
                "%s\n",
                "Buffer overflow, converted number cannot be stored in buffer");
            // exit(-1);
            return 3;
        }
        s[j++] = mapping[n % b];
        n = n / b;
    } while (n != 0);
    s[j] = '\0';
    strrev(s);
    return 0;
}

int main()
{
    char buffer[64];
    // Initialize conversion map.
    // int j = 0;

    // The following way of initializing mapping does not work on non ascii
    // systems. This only works on ascii based systems. To make this program
    // portable, it is necessary to hardcode the characters for(int i = '0'; i
    // <= '9'; i++) mapping[j++] = i; for(int i = 'a'; i <= 'z'; i++)
    // mapping[j++] = i; assert(j==36);

    int n = 0;
    printf("%s\n", "Input non numeric to exit");
    // MAYBE A BUG
    // When sending interrupt using Ctrl+C, some extra lines are printed
    // Does not happen with Ctrl+D
    while (1) {
        // Type any character and enter to exit
        if (scanf("%d", &n) == 0) break;
        for (int i = 2; i <= 36; i++) {
            if (itob(n, buffer, i, 64) == 0) printf("%d - %s\n", i, buffer);
        }
    }
    return 0;
}
