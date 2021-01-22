#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todo.h"
#include "datemap.h"
#include "date.h"

// Write the DateMapNodes to a file in preorder (root, left, right).  This 
// should mean that when we read them, they will recreate the BST, right?
void writeDateMapNodes(FILE *file, DateMapNode *root) {
	if (root != NULL && file != NULL) {
		fwrite(&(root->date), sizeof(Date), 1, file);
		fwrite(&(root->numTodos), sizeof(int), 1, file);
		fwrite(root->todos, sizeof(Todo), root->numTodos, file);

		writeDateMapNodes(file, root->left);
		writeDateMapNodes(file, root->right);
	}
}

DateMapNode *readDateMapNodes(FILE *file) {
	if (file != NULL) {
		// read each datemapnode from the file, adding them to the bst
		DateMapNode *root = NULL;
		Date rDate;

		fread(&rDate, sizeof(rDate), 1, file);
		while (!feof(file)) {
			int numTodos;
			fread(&numTodos, sizeof(int), 1, file);
			
			Todo *todos = malloc(sizeof(Todo)*numTodos);
			fread(todos, sizeof(Todo), numTodos, file);
			
			DateMapNode newNode = {rDate, todos, numTodos, NULL, NULL};
			root = insertExistingNode(root, newNode);
			
			fread(&rDate, sizeof(rDate), 1, file);
		}

		return root;
	}
	return NULL;
}

void cleanUpTree(DateMapNode *root) {
	while (root != NULL) {
		root = removeNode(root, root->date, 1);
	}
}

void printCurrentDate() {
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char s[64];
	strftime(s, sizeof(s), "%c", tm);
	printf("%s\n", s);
}

DateMapNode *loadFromFile() {
	FILE *file = fopen("test.dat", "rb");
	DateMapNode *root = readDateMapNodes(file);
	fclose(file);
	return root;
}

void writeToFile(DateMapNode *root) {
	FILE *file = fopen("test.dat", "wb");
	writeDateMapNodes(file, root);
	fclose(file);
}

void outputTodos(DateMapNode *root, Date date) {
	printf("===== Murdoch's TODOs =====\n");
	printCurrentDate();
	printf("Today's todos:\n");

	// read from the todos file 
	DateMapNode *foundNode = search(root, date);
	if (foundNode == NULL) {
		return;
	}
	printNodeTodos(foundNode);
}

DateMapNode *addTodo(DateMapNode *root) {
	printf("Enter the date for this todo (dd/mm/yyyy):\n");
	char dateString[11];
	fgets(dateString, 11, stdin);
	getchar();
	
	printf("Enter the description for this todo (max 200 chars):\n");
	char descString[201] = {0};
	fgets(descString, 201, stdin);

	// check and remove newline
	if (descString[strlen(descString)-1] == '\n') {
		descString[strlen(descString)-1] = '\0';
	}

	Date d = stringToDate(dateString);
	
	Todo newTodo;	// don't think there's any need to malloc
	newTodo.completed = 0;
	strncpy(newTodo.description, descString, 201);
	newTodo.date = d;
	
	// add newTodo to the appropriate node in root
	root = addTodoNode(root, newTodo);
	
	return root;
}

DateMapNode *removeTodo(DateMapNode *root) {
	printf("Enter the date for this todo (dd/mm/yyyy):\n");
	char dateString[11];
	fgets(dateString, 11, stdin);
	getchar();
	
	Date d = stringToDate(dateString);
	DateMapNode *node = search(root, d);
	if (node == NULL) {
		return root;
	}
	
	printf("Pick a todo to remove:\n");
	for (int i = 0; i < node->numTodos; i++) {
		printf("\t%d. %s\n", i, node->todos[i].description);
	}
	
	int choice;
	printf("Enter the index of the todo to remove: ");
	scanf("%d", &choice);

	node = removeNodeTodo(node, choice);
	
	return root;
}

DateMapNode *completeTodo(DateMapNode *root, int completeVal) {
	printf("Enter the date for this todo (dd/mm/yyyy):\n");
	char dateString[11];
	fgets(dateString, 11, stdin);
	getchar();
	
	Date d = stringToDate(dateString);
	DateMapNode *node = search(root, d);
	if (node == NULL) {
		return root;
	}
	
	printf("Pick a todo to complete:\n");
	for (int i = 0; i < node->numTodos; i++) {
		printf("\t%d. %s\n", i, node->todos[i].description);
	}
	
	int choice;
	printf("Enter the index of the todo to complete: ");
	scanf("%d", &choice);

	node = completeNodeTodo(node, choice, completeVal);
	
	return root;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		DateMapNode *root = loadFromFile();
		outputTodos(root, getTodaysDate());
	} else if (argc == 2) {
		if (strcmp(argv[1], "add") == 0) {
			DateMapNode *root = loadFromFile();
			root = addTodo(root);
			writeToFile(root);
			cleanUpTree(root);
		} else if (strcmp(argv[1], "remove") == 0) {
			DateMapNode *root = loadFromFile();
			root = removeTodo(root);
			writeToFile(root);
			cleanUpTree(root);
		} else if (strcmp(argv[1], "complete") == 0) {
			DateMapNode *root = loadFromFile();
			root = completeTodo(root, 1);
			writeToFile(root);
			cleanUpTree(root);
		} else if (strcmp(argv[1], "ncomplete") == 0) {
			DateMapNode *root = loadFromFile();
			root = completeTodo(root, 0);
			writeToFile(root);
			cleanUpTree(root);
		} else {
			DateMapNode *root = loadFromFile();
			Date d = stringToDate(argv[1]);
			outputTodos(root, d);
			cleanUpTree(root);
		}
	}
}
