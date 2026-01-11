/* Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B. */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
size_t strncpy_(char *s, char *t, size_t n)
{
    size_t tmp = 1;
    while (tmp <= n) {
        if (!(*s++ = *t++)) break;
        tmp++;
    }
    return tmp;
}

void strlcpy_(char *s, char *t, size_t n)
{
    // Copies a c string and places null character if necessary.
    printf("strlen(t) = %zu n = %zu\n", strlen(t), n);
    if (strlen(t) > n) {
        strncpy_(s, t, n - 1);
        assert(n - 1 < 128);
        printf("Setting element at index %zu to null\n", n - 1);
        s[n - 1] = '\0';
    }
    else
        strncpy_(s, t, n);
}

void strncat_(char *s, char *t, size_t n)
{
    size_t tmp = 1;
    // Go to the end of the string
    while (*s) {
        s++;
        tmp++;
    }
    printf("End of string is at :%zu\n", tmp);
    while (tmp <= n) {
        if (!(*s++ = *t++)) break;
        tmp++;
    }
    // Check if the length was not enough
    printf("%zu %zu\n", tmp, n);
    if (tmp > n) {
        printf("+Length ==%zu\n", tmp);
        s[tmp] = 'A';
        printf("(%c)\n", s[tmp]);
    }
}

int strncmp_(char *cs, char *ct, size_t n)
{
    /* int strncmp(cs,ct,n)
     * compare at most n characters of string cs to string ct; return <0 if
     * cs<ct, 0 if cs==ct, or >0 if cs>ct. */
    // Page 227, The C programming lanugage by K&R, 2nd ed

    size_t tmp = 1;
    while(*cs == *ct)
    {
        if(tmp > n || n == 0)
            return 0;
        if(*cs == '\0')
            // Found the end of the first string.
            return 0;
        cs++;
        ct++;
        tmp++;
    }
    return *cs - *ct;
}

void displayBuffer(char *buff)
{
    // Check for NULL
    char *b = buff;
    if (!buff) return;
    // Assumes that buff is null terminated C-string
    while (*buff) {
        putchar(*buff);
        buff++;
    }
    printf("\n");
    printf("Length of the buffer is %zu\n", buff - b);
    putchar('\n');
}

int main()
{
    /* char buffer1[128] = {'\0'}; */
    char buffer1[128] = "Bhis";
    char buffer2[128] = {'\0'};
    /*
        // Array of 126 ones and one 2
        char *ones =
            "1111111111111111111111111111111111111111111111111111111111111111111111"
            "111111111111111111111111111111111111111111111111111111112";

        strlcpy_(buffer1, ones, 128);

        displayBuffer(buffer1);
        */
    char *h = "hello_";
    char *w = " world";
    /* strncat_(buffer1, h, 6);
     * displayBuffer(buffer1); */
    // strncat_(buffer1, w, 16);
    printf("%d\n", strncmp_(buffer1, "Bhxa", 1));
    // displayBuffer(buffer1);
}
/*
 *
11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
111111111111 \¿
*/
