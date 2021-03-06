#include <stdio.h>
#include <stdlib.h>


typedef struct tree treeNode;

struct tree{
	char character;
	int val;
	treeNode *right;
	treeNode *left;
	int huffVal;
};


typedef struct item{
	int val;
	int occur;
}Item;



//FUNCTIONS:
void initTable(void);
void fillTable(FILE *file);
treeNode **buildList(treeNode **list, int *count);
treeNode **buildTree(treeNode **list, int *count);
char  **encodeTable(treeNode *list);
char *getPath(treeNode *node, char character, char *path, int index);
int compFunction1(const void *a, const void *b);
int compFunction2(const void *a, const void *b);


int table[256];
