/* Exercise 5-2. Write getfloat, the floating-point analog of
 * getint. What type does
 * getfloat return as its function value? */
#include <ctype.h>
#include <stdio.h>

// Code for handling the getch and ungetch
#define getch() (cp > 0) ? (charbuffer[--cp]) : getchar()
#define ungetch(ch)                                                     \
    {                                                                   \
        if (cp >= CHARBUFFSIZE)                                         \
            printf("Temporary buffer stack is full, cant push back\n"); \
        else                                                            \
            charbuffer[cp++] = (char)ch;                                \
    }

#define CHARBUFFSIZE 100
int cp = 0;

char charbuffer[CHARBUFFSIZE] = {'\0'};
int getfloat(double *dbl)
{
    int ch, sign, tmp;
    double power = 1;
    double result;
    // Skip whitespaces, tabs, etc
    while (isspace(ch = getch()))
        ;

    // Gets the sign (if any)
    if (ch == '+' || ch == '-') {
        sign = (ch == '-') ? -1 : 1;
        tmp = getch();
        // The next character after the sign is not a digit.
        // Example: +a , -z, etc
        // Note: This means that this program does not support  decimal numbers
        // such as -.3, +.2, etc.
        if (!isdigit(tmp)) {
            // Un-gets the the sign and the character which was read
            ungetch(tmp) ungetch(ch) return 0;
        }
        ch = tmp;
    }
    else if (isdigit(ch)) {
        // The number does not include any sign, for example 312, 123, 312.123,
        // etc. The number is assumed to be positive.
        sign = 1;
    }
    else {
        // Invalid character.
        // Note: Numbers such as .32, .12, etc become invalid.
        ungetch(ch) return 0;
    }
    *dbl = 0;
    while (isdigit(ch)) {
        *dbl = *dbl * 10.0 + (ch - '0');
        ch = getch();
    }

    if (ch == '.') {
        // There might be a fractional part here.
        tmp = getch();
        // Check if the next character after the dot is an number.
        if (!isdigit(tmp)) {
            // Un-gets the the sign and the character which was read
            // Note: Inputs such as 312. , 123. or 112.a are valid and will be
            // considered only upto the decimal dot
            ungetch(tmp) ungetch(ch)
        }
        else {
            ch = tmp;
            while (isdigit(ch)) {
                *dbl = *dbl * 10.0 + (ch - '0');
                power /= 10.0;
                ch = getch();
            }
            // Ungets the character which was not a digit.
            if (ch != EOF) ungetch(ch)
        }
    }
    else {
        // Un-gets the non digit number which was read.
        if (ch != EOF) ungetch(ch)
    }
    *dbl *= power;
    *dbl *= sign;
    return 1;
}
int main()
{
    double var;
    if (getfloat(&var)) {
        printf("%.15g\n", var);
    }
    else {
        printf("%s\n", "Invalid floating point number");
    }
}
