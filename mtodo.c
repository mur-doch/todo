#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "todo.h"
#include "datemap.h"

void printCurrentDate() {
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char s[64];
	strftime(s, sizeof(s), "%c", tm);
	printf("%s\n", s);
}

void getTodos() {
	printf("===== Murdoch's TODOs =====\n");
	printCurrentDate();
	printf("Today's todos:\n");
	// read from the todos file 
}

// Write the DateMapNodes to a file in preorder (root, left, right).  This 
// should mean that when we read them, they will recreate the BST, right?
void writeDateMapNodes(FILE *file, DateMapNode *root) {
	if (root != NULL && file != NULL) {
		// TODO: Need to write the todos separately.  All DateMapNode
		// holds is a pointer, and so the stored address won't point 
		// to anything now.
		// The only things that really need to be written are:
		// 	- date
		// 	- numTodos
		// 	- each of the todos
		fwrite(&(root->date), sizeof(Date), 1, file);
		fwrite(&(root->numTodos), sizeof(int), 1, file);
		for (int i = 0; i < root->numTodos; i++) {
			fwrite(&(root->todos[i]), sizeof(Todo), 1, file);
		}
		// TODO: Does this work?
		// fwrite(root->todos, sizeof(Todo), numTodos, file);

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
			for (int i = 0; i < numTodos; i++) {
				fread(&(todos[i]), sizeof(Todo), 1, file);
			}
			
			DateMapNode newNode = {rDate, todos, numTodos, NULL, NULL};
			root = insertExistingNode(root, newNode);
			
			fread(&rDate, sizeof(rDate), 1, file);
		}

		return root;
	}
	return NULL;
}

void cleanUpTree(DateMapNode *root) {
	// TODO: Remove everything
	//while (root != NULL) {
	//	removeNode(root, root->date);
	//}
	//removeNode(root, root->date);
}

int main(int argc, char* argv) {
	//if (argc == 1) {
	//	getTodos();
	//}
	// TODO: Create some DateMapNodes
	// Test writing and reading them.
	Todo todo1 = {0, "TODO 1", 31, 1, 2001};
	Todo todo2 = {0, "TODO 2", 12, 1, 2001};

	Todo todos1[] = {todo1, todo2};
	Todo todos2[] = {todo2};
	Date date1 = {31, 1, 2001};
	Date date2 = {12, 1, 2001};

	DateMapNode node1;
	node1 = (DateMapNode) {date1, todos1, 2, NULL, NULL};
	DateMapNode node2;
	node2 = (DateMapNode) {date2, todos2, 1, NULL, &node1};

	DateMapNode *root = &node2;
	
	FILE *file = fopen("test.dat", "wb");
	writeDateMapNodes(file, root);
	fclose(file);

	cleanUpTree(root);
	
	file = fopen("test.dat", "rb");
	DateMapNode *root2 = readDateMapNodes(file);
	fclose(file);
	
	printInOrder(root2);
	printf("%d\n", root2->numTodos);
	//printf("%s\n", root2->todos[0]);
	for (int i = 0; i < root2->numTodos; i++) {
		printf("DMN1: %s\n", root2->todos[i].description);
	}
}
