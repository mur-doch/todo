#ifndef TODO_H
#define TODO_H

#include <stdio.h>

typedef struct {
	int completed;
	char description[201];
	int day;
	int month;
	int year;
} Todo;

void printTodo(Todo *todo) {
	printf("\t- ");
	
	if (todo->completed) {
		printf("[DONE] ");
	}

	printf("%s\n", todo->description);
}

#endif
