#include "utest.h"

UTEST(FunCheck, CheckFunc2) { ASSERT_TRUE(1); }

UTEST(FunCheck, CheckFunc)
{
    int a = 5;
    int b = 5;
    ASSERT_TRUE(a != b);
}

UTEST_MAIN();
