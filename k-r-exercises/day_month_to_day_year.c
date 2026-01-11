/* Let us define two functions to do the conversions: day_of_year converts the
 * month and day into the day of the year, and month_day converts the day of the
 * year into the month and day. Since this latter function computes two values,
 * the month and day arguments will be pointers: */

static char daymap[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day)
{
    // Check if year is valid
    if(year < 0)
        return -1;

    // Check if month is valid
    if(!(month >= 1 && month <= 12))
    {
        return -2;
    }

    // Check if day is valid
    if(!(day >= 1 && day <= 31))
    {
        return -3;
    }
    /*
     * Returns the day of year which corresponds to the day of the given month.
     */
    int leap = ((year % 4 == 0) && year % 100 != 0) || (year % 400 == 0);
    for (int i = 1; i < month; i++) day += daymap[leap][i];
    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
    if(pmonth)
        *pmonth = 0;
    if(pday)
        *pday = 0;

    int i, leap;
    leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);

    // Check if yearday is valid
    if(!(yearday >= 0 && yearday <= 366) && leap)
    {
        // A leap year
        return -1;
    }
    else if(!(yearday >= 0 && yearday <= 365))
    {
        // Not a leap year
        return -2;
    }

    if(year < 0)
    {
        return -3;
    }

    for (i = 1; yearday > daymap[leap][i]; i++) yearday -= daymap[leap][i];

    if(pmonth)
        *pmonth = i;
    if(pday)
        *pday = yearday;
    return 1;
}
#include <stdio.h>
int main()
{
    int m, d;
    month_day(2022, 400, &m, &d);
    printf("%d\n", day_of_year(2022, 8, 32));
    printf("%d %d\n", m, d );
}
