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

DateMapNode* search(DateMapNode *root, Date date) {
	if (root == NULL) {
		return root;
	} 
	
	int cRes = compareDates(root->date, date);
	if (cRes == 0) {
		return root;
	}
	else if (cRes > 0) {
		// means date < root->date
		return search(root->left, date);
	} else {
		// means date > root->date
		return search(root->right, date);
	}
}

DateMapNode* findMinimum(DateMapNode *root) {
	if (root == NULL) {
		return NULL;
	} else if (root->left != NULL) {
		return findMinimum(root->left);
	}
	return root;
}

DateMapNode *createNode(Date date) {
	DateMapNode *p;
	p = malloc(sizeof(DateMapNode));
	p->date = date;
	p->todos = NULL;
	p->left = NULL;
	p->right = NULL;
	p->numTodos = 0;
	return p;
}

DateMapNode *insertNode(DateMapNode *root, Date date) {
	if (root == NULL) {
		return createNode(date);
	}
	int cRes = compareDates(root->date, date);
	if (cRes > 0) {
		root->left = insertNode(root->left, date);

		root->right = insertNode(root->right, date);
	}
	return root;
}

DateMapNode *removeNode(DateMapNode *root, Date date, int freeTodos) {
	int cRes = compareDates(root->date, date);
	if (root == NULL) {
		return NULL;
	} else if (cRes > 0) {
		root->left = removeNode(root->left, date, 1);
	} else if (cRes < 0) {
		root->right = removeNode(root->right, date, 1);
	} else {
		if (root->left == NULL && root->right == NULL) {
			if (root->todos != NULL && freeTodos == 1)
				free(root->todos);
			free(root);
			return NULL;
		} else if (root->left == NULL || root->right == NULL) {
			DateMapNode *temp;
			if (root->left == NULL) {
				temp = root->right;
			} else {
				temp = root->left;
			}
			if (root->todos != NULL && freeTodos == 1)
				free(root->todos);
			free(root);
			return temp;
		} else {
			DateMapNode *temp = findMinimum(root);
			root->numTodos = temp->numTodos;
			root->todos = temp->todos;
			root->date = temp->date;
			// Don't remove the todos because we're using them in temp
			removeNode(root->right, temp->date, 0);
		}
	}

	return root;
}

void printInOrder(DateMapNode *root) {
	if (root != NULL) {
		printInOrder(root->left);
		printf(" ");
		printDate(root->date);
		printf(" ");
		printInOrder(root->right);
		printf(" ");
	}
}

DateMapNode *insertExistingNode(DateMapNode *root, DateMapNode newNode) {
	if (root == NULL) {
		DateMapNode *p;
		p = malloc(sizeof(DateMapNode));
		p->date = newNode.date;
		p->todos = newNode.todos;
		p->left = newNode.left;
		p->right = newNode.right;
		p->numTodos = newNode.numTodos;
		return p;
	}
	int cRes = compareDates(root->date, newNode.date);
	if (cRes > 0) {
		root->left = insertExistingNode(root->left, newNode);
	} else {
		root->right = insertExistingNode(root->right, newNode);
	}
	return root;
}

void printNodeTodos(DateMapNode *node) {
	if (node != NULL) {
		for (int i = 0; i < node->numTodos; i++) {
			printTodo(&node->todos[i]);
		}
	}
}

DateMapNode *addTodoNode(DateMapNode *root, Todo newTodo) {
	if (root == NULL) {
		DateMapNode *p;
		p = malloc(sizeof(DateMapNode));
		Todo *todos = malloc(sizeof(Todo));
		todos[0] = newTodo;

		p->date = newTodo.date;
		p->todos = todos;
		p->left = NULL;
		p->right = NULL;
		p->numTodos = 1;
		return p;
	}

	int cRes = compareDates(root->date, newTodo.date);
	if (cRes > 0) {
		root->left = addTodoNode(root->left, newTodo);
	} else if (cRes < 0) {
		root->right = addTodoNode(root->right, newTodo);
	} else {
		// if we've found the existing node
		int size = root->numTodos + 1;
		Todo *todo = root->todos;
		root->todos = realloc(todo, sizeof(Todo)*size);
		root->todos[size - 1] = newTodo;
		root->numTodos = size;
	}

	return root;
}

DateMapNode *removeNodeTodo(DateMapNode *node, int todoIndex) {
	if (node == NULL || todoIndex < 0 || todoIndex >= node->numTodos) {
		return node;
	}
	
	// TODO: I think the above could be made more efficient using memcpy.
	Todo *newTodos = malloc(sizeof(Todo)*(node->numTodos - 1));
	int offset = 0;
	for (int i = 0; i < node->numTodos; i++) {
		if (i != todoIndex) {
			newTodos[i - offset] = node->todos[i];
		} else {
			offset++;
		}
	}

	node->numTodos -= 1;
	free(node->todos);
	node->todos = newTodos;

	return node;
}

DateMapNode *completeNodeTodo(DateMapNode *node, int todoIndex) {
	if (node == NULL || todoIndex < 0 || todoIndex >= node->numTodos) {
		return node;
	}
	
	for (int i = 0; i < node->numTodos; i++) {
		node->todos[i].completed = 1;
	}

	return node;
}

#endif
