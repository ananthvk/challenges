/* Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t.
 * (Block structure will help.) */
// The block structure is needed because without it, the variable is declared twice.
// And this causes an error during compilation
#include<stdio.h>
#define printd(expr) printf(#expr " %g\n", expr)
#define printi(expr) printf(#expr " %d\n", expr)
#define swap(t, x, y) \
    { \
    t tmp = x; \
    x = y; \
    y = tmp; \
    } 

int main()
{
    double a = 3, b = 5;
    printd(a);
    printd(b);
    swap(double, a, b)
    printd(a);
    printd(b);
    int c = 6, d = 17;
    printi(c);
    printi(d);
    swap(int, c, d)
    printi(c);
    printi(d);
}
