#ifndef TODO_H
#define TODO_H

#include <stdio.h>

#include "date.h"

typedef struct {
	int completed;
	char description[201];
	Date date;
} Todo;

void printTodo(Todo *todo) {
	printf("\t- ");
	
	if (todo->completed) {
		printf("[DONE] ");
	}

	printf("%s\n", todo->description);
}

#endif
