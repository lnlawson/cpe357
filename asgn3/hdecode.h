/*Name: Logan Lawson
**Assignment 3 : hdecode*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


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


// Functions:
int readHeader(int infile);

void decode(int infile, int outfile,treeNode *tree, int *totalbits);

// int cyclingBuffs(int bitCount, int *decodedCharsCount, int outfile, char *decodedChars, char *codeBuff, treeNode *curNode, 
// 		treeNode *tree, int total, int totalBits);

void binIntToCode(uint8_t intCode, char *byteCode);

void initTable(void);
treeNode **buildList(treeNode **list);
treeNode **buildTree(treeNode **list, int *count);
PathCode  **encodeTable(treeNode *list, int *totalbits);
char *getPath(treeNode *node, char character, char *path, int index);

void freeTree(treeNode *node);
void freeTable(PathCode **codeTable);

int compFunction1(const void *a, const void *b);
int compFunction2(const void *a, const void *b);


int table[256];
