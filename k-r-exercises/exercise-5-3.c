/* Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s. */

#include <stdio.h>
void strcat_(char *s1, char *s2)
{
    // s2 is copied to the end of s1

    // Go to the end of s1
    // This version does not work
    // while(*s1++);
    // Because, when it exits the loop, null character has been found
    // but the ++ (increment part is executed) and s1 points to the character
    // after the null char so it is necessary to either decrement s1 after this
    // loop or use the structure in which s1 is incremented only if it is not
    // null. While this version works
    while (*s1) s1++;
    while ((*s1++ = *s2++))
        ;
}

int main()
{
    char buf[64] = "hello";
    strcat_(buf, " world");
    printf("%s\n", buf);
}
