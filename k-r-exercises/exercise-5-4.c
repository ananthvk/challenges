/* Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t
 * occurs at the end of the string s, and zero otherwise. */

// ALGORITHM
// =========
// Example: s: h e l l o  w o r l d \0
//          t:              o r l d \0
// 1. Find the length of t and s.
// 2. Keep incrementing pointer s and t till they both point to the null
// character.
// 3. If the length of t is greater than that of s, return false
// 4. Keep decrementing pointer s and t, len(t) times. If the char at s and t
// are different return false.
// 5. Return true.

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define DEBUG

#include "utest.h"
int strend_(char *s, char *t)
{
    // Check for null
    if(!s)
        return 0;
    if(!t)
        return 0;
#ifdef DEBUG
    char *sp = s;
    char *tp = t;
#endif
    size_t l_s = strlen(s), l_t = strlen(t);
    // Length of string s is lesser than length of string t, so s can never end
    // with t.
    if (l_s < l_t) return 0;
    // Move both pointers to the end of the string.
    // It can also be done as s = s + l_s; (?)
    // while (*s) s++;
    // while (*t) t++;
    s = s + l_s;
    t = t + l_t;

    // This loop runs one less than the length of the string because
    // decrementing pointer to one element before the first element is UB.
    // C11 6.5.6p8
    // l_t - 1 is not required, becauase s and t point to the null character and
    // not the last character of the string.
    //
    for (size_t i = 0; i < l_t; i++) {
        // printf("[IN LOOP] %c %c\n", *s, *t);
#ifdef DEBUG
        assert(s >= sp);
        assert(t >= tp);
#endif
        if (*s-- != *t--) return 0;
    }
    // Now the pointer points to the first element of t.
    // printf("[OUT OF LOOP] %c %c\n", *s, *t);
#ifdef DEBUG
    assert(s >= sp);
    assert(t >= tp);
#endif
    if (*s != *t) {
        return 0;
    }
    return 1;
}

UTEST(strend_test, basic)
{
    char buffer[256] = {'\0'};
    strcpy(buffer, "The quick brown the over jumps cat fox jumps over the");

    // Test cases when the string is present at the end
    ASSERT_EQ(strend_(buffer, "the"), 1);
    ASSERT_EQ(strend_(buffer, " the"), 1);
    ASSERT_EQ(strend_(buffer, "over the"), 1);
    ASSERT_EQ(strend_(buffer, "jumps over the"), 1);

    // Test cases when the string is not present at the end
    ASSERT_EQ(strend_(buffer, "\nthe"), 0);
    ASSERT_EQ(strend_(buffer, " thee"), 0);
    ASSERT_EQ(strend_(buffer, "Iver the"), 0);
    ASSERT_EQ(strend_(buffer, "jumps ovr the"), 0);

    // Test cases when the string is present elsewhere in the string but not at
    // the end
    ASSERT_EQ(strend_(buffer, "quick brown"), 0);
    ASSERT_EQ(strend_(buffer, "over jumps"), 0);
    ASSERT_EQ(strend_(buffer, "cat"), 0);

    // Test cases when the length of s is equal to t
    strcpy(buffer, "hello");
    ASSERT_EQ(strend_(buffer, "ello"), 1);
    ASSERT_EQ(strend_(buffer, "hello"), 1);

    ASSERT_EQ(strend_(buffer, "hellr"), 0);
    ASSERT_EQ(strend_(buffer, "zello"), 0);

    // Test cases when the length of t is more than that of s
    strcpy(buffer, "world");
    ASSERT_EQ(strend_(buffer, "hello world"), 0);
    ASSERT_EQ(strend_(buffer, " world"), 0);
    ASSERT_EQ(strend_(buffer, "this is the world"), 0);
    ASSERT_EQ(strend_(buffer, "The world"), 0);
    ASSERT_EQ(strend_(buffer, "HHorld"), 0);
}

UTEST(strend_test, edge_cases)
{
    char buffer[256] = {'\0'};
    // Test cases when s is empty
    ASSERT_EQ(strend_(buffer, ""), 1);
    // NOTE: The the above test case should return 1, since both s and t are
    // empty, we can consider that s ends with t.
    ASSERT_EQ(strend_(buffer, "hello"), 0);
    ASSERT_EQ(strend_(buffer, "This is just another sentence"), 0);

    strcpy(buffer, "The quick brown the over jumps cat fox jumps over the");

    // Test cases when t is empty
    // When t is empty, strend_ should return true for every string s
    ASSERT_EQ(strend_(buffer, ""), 1);

    // Test cases when the length of t is 1
    ASSERT_EQ(strend_(buffer, "e"), 1);
    ASSERT_EQ(strend_(buffer, "h"), 0);
    ASSERT_EQ(strend_(buffer, "a"), 0);

    // Test cases when the length of s is 1
    strcpy(buffer, "a");
    ASSERT_EQ(strend_(buffer, "a"), 1);
    ASSERT_EQ(strend_(buffer, ""), 1);
    ASSERT_EQ(strend_(buffer, " a"), 0);
    ASSERT_EQ(strend_(buffer, "abc"), 0);
}

UTEST_MAIN();
