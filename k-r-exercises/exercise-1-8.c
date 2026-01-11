#include <stdio.h>

int main()
{
    int ch;
    int nb = 0, nt = 0, nl = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == ' ') ++nb;
        if (ch == '\n') ++nl;
        if (ch == '\t') ++nt;
    }
    printf("Spaces:%-6dTabs:%-6dNewlines:%-6d\n", nb, nt, nl);
    return 0;
}
