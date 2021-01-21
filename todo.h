#ifndef TODO_H
#define TODO_H

typedef struct {
	int completed;
	char description[201];
	int day;
	int month;
	int year;
} Todo;

#endif
