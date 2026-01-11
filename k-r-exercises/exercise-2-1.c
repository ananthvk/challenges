#include <float.h>
#include <limits.h>
#include <stdio.h>

int main()
{
    printf("%s\n", "Basic datatypes");
    printf("%s\n", "===============");
    printf("char  : %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("short : %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("int   : %d to %d\n", INT_MIN, INT_MAX);
    printf("long  : %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("long long int : %lld to %lld\n", LLONG_MIN, LLONG_MAX);

    printf("float : %f to %f\n", FLT_MIN, FLT_MAX);
    printf("double: %f to %f\n", DBL_MIN, DBL_MAX);

    printf("\n");

    printf("%s\n", "Unsigned datatypes");
    printf("%s\n", "===============");

    printf("unsigned char  : %d to %d\n", 0, UCHAR_MAX);
    printf("unsigned short : %d to %d\n", 0, USHRT_MAX);
    printf("unsigned int   : %d to %d\n", 0, UINT_MAX);
    printf("unsigned long  : %d to %lu\n", 0, ULONG_MAX);

    printf("\n");
    /**
     * // Long double does not work in my machine as I use a port of gcc (mingw)
     * on windows. printf("%s\n","long datatypes");
     *     printf("%s\n","===============");
     *
     *     printf("long double: %LF to %LF\n", LDBL_MIN, LDBL_MAX);
     *
     *     printf("\n"); */
}
