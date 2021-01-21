#ifndef S_DATE_H
#define S_DATE_H

#include <stdlib.h>
#include <string.h>

typedef struct {
	int day;	// 1-31
	int month;	// 0-11
	int year;	// current year, i.e. 2021
} Date;

int compareDates(Date date1, Date date2) {
	int dateInt1 = date1.year * 10000 + date1.month * 100 + date1.day;
	int dateInt2 = date2.year * 10000 + date2.month * 100 + date2.day;

	if (dateInt1 < dateInt2) {
		return -1;
	} else if (dateInt1 == dateInt2) {
		return 0;
	}
	return 1;
}

void printDate(Date date) {
	printf("%d/%d/%d", date.year, date.month, date.day);
}

// string of the format dd/mm/yyyy
Date stringToDate(char *s) {
	Date d = {0};
	
	int i = 0;
	int vals[3] = {0};
	char *tok = strtok(s, "/");
	while (tok != NULL && i < 3) {
		vals[i++] = atoi(tok);
		tok = strtok(NULL, "/");
	}

	if (i >= 3) {
		d.day = vals[0];
		d.month = vals[1];
		d.year = vals[2];
	}

	return d;
}

#endif
