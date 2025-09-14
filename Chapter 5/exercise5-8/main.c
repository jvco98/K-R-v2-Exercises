#include <stdio.h>

/*
 * Exercise 5-8. There is no error checking in day_of_year or month_day. Remedy this defect
 */

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(void) {
    int day =-1, month=-1, yearday=-1, year =-1;
    printf("enter month: ");
    fflush(stdout);
    scanf("%d", &month);
    printf("enter day: ");
    fflush(stdout);
    scanf("%d", &day);
    printf("enter year: ");
    fflush(stdout);
    scanf("%d", &year);
    yearday = day_of_year(year, month, day);
    month_day(year, yearday, &month, &day);
    fflush(stdout);
    if (yearday > 0)
        printf("day of the year: %d\n", yearday);
    if (year >0 && yearday >0)
        printf("month, day of the year = %d, %d\n",month, day);
    return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int flag = 0;
    if (year <= 0) {
        printf("invalid year format\n");
        flag = 1;
    }
    if (month <= 0 || month > 12) {
        printf("invalid month format\n");
        flag = 1;
    }
    if (day <= 0 || day > 31) {
        printf("invalid day format\n");
        flag = 1;
    }
    if (flag)
        return 1;
    else {
        int i, leap;
        leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
        for (i = 1; i < month; i++)
            day += daytab[leap][i];
        return day;
    }
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int flag = 0;

    if (year <= 0) {
        flag = 1;
        printf("invalid year format\n");
    }
    if (yearday <= 0 || yearday > 366) {
        flag = 1;
        printf("invalid day-of-year format\n");
    }
    if (!flag) {
        int i, leap;
        leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
        for (i = 1; yearday > daytab[leap][i]; i++)
            yearday -= daytab[leap][i];
        *pmonth = i;
        *pday = yearday;
    }
}