#include <stdio.h>
#define RANGE_MIN 0
#define RANGE_MAX 300
#define STEP 20

// Program to print the corresponding Celsius to Fahreheit table.
int main()
{
    float temperatureInF = 0;
    int temperatureInC = RANGE_MIN;
    printf("%8s%11s\n", "CELSIUS", "FAHRENHEIT");
    while (temperatureInC <= RANGE_MAX) {
        temperatureInF = ((9.0 / 5.0) * temperatureInC) + 32;
        printf("%-8d%11.2f\n", temperatureInC, temperatureInF);
        temperatureInC += STEP;
    }
    return 0;
}
