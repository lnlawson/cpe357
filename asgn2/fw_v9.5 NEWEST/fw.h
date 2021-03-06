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

void printOutput(HashItem **table, int *amount, int nflag);

char *procWord(char *line);

HashItem **procInput(HashItem **table, int agc, char const *agv[], int *size, int *amount, int *n);

HashItem **procFile(HashItem **table, FILE *file, int *size, int *amount, int *nflag);

HashItem **procLine(HashItem **table, char *curline, int *size, int *amount);

HashItem **reHashTable(HashItem **table, int *size, int *amount);

HashItem **FreeTable(HashItem **tabl, int *size);

HashItem **filterTable(HashItem **temptable, int *size, int *amount, int nflag);

int loadFactor(int *amount, int *size);

int compFunction(const void *a, const void *b);

#endif
