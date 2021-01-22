#ifndef DATEMAP_H
#define DATEMAP_H

#include "todo.h"
#include "date.h"
#include <stdlib.h>

typedef struct DateMapNode DateMapNode;

struct DateMapNode {
	Date date;
	Todo *todos;
	int numTodos;
	DateMapNode *left;
	DateMapNode *right;
};

DateMapNode* search(DateMapNode *root, Date date);

DateMapNode* findMinimum(DateMapNode *root);

DateMapNode *createNode(Date date);

DateMapNode *insertNode(DateMapNode *root, Date date);

DateMapNode *removeNode(DateMapNode *root, Date date, int freeTodos);

void printInOrder(DateMapNode *root);

DateMapNode *insertExistingNode(DateMapNode *root, DateMapNode newNode);

void printNodeTodos(DateMapNode *node);

DateMapNode *addTodoNode(DateMapNode *root, Todo newTodo);

DateMapNode *removeNodeTodo(DateMapNode *node, int todoIndex);

DateMapNode *completeNodeTodo(DateMapNode *node, int todoIndex, int completeVal);

#endif
