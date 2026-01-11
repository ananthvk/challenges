#include<stdio.h>

int cents, tmp;

int get_cents()
{
    int cents;
    printf("%s:", "Cents:");
    scanf("%d", &cents);
    printf("%s", "\n");
    return cents;
}

int calculate_quarters() 
{
    tmp = cents / 25;
    cents = cents % 25;
    return tmp;
}
int calculate_dimes()
{
    tmp = cents / 10;
    cents = cents % 10;
    return tmp;
}
int calculate_nickels()
{
    tmp = cents / 5;
    cents = cents % 5;
    return tmp;
}
int calculate_pennies()
{
    tmp = cents;
    cents = 0;
    return tmp;
}
int main()
{
    int tmp2;
    cents = get_cents();
    tmp2 = cents;
    int total = calculate_quarters()
    + calculate_dimes()
    + calculate_nickels()
    + calculate_pennies();
    printf("%d\n", total);

    cents = tmp2;
    printf("%d\n", calculate_quarters());
    printf("%d\n", calculate_dimes());
    printf("%d\n", calculate_nickels());
    printf("%d\n", calculate_pennies());
}
