/* Exercise 4-12. Adapt the ideas of printd to write a recursive version of
 * itoa; that is, convert an integer into a string by calling a recursive
 * routine. */
#include <stdio.h>

#include "utest.h"


void itoa_(char buff[], int num, int length)
{
    if (num / 10) {
        itoa_(buff, num / 10, length - 1);
    }
    buff[length - 1] = num % 10 + '0';
    printf("%d %d\n", num % 10, length-1);
}

int getLength(int n)
{
    int l = 0;
    do {
        l++;
    } while ((n = n / 10) != 0);
    return l;
}

void itoa2(char buff[], int num)
{
    int l = getLength(num);
    itoa_(buff, num, l);
    buff[l] = '\0';
}

UTEST(test_itoa_recursive, basic)
{
    char buffer[512] = {'\0'};

    itoa2(buffer, 54321);
    EXPECT_STREQ(buffer, "54321");

    itoa2(buffer, 12345);
    EXPECT_STREQ(buffer, "12345");

    itoa2(buffer, 1234);
    EXPECT_STREQ(buffer, "1234");

    itoa2(buffer, 123);
    EXPECT_STREQ(buffer, "123");

    itoa2(buffer, 12);
    EXPECT_STREQ(buffer, "12");

    itoa2(buffer, 1);
    EXPECT_STREQ(buffer, "1");

    itoa2(buffer, 0);
    EXPECT_STREQ(buffer, "0");

    itoa2(buffer, 10);
    EXPECT_STREQ(buffer, "10");

    itoa2(buffer, 100);
    EXPECT_STREQ(buffer, "100");

    itoa2(buffer, 1001);
    EXPECT_STREQ(buffer, "1001");

    itoa2(buffer, 10010);
    EXPECT_STREQ(buffer, "10010");

    itoa2(buffer, 10101);
    EXPECT_STREQ(buffer, "10101");

    itoa2(buffer, 31024006);
    EXPECT_STREQ(buffer, "31024006");

    itoa2(buffer, 3);
    EXPECT_STREQ(buffer, "3");

    itoa2(buffer, 1181);
    EXPECT_STREQ(buffer, "1181");

    itoa2(buffer, 10110210);
    EXPECT_STREQ(buffer, "10110210");

    itoa2(buffer, 60);
    EXPECT_STREQ(buffer, "60");

    itoa2(buffer, 2211);
    EXPECT_STREQ(buffer, "2211");

    itoa2(buffer, 321212);
    EXPECT_STREQ(buffer, "321212");

    itoa2(buffer, 6);
    EXPECT_STREQ(buffer, "6");

    itoa2(buffer, 55112);
    EXPECT_STREQ(buffer, "55112");

    itoa2(buffer, 99);
    EXPECT_STREQ(buffer, "99");

    itoa2(buffer, 0);
    EXPECT_STREQ(buffer, "0");

    itoa2(buffer, 1000);
    EXPECT_STREQ(buffer, "1000");

    // itoa2(buffer, );
    // EXPECT_STREQ(buffer, "");
}
UTEST_MAIN();
