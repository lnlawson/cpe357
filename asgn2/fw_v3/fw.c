/*Name: Logan Lawson
**Assignment 2 : fw.c*/

#include "fw.h"
#include "readline.h"

int size = SIZE;
int amount = 0;

int main(int argc, char const *argv[])
{
        printf("made it in main\n");
	FILE *file;
	HashItem **hashTable = NULL;
	//char *curline = NULL;

	if (NULL == (file = fopen(argv[1], "r"))){
		perror(__FUNCTION__);
		exit(-1);
	}

	/*while (NULL != (curline = readline(file))){
		if( NULL==(hashTable=(HashItem**)malloc(size)) ) { 
			perror(__FUNCTION__);
			exit(-1);
		}
		procLine(hashTable, curline);
	}*/
        procFile(hashTable, file);

	for (int k=0; k<size; ++k){
		if ((hashTable[k]) != NULL){
			printf("%s\n", hashTable[k]->word);
			printf("%ld\n", hashTable[k]->occur);
		}
	}
	return 0;
}

////////////////////////////function for processing file

void procFile(HashItem **table, FILE *file){
   printf("made it to procFile\n");
   char *current = readline(file);
   while (current != NULL){
      printf("current: %s\n",current);
      table = (HashItem**)calloc(size, sizeof(HashItem*)); 
      if(table == NULL){
         printf("problem with mallocing table\n");
         perror(__FUNCTION__);
         exit(-1);
      }
      printf("before procLine\n");
      procLine(table, current);
      printf("after procLine\n");
      current = readline(file);

   }

}

////////////////////////////

void procLine(HashItem **table, char *curline){
                printf("made it in procLine\n");
		char *compTok = NULL;
		char *curword = NULL;
		int code;
		compTok = strtok(curline, " ,./;'[]<>?:\"{}|*");
			while (compTok != NULL){
				if (loadFactor(amount, size)){
					reHashTable(table);
				}
				for (int i = 0; compTok[i] != '\0'; ++i){
					if (isdigit(compTok[i])){
						compTok = strtok(NULL, " ,./;'[]<>?:\"{}|*");
						break;
					}
					compTok[i] = tolower(compTok[i]);
					if (compTok[i+1] == '\0'){
						printf("hi\n");
						if(NULL==(curword=(char*)realloc(curword,(i+1) * sizeof(char)))) { 
							perror(__FUNCTION__);
							exit(-1);
						}
						//printf("curword: %s\n", curword);
						//printf("compTok: %s\n", compTok);
						strcpy(curword, compTok);
						printf("herro: 1\n");
						curword[i+1] = '\0';
						printf("herro: 2\n");
						printf("compTok: %s\n", compTok);
						printf("curword: %s\n", curword);
						code = hashCode(curword);
						printf("%d\n", code);
						printf("herro: 3\n");
						//printf("table[index]: %s\n", table[code]->word);
						if ((table[code]) != NULL){
							printf("herro: 4\n");
							cyclingHashTable(table, code, curword, 0);/////////////////////
							compTok = strtok(NULL, " ,./;'[]<>?:\"{}|*");
							break;
						}
						printf("herro: 5\n");
						createItem(table, code, curword);
						printf("herro: 6\n");
						amount += 1;
						compTok = strtok(NULL, " ,./;'[]<>?:\"{}|*");
						break;
					}
				}
			}
}

int loadFactor(int amount, int size){/////////////////////////////
	float refactorVal = .85;
	if (((float)amount / size) > refactorVal){
		return 1;
	}
	return 0;
}//////////////////////////////////////////////^

HashItem **reHashTable(HashItem **table){								//////////////////////////////////////////////////
	int oldSize = size;
	int newcode;
	int index;
	size *= 2;
	HashItem **tempTable = table;
	HashItem **hashTable;

	if( NULL==(hashTable=(HashItem**)malloc(size * sizeof(HashItem*))) ) { 
		perror(__FUNCTION__);
		exit(-1);
		}

	for (int o = 0; o < oldSize; ++o){
		if (tempTable[o] != NULL){
			newcode = hashCode(tempTable[o]->word);
			
			if (hashTable[newcode] != NULL){
				index = cyclingHashTable(hashTable, newcode, tempTable[o]->word, 1);	//////////////////////
				hashTable[index]->occur = tempTable[o]->occur;

			} else{
				createItem(hashTable, newcode, tempTable[o]->word);
				hashTable[newcode]->occur = tempTable[o]->occur;
			}
		}
	}
	return hashTable;
}																						//////////////////////////////////////////////////////^^^^^^^^^^^^

int cyclingHashTable(HashItem **table, int ind, char *word, int mode){/////////////////////////
	int index = ind;
	for (int j = 0; table[index] != NULL; ++j){
		printf("herro: 7\n");
		index = quadProbing(index, j);
		if (!mode){
			printf("herro: 8\n");
			if (table[index] == NULL){
				printf("herro: 9\n");
				createItem(table, index, word);
				printf("herro: 10\n");
				amount += 1;
				break;
			
			} else if ( !(strcmp( (table[index])->word, word) )){
				printf("herro: 11\n");
				(table[index])->occur += 1;
				break;
			}
		}
		if (mode){
			if (table[index] == NULL){
				createItem(table, index, word);
				break;
			}
		}
	}
	return index;
}

void createItem(HashItem **table, int index, char *word){
	table[index] = malloc(sizeof(HashItem));
	(table[index])->word = word;
	(table[index])->occur = 1;
	return;
}

int quadProbing(int index, int inc){
	int newindex;
	newindex = (index + (inc * inc)) % size;
	return newindex; 
}

int hashCode(char *value){
	int asval = 0;
	for (int l = 0; *(value + l) != '\0'; ++l, asval += (int)(*(value + l)));

	return asval % size;
}

