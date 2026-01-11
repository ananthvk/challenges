#include <ctype.h>
#include <stdio.h>
#define OUT_NUMBER 0
#define IN_NUMBER 1

int atoi(char s[])
{
    int i, sign = 1, mode = OUT_NUMBER;
    for (i = 0; s[i] != '\0'; i++) {
        if (mode == OUT_NUMBER) {
            if (s[i] == ' ' || s[i] == '+') continue;
            if (s[i] == '-')
                sign = -sign;
            else {
                printf("%s\n", "Bad input");
                return -1;
            }
        }
        if (isdigit(s[i])) {
            mode = IN_NUMBER;
        }
    }
}

int main()
{
    char s[] = "-53212";
    printf("%d", atoi(s));
}
