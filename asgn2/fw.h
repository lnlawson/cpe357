/*Name: Logan Lawson
**Assignment 2 : fw.c*/

#ifndef FW_H
#define FW_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 101

typedef struct hashitem
{
	long int occur;
	char *word;

}HashItem;

int hashCode(char *value);

int quadProbing(int index, int inc);

void createItem(HashItem **table, int index, char *word);

void cyclingHashTable(HashItem **table, int index, char *word);

void procLine(HashItem **table, char *curline);




#endif