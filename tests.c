#include <stdio.h>
#include <stdlib.h>

#include "todo.h"
#include "datemap.h"

int main() {
	Date date1 = {31, 1, 2000};
	Date date2 = {27, 8, 2010};
	Date date3 = {13, 10, 2020};
	//int r = compareDates(date1, date1);
	//printf("%d", r);
	DateMapNode left;
	left.date = date1;
	left.todos = NULL;
	left.left = NULL;
	left.right = NULL;
	
	DateMapNode right;
	right.date = date3;
	right.todos = NULL;
	right.left = NULL;
	right.right = NULL;
	
	DateMapNode root;
	root.date = date2;
	root.todos = NULL;
	root.left = &left;
	root.right = &right;
	
	Date date4 = {13, 20, 2020};
	//DateMapNode *res = getDateMapNode(&root, date4);
	//printf("Date Found: %d\n", res);
	
	printInOrder(&root);
	
	char s[] = "HELLO WORLD";
	FILE *file = fopen("test.dat", "wb");
	fwrite(s, 12, 1, file);
	fclose(file);
	
	//DateMapNode new;
	//new.date = date4;
	//new.todos = NULL;
	//new.left = NULL;
	//new.right = NULL;
	//
	////DateMapNode *rPtr = &root;
	//DateMapNode *rPtr = NULL;
	//DateMapNode **rPtrPtr = &rPtr;
	//addDateMapNode(rPtrPtr, &new);
	//
	//DateMapNode nodes[5] = {root, left, right, new};
	//char names[5][6] = {"root", "left", "right", "new"};
	//for (int i = 0; i < 4; i++) {
	//	printf("%s\n");
	//	printf("Date: %d/%d/%d\n", nodes[i].date.year, nodes[i].date.month, nodes[i].date.day);
	//	printf("Address: %p\n", &nodes[i]); 
	//	printf("Left: %p\n", &nodes[i].left);
	//	printf("Right: %p\n", &nodes[i].right);
	//}

	//printf("right->right: %p\n", (void*)right.right);
	//printf("rPtr: %p\n", (void *)rPtr);
}
