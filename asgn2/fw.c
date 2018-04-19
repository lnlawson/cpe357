/*Name: Logan Lawson
**Assignment 2 : fw.c*/

#include "fw.h"
#include "readline.h"

int size = SIZE;
int amount = 0;

int main(int argc, char const *argv[])
{
	FILE *file;
	void *hashTable = NULL;
	char *curline = NULL;

	int code = NULL;

	if (NULL == (file = fopen(argv[1], "r"))){
		perror(__FUNCTION__);
		exit(-1);
	}

	while (NULL != (curline = readline(file))){
		if( NULL==(hashTable=malloc(size * sizeof(HashItem *))) ) { 
			perror(__FUNCTION__);
			exit(-1);
		}
		procLine(&hashTable, &curline);

	for (int k=0; k<size; ++k){
		if (hashTable[k] != NULL){
			printf("%s\n", hashTable[k]->word);
			printf("%d\n", hashTable[k]->occur);
		}
	}
	return 0;
}

void procLine(void *table, char *curline){
		char *compTok = NULL;
		char *curword = NULL;
		compTok = strtok(curline, " ,./;'[]<>?:\"{}|*");
			while (compTok != NULL){
				for (int i = 0; compTok[i] != '\0'; ++i){
					if (isdigit(compTok[i])){
						compTok = strtok(NULL, " ,./;'[]<>?:\"{}|*");
						break;
					}
					tolower(compTok[i]);
					if (compTok[i+1] == '\0'){
						if(NULL==(curword=(char*)malloc(i+1 * sizeof(char)))) { 
							perror(__FUNCTION__);
							exit(-1);
						}
						strcpy(curword, compTok);
						curword[i+1] = '\0';
						code = hashCode(&curword, size);
						if (hashTable[code] != NULL){
							cyclingHashTable(&hashTable, code, &curword, size);
							compTok = strtok(NULL, " ,./;'[]<>?:\"{}|*");
							break;
						}
						createItem(&hashTable, code, &curword);
						amount += 1;
						compTok = strtok(NULL, " ,./;'[]<>?:\"{}|*");
						break;
					}
				}
			}
}


void cyclingHashTable(void *table, int index, char *word){
	for (int j = 1; table[index] != NULL; ++j){
		index = quadProbing(index, j, size);
		if ( !(strcmp(hashTable[index]->word, curword)) ) {
			hashTable[index]->occur += 1;
			break;
		}
		if (table[index] == NULL){
			createItem(&table, index, &word);
			amount += 1;
			break;
		}
	}
	return;
}

void createItem(void *table, int index, char *word){
	table[index] = malloc(sizeof(HashItem));
	table[index]->word = word;
	table[index]->occur = 1;
	return;
}

int quadProbing(int index, int inc){
	int newindex;
	newindex = (index + (inc * inc)) % size;
	return newindex; 
}

int hashCode(char *value){
	for (int i = 0, asval = 0; *(value + i) != '\0'; ++i)
	{
		asval += (int)(*(value + i));
	}
	return asval % size;
}

