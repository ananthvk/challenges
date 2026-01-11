// Max range of characters for ascii
#define MAX_CHAR_RANGE 256
#include <stdio.h>
int main()
{
    int frequencies[MAX_CHAR_RANGE] = {0};
    int outOfRanges = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (ch < MAX_CHAR_RANGE)
            frequencies[ch]++;
        else
            outOfRanges++;
    }

    for (int i = 0; i < MAX_CHAR_RANGE; i++) {
        if (frequencies[i] > 0) {
            switch (i) {
                case ' ':
                    printf("%-8s", "BLNK");
                    break;
                case '\n':
                    printf("%-8s", "\\n");
                    break;
                case '\t':
                    printf("%-8s", "\\t");
                    break;
                default:
                    printf("%-8c", i);
            }
            printf("%d\n", frequencies[i]);
        }
    }
    if (outOfRanges > 0)
        printf("Number of out of range characters: %d\n", outOfRanges);
}
// TOOD: Add code to print the histogram
