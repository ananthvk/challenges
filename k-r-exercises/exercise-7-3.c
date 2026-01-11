#include <stdarg.h>
#include<stdio.h>

void my_printf(const char *fmt, ...)
{
    va_list ap;
    double fval;
    int ival;
    unsigned int uval;
    char *s;
    va_start(ap, fmt);
    const char *fmt_ptr = fmt;
    for (fmt_ptr = fmt; *fmt_ptr != '\0'; fmt_ptr++) {
        if (*fmt_ptr != '%') {
            putchar(*fmt_ptr);
        }
        else {
            switch(*++fmt_ptr)
            {
                case 'd':
                case 'i':
                    ival = va_arg(ap, int);
                    printf("%d", ival);
                    break;
                case 'u':
                    uval = va_arg(ap, unsigned int);
                    printf("%u", uval);
                    break;
                case 'f':
                    fval = va_arg(ap, double);
                    printf("%f", fval);
                    break;
                case 's':
                    s = va_arg(ap, char *);
                    if(s == NULL) break;
                    while(*s)
                    {
                        putchar(*s++);
                    }
                    break;
                default:
                    putchar(*fmt_ptr);
                    break;
            }
        }
    }
    va_end(ap);
}

int main()
{
    my_printf(":%s:\n", "This is a string!");
    my_printf("%s%d\n", "This is a number!:", 71);
}