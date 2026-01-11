#include<stdio.h>

int sum(int a, int b){return a+b;}
int mul(int a, int b){return a*b;}
int div(int a, int b){return a/b;}
int sub(int a, int b){return a-b;}
int unk(int a, int b){printf("Unknown symbol %d %d \n", a, b); return 0;}

typedef int (*fptr)(int, int);

fptr givefunc(char ch)
{
    switch(ch)
    {
        case '+':
            return sum;
        case '-':
            return sub;
        case '/':
            return div;
        case '*':
            return mul;
        default:
            return unk;
    }
}

int main()
{
    int res = givefunc('+')(5, 2);
    fptr f = givefunc('-');
    printf("%d\n", res);
    printf("%d\n", f(4, 8));
}
