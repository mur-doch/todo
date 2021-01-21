#include "todo.h"
#include <stdlib.h>

typedef struct {
	int day;
	int month;
	int year;
} Date;

int compareDates(Date date1, Date date2) {
	int dateInt1 = date1.year * 10000 + date1.month * 100 + date1.day;
	int dateInt2 = date2.year * 10000 + date2.month * 100 + date2.day;

	if (dateInt1 < dateInt2) {
		return -1;
	} else if (dateInt1 == dateInt2) {
		return 0;
	}
	return 1;
}

void printDate(Date date) {
	printf("%d/%d/%d", date.year, date.month, date.day);
}

typedef struct DateMapNode DateMapNode;

struct DateMapNode {
	Date date;
	Todo *todos;
	int numTodos;
	DateMapNode *left;
	DateMapNode *right;
};

DateMapNode* search(DateMapNode *root, Date date) {
	int cRes = compareDates(root->date, date);
	if (root == NULL || cRes == 0) {
		return root;
	} else if (cRes > 0) {
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

DateMapNode *removeNode(DateMapNode *root, Date date) {
	int cRes = compareDates(root->date, date);
	if (root == NULL) {
		return NULL;
	} else if (cRes > 0) {
		root->left = removeNode(root->left, date);
	} else if (cRes < 0) {
		root->right = removeNode(root->right, date);
	} else {
		if (root->left == NULL && root->right == NULL) {
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
			free(root->todos);
			free(root);
			return temp;
		} else {
			DateMapNode *temp = findMinimum(root);
			root->todos = temp->todos;
			root->date = temp->date;
			removeNode(root->right, temp->date);
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

/*
DateMapNode *getDateMapNode(DateMapNode *root, Date date) {
	//int cRes = compareDates(root->date, date);
	//if (cRes == -1) {
	//	return getDateMapNode(root->left, date);
	//} else if (cRes == 1) {
	//	return getDateMapNode(root->right, date);
	//}
	//return root;
	
	DateMapNode *cur = root;
	while (cur != NULL) {
		int cRes = compareDates(cur->date, date);
		if (cRes == 0) {
			return cur;
		} else if (cRes < 0) {
			// root->date < date
			cur = cur->right;
		} else if (cRes > 0) {
			// root->date > date
			cur = cur->left;
		}
	}
	return cur;
}


void addDateMapNode(DateMapNode **rootPtrPtr, DateMapNode *toAdd) {
	// TODO
	if (rootPtrPtr == NULL) {
		return;
	}
	// need the check above because otherwise we're dereferencing a pointer to nothing
	// what we really meant was that the rootPtr (or *rootPtrPtr) if null, should be
	// set to toadd
	DateMapNode *cur = *rootPtrPtr;
	DateMapNode **curP = rootPtrPtr;
	while (cur != NULL) {
		int cRes = compareDates(cur->date, toAdd->date);
		if (cRes == -1) {
			// cur->date < toAdd->date
			cur = cur->right;
			curP = &cur->right;
		} else if (cRes == 1) {
			// cur->date > toAdd->date
			cur = cur->left;
			curP = &cur->left;
		} 
		// TODO: want to merge the todos
		//else if (cRes == 0) {
		//
		//}
	}

	//if (curP != NULL) {
	//	*curP = toAdd;
	//} else {
	//	*rootPtrPtr = toAdd;
	//}
	*curP = toAdd;
}

void removeDateMapNode(DateMapNode *root, Date toRemove) {
	// basically to remove this from the tree we need to find its parent and set 
	// the reference to null
	// we only need to free() it if we use malloc to set it... we don't know if we'll be 
	// doing that yet.
	// TODO: Do we need to free() toRemove?  It's basically all going to be in 
	// the main of this project.
	
	DateMapNode *cur = root;
	while (1) {
		int cRes = compareDates(root->date, date);
		if (cRes == -1) {
			return getDateMapNode(root->left, date);
		} else if (cRes == 1) {
			return getDateMapNode(root->right, date);
		}
		return root;
	}
}*/
