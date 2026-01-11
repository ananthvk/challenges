#include<stdio.h>
#include<ctype.h>
#include<string.h>
int main(int argc, char *argv[])
{
    int ch;
    if(strcmp(argv[0], "exercise-7-1.exe") == 0)
    {
        while((ch=getchar())!=EOF)putchar(tolower(ch));
    }
    else
    {
        while((ch=getchar())!=EOF)putchar(toupper(ch));
    }
}
