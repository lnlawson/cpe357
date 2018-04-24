/*Name: Logan Lawson
**Assignment 2 : fw.c*/

#ifndef FW_H
#define FW_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct hashitem
{
	int occur;
	int ascival;
	char *word;

}HashItem;

int hashCode(int asval, int *size);

int asciiAdd(char *value);

int quadProbing(int index, int inc, int *size);

void createItem(HashItem **table, int index, char *word, int asval, int len);

int cyclingHashTable(HashItem **table, int ind, char *word, int asval, int *size, int *amount, int len, int mode);

HashItem **procFile(HashItem **table, FILE *file, int *size, int *amount);

HashItem **procLine(HashItem **table, char *curline, int *size, int *amount);

HashItem **reHashTable(HashItem **table, int *size, int *amount);

HashItem **FreeTable(HashItem **tabl, int *size);

HashItem **filterTable(HashItem **temptable, int *size, int *amount);

int loadFactor(int *amount, int *size);


#endif
