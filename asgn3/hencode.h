/*Name: Logan Lawson
**Assignment 3 : hencode*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

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

typedef struct path
{
	char path[256];
	int len;
}PathCode;



//FUNCTIONS:
void initTable(void);
void fillTable(FILE *file);
treeNode **buildList(treeNode **list, int *count);
treeNode **buildTree(treeNode **list, int *count);
PathCode **encodeTable(treeNode *list);
char *getPath(treeNode *node, char character, char *path, int index);
void writeHeader(FILE *outfile, FILE *infile, int *count);
void writeBits(FILE *outfile, FILE *infile, PathCode **codeTable);
int calcBinInt(char *byte);

int freeTree(treeNode *node);
void FreeTable(PathCode **codeTable);


int compFunction1(const void *a, const void *b);
int compFunction2(const void *a, const void *b);


int table[256];
