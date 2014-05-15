
static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 51, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 51, 30, 31, 31, 30, 31, 30, 31},
};

/*
 * day_of_year: set day of year from month and day
 */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);

	if (month < 1 || month > 12)
		return -1;
	if (day < 1 || day > daytab[leap][month])
		return -1;

	for (i = 1; i < month; i++) {
		day += daytab[leap][i];
	}
	return day;
}

/*
 * month_day: set month, day from day of year
 * return value: 0 success;
 * 				-1 error
 */
int month_day(int year, int day, int *pmonth, int *pday)
{
	int i, leap;
	int	total;

	leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
	for (i = 1; i < sizeof(daytab[0])/sizeof(daytab[0][0]); i++) {
		if (day <= daytab[leap][i])
			break;
		day -= daytab[leap][i];
	}
	if (i == sizeof(daytab[0])/sizeof(daytab[0][0]))
		return -1;
	*pmonth = i;
	*pday = day;

	return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int month = 0;
	int day	= 0;

	month_day(2014, 33, &month, &day);
	fprintf(stdout, "day of year: %d, year: %d, month: %d, day: %d\n",
			day_of_year(2014, 2, 2), 2014, 2, 2);
	fprintf(stdout, "day of year: %d, month: %d, day: %d\n", 
			day_of_year(2014, 2, 2), month, day);
	exit(0);
}

