#include <stdio.h>
#define RANGE_START 300
#define RANGE_END 0
#define STEP -20

// Program to print the corresponding Celsius to Fahreheit table.
int main()
{
    float temperatureInF = 0;

    printf("%8s%11s\n", "CELSIUS", "FAHRENHEIT");
    for (int temperatureInC = RANGE_START; temperatureInC >= RANGE_END;
         temperatureInC += STEP) {
        temperatureInF = ((9.0 / 5.0) * temperatureInC) + 32;
        printf("%-8d%11.2f\n", temperatureInC, temperatureInF);
    }
    return 0;
}
