/** Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes
 * each character in s1 that matches any character in the string s2. */
/*
 * Simple algorithm
 * ===============
 * Time complexity : n^2 (m*n if the length of the strings are different)
 * j = 0
 * For every character c of s1
 *      If c is not present in s2
 *          s1[j] = c
 *          Increment j by 1
 * Set the value of s1[j] to null character.
 *
 * Improved algorithm
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
 *      If charactermap[c1] == 0 then
 *          s1[j] = c1
 *          Increment j by 1
 * Set the value of s1[j] to null character.
 *
 */
#include <stdio.h>
#include <string.h>
#define CHAR_MAP_SIZE 256
void squeeze(char s1[], char s2[])
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
        if (!charactermap[s1[i]]) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}
int main()
{
    char s1[] = "the quick brown fox jumps over the lazy dogs";
    char s2[] = "aeiou";
    /** char s2[] = "abcdefghijklmnopqrstuvwxyz"; */
    squeeze(s1, s2);
    printf("%s\n", s1);
}
