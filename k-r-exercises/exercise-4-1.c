/* Exercise 4-1. Write the function strindex(s,t) which returns the position of
 * the rightmost occurrence of t in s, or -1 if there is none. */
#include <stdio.h>
#include <string.h>

#include "utest.h"
int lstrindex(char s[], char t[])
{
    int i, k;
    // Iterate over every character of the string which has to be searched.
    for (i = 0; s[i] != '\0'; i++) {
        // Iterate over every character of the search string.
        for (k = 0; t[k] != '\0'; k++) {
            // This part here can cause an out of bounds access.
            // if the last character is compared, i+k will exceed the length of
            // the original array.

            // if(s[i + k] != t[k])
            //  break;

            if (s[i + k] == '\0') {
                // If the k th char of the source string is the null character,
                // we have reached the end of the string. This will probably get
                // handled in the below condition, but just to be explicit and
                // safe....
                break;
            }
            if (s[i + k] != t[k]) break;
        }

        if (t[k] == '\0') {
            // The above loop finished completely, we have the substring at i
            return i;
        }
    }
    return -1;
}

int rstrindex(char s[], char t[])
{
    // NOTE: This is not an efficient algorithm
    // TOOD: Implement Boyer-Moore algorithm for string searching.
    // Find the length of the string
    // char *temp = s;
    // int length;
    // while(*temp++) ++length;

    int length = strlen(s);
    int k;
    // Iterate over every character from backside
    for (int i = (length - 1); i >= 0; i--) {
        for (k = 0; t[k] != '\0'; k++) {
            if (s[i + k] == '\0' || s[i + k] != t[k]) break;
        }
        if (t[k] == '\0') return i;
    }
    return -1;
}

UTEST(RightStrindex, Validity)
{
    ASSERT_EQ(rstrindex("The quick brown fox jumps over the lazy dogs", "over"),
              26);
    ASSERT_TRUE(rstrindex("This is the way", "is") == 5);
    ASSERT_EQ(rstrindex("Once upon a time, long ago in", "in"), 27);
    ASSERT_EQ(rstrindex("Once upon a time, long ago up", "upona"), -1);
    ASSERT_TRUE(rstrindex("is it the way", "is") == 0);
    // ASSERT_EQ(lstrindex("", ""), 0);
    ASSERT_EQ(rstrindex("Once upon a time in a galaxy", "n"), 18);
    ASSERT_EQ(rstrindex("Once upon a time in a galaxy", "O"), 0);
    ASSERT_EQ(rstrindex("Once upon a time in in in in in in in in a a a galaxy",
                        "in"),
              38);
    ASSERT_EQ(
        rstrindex("Once upon a time in in in in in in in in a a a galaxy", "a"),
        50);
    ASSERT_EQ(rstrindex("Once upon a time in in in in in in in in a a a galaxy",
                        "Oncee"),
              -1);
    ASSERT_EQ(rstrindex("Once upon a time in in in in in in in in a a a galaxy",
                        "n "),
              39);
}

UTEST_MAIN();
