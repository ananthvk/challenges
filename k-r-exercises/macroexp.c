#include<stdio.h>
#define dprint(expr) printf(#expr " = %g\n", expr)
#define noteof(character) while(character != EOF)
int main()
{
    double a, b, c;
    a = 3;
    b = 2;
    c = 7;
    int ch;
    dprint(a + b * c );
    // Can be used to print code
    dprint(printf("Hello\n"));

    // Macros can be used to create your own constructs, or keywords :)
    noteof((ch = getchar()))
    {
        putchar(ch);
    }

}
