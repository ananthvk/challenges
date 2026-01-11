/** Write the function any(s1,s2), which returns the first location in a string
 * s1 where any character from the string s2 occurs, or -1 if s1 contains no
 * characters from s2. (The standard library function strpbrk does the same job
 * but returns a pointer to the location.) */
/*
 * I have reused code from exercise-2-4
 */

/* Improved algorithm
 * ==================
 * Time complexity : 2n (m + n if the length of the strings are different)
 * Currently works only for ASCII.
 * I am not using a map/hashmap here.
 * Create an array of size 256.(Larger if you want to support other charsets).
 * Call it charactermap and initialize it to 0.
 *
 * For every char c2 of s2
 *      Check if c2 is within range of the charactermap array.
 *      charactermap[c2] = 1
 *
 * j = 0
 * For every char c1 of s1
 *      If charactermap[c1] == 1 then
 *          return j
 *      Increment j by 1
 * return -1
 *
 */
#include <stdio.h>
#include <string.h>
#define CHAR_MAP_SIZE 256
int any(char s1[], char s2[])
{
    // exercise-2-4.c|43 col 21| warning: array subscript has type 'char'
    // [-Wchar-subscripts] On some systems, char can also be signed, i.e. some
    // characters can have negative integer values. So when it is used as array
    // index, the program can access some other memory location and cause
    // undefined behaviour.
    // SO THIS IMPLEMENTATION WORKS ONLY FOR ASCII and UNSIGNED CHAR SYSTEM.
    // The general solution will be to implement a char-int map instead of an
    // array.
    int charactermap[CHAR_MAP_SIZE] = {0};
    size_t i, j;
    for (i = 0; i < strlen(s2); i++) {
        charactermap[s2[i]] = 1;
    }
    for (i = j = 0; s1[i] != '\0'; i++) {
        if (charactermap[s1[i]]) {
            return j;
        }
        j++;
    }
    return -1;
}
int main()
{
    char s1[] = "the quick brown fox jumps over the lazy dogs";
    char s2[] = "ABCD120a";
    /** char s2[] = "abcdefghijklmnopqrstuvwxyz"; */
    int pos = any(s1, s2);
    printf("%d\n", pos);
}
