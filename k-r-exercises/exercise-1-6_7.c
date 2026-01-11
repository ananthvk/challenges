#include <stdio.h>
int main()
{
    // Verifying that getchar() != EOF is either 1 or 0
    int ch, ch2;
    ch = getchar() != EOF;
    ch2 = getchar() != EOF;
    printf("%d\n", ch);
    printf("%d\n", ch2);
    printf("Value of EOF is: %s\n", EOF);

    /*^Z*/
    /*^D*/
    /*0*/
    /*1*/
    /*Value of EOF is: -1*/

    return 0;
}
