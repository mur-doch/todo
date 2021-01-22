#include "todo.h"

void printTodo(Todo *todo) {
	printf("\t- ");
	
	if (todo->completed) {
		printf("[DONE] ");
	}

	printf("%s\n", todo->description);
}
