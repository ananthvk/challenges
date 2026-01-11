#include <stdio.h>

float celsiusToFarenheit(float c) { return (9.0 / 5.0) * c + 32.0; }
int main()
{
    for (int i = 0; i <= 100; i += 1) {
        printf("%-7d%-7.2f\n", i, celsiusToFarenheit(i));
    }
}
