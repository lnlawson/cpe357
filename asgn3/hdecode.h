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
	unsigned char character;
	unsigned int val;
	treeNode *right;
	treeNode *left;
};


typedef struct item{
	unsigned int val;
	unsigned int occur;
}Item;

typedef struct path
{
	char path[400];
	unsigned int len;
}PathCode;


// Functions:
unsigned int readHeader(unsigned int infile);

void decode(unsigned int infile, unsigned int outfile, treeNode *tree, int *totalbits);

// unsigned int cyclingBuffs(int bitCount, int *decodedCharsCount, int outfile, char *decodedChars, char *codeBuff, treeNode *curNode, 
// 		treeNode *tree, int total, int totalBits);

void binIntToCode(uint8_t intCode, char *byteCode);

void initTable(void);
treeNode **buildList(treeNode **list);
treeNode **buildTree(treeNode **list, uint32_t *count);
PathCode  **encodeTable(treeNode *list, int *totalbits);
char *getPath(treeNode *node, char character, char *path, int index);

void freeTree(treeNode *node);
void freeTable(PathCode **codeTable);

int compFunction1(const void *a, const void *b);
int compFunction2(const void *a, const void *b);


unsigned int table[256];
