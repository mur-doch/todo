#ifndef S_DATE_H
#define S_DATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int day;	// 1-31
	int month;	// 0-11
	int year;	// current year, i.e. 2021
} Date;

int compareDates(Date date1, Date date2);

void printDate(Date date);

Date getTodaysDate();

// string of the format dd/mm/yyyy
Date stringToDate(char *s);

#endif
