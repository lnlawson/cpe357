#include <stdio.h>
#include <stdlib.h>


typedef struct tree treeNode;

struct tree{
	char character;
	int val;
	treeNode *right;
	treeNode *left;
};


typedef struct item{
	int val;
	int occur;
}Item;



//FUNCTIONS:
void initTable(void);
void fillTable(FILE *file);
treeNode **buildList(treeNode **list, int *count);

int table[256];
