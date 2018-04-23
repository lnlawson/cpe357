/*Name: Logan Lawson
**Assignment 2 : fw.c*/

#include "fw.h"
#include "readline.h"



int main(int argc, char const *argv[])
{
        // printf("made it in main\n");
	FILE *file;
	HashItem **hashTable = NULL;
	int tableSize = 101;
	int tableAmount = 0;
	int *size = &tableSize;
	int *amount = &tableAmount;

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
   
   hashTable = procFile(hashTable, file, size, amount);

   printf("done\n");
	for (int k=0; k<*size; ++k){
		//printf("maybe\n");

		if ((hashTable[k]) != NULL){
			// if (hashTable[k]->occur>35)
			//{
			printf("hashTable[%d]: ", k);
			printf("%s\n", hashTable[k]->word);
			printf("occur: %d\n", hashTable[k]->occur);			}
		//}
	}
	hashTable = FreeTable(hashTable, size);
	free(hashTable);
	printf("ALL DONE!!!!!!!\n");
	return 0;
}

HashItem **procFile(HashItem **table, FILE *file, int *size, int *amount){
   // printf("made it to procFile\n");
   char *current = readline(file);
   table = (HashItem**)calloc(*size, sizeof(HashItem*)); 
	if(table == NULL){
	   printf("problem with mallocing table\n");
	   perror(__FUNCTION__);
	   exit(-1);
	}
   while (current != NULL){
      // printf("current: %s\n",current);
      // printf("%d\n", *size);
      // printf("before procLine\n");
      table = procLine(table, current, size, amount);
      free(current);
      // printf("after procLine\n");
      current = readline(file);
   }
   free(current);
   return table;
}


HashItem **procLine(HashItem **tabl, char *curline, int *size, int *amount){
                // printf("made it in procLine\n");
		char *compTok = NULL;
		char *curword = NULL;
		int code;
		HashItem **table = tabl;
		compTok = strtok(curline, " ,./;[]<>?:\"{}()|*\n");
			while (compTok != NULL){
				if (loadFactor(amount, size)){
					// printf("REHASH\n");
					printf("size1: %d\n", *size);
					table = reHashTable(table, size, amount);
					printf("size2: %d\n", *size);

				}
				for (int i = 0; compTok[i] != '\0'; ++i){
					if (isdigit(compTok[i])){
						compTok = strtok(NULL, " ,./;[]<>?:\"{}|()*\n");
						break;
					}
					compTok[i] = tolower(compTok[i]);
					if (compTok[i+1] == '\0'){
						// printf("hi\n");
						if(NULL==(curword=(char*)malloc((i+1) * sizeof(char)))) { 
							perror(__FUNCTION__);
							exit(-1);
						}
						// printf("curword: %s\n", curword);
						// printf("compTok: %s\n", compTok);
						strcpy(curword, compTok);
						// printf("herro: 1\n");
						curword[i+1] = '\0';
						// printf("herro: 2\n");
						// printf("compTok: %s\n", compTok);
						// printf("curword: %s\n", curword);
						code = hashCode(curword, size);
						// printf("%d\n", code);
						// printf("herro: 3\n");
						// printf("table[index]: %s\n", table[code]->word);
						if ((table[code]) != NULL){
							// printf("herro: 4\n");
							cyclingHashTable(table, code, curword, size, amount, 0);
							compTok = strtok(NULL, " ,./;[]<>?:\"{}|()*\n");
							break;
						}
						// printf("herro: 5\n");
						createItem(table, code, curword);
						// printf("herro: 6\n");
						*amount += 1;
						compTok = strtok(NULL, " ,./;'[]<>?:\"{}|()*\n");
						// printf("%s\n", compTok);
						free(curword);
						break;
					}
				}
			}
	return table;		
}

HashItem **reHashTable(HashItem **table, int *size, int *amount){
	int oldSize = *size;
	int newcode;
	int index;
	*size *= 2;
	HashItem **tempTable = table;
	HashItem **hashTable = NULL;

	if( NULL==(hashTable=(HashItem**)calloc(*size, sizeof(HashItem*))) ) { 
		perror(__FUNCTION__);
		exit(-1);
		}

	for (int o = 0; o < oldSize; ++o){
		if (tempTable[o] != NULL){
			newcode = hashCode(tempTable[o]->word, size);
			// printf("%d\n", newcode);
			if (hashTable[newcode] != NULL){
				index = cyclingHashTable(hashTable, newcode, tempTable[o]->word, size, amount, 1);	
				hashTable[index]->occur = tempTable[o]->occur;
				free(tempTable[o]);

			} else{
				createItem(hashTable, newcode, tempTable[o]->word);
				hashTable[newcode]->occur = tempTable[o]->occur;
				free(tempTable[o]);

			}
		}
	}
	free(tempTable);
	return hashTable;
}																						

int cyclingHashTable(HashItem **table, int ind, char *word, int *size, int *amount,int mode){
	int index = ind;
	for (int j = 0; table[index] != NULL; ++j){
		// printf("herro: 7\n");
		index = quadProbing(index, j, size);
		// printf("index: %d, size: %d\n", index, *size);
		if (!mode){
			// printf("herro: 8\n");
			if (table[index] == NULL){
				// printf("herro: 9\n");
				createItem(table, index, word);
				// printf("herro: 10\n");
				*amount += 1;
				break;
			
			} else if ( !(strcmp( (table[index])->word, word) )){
				// printf("herro: 11\n");
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

HashItem **FreeTable(HashItem **tabl, int *size){
	HashItem **table = tabl;
	for (int t = 0; t<*size; ++t){
		if (table[t]!=NULL){
			//free(table[t]->word);
			free(table[t]);
		}
	}
	return table;
}
void createItem(HashItem **table, int index, char *word){
	table[index] = malloc(sizeof(HashItem));
	(table[index])->word = word;
	(table[index])->occur = 1;
	return;
}

int quadProbing(int index, int inc, int *size){
	int newindex;
	newindex = (index + (inc * inc)) % *size;
	return newindex; 
}

int hashCode(char *value, int *size){
	int asval = 0;
	for (int l = 0; *(value + l) != '\0'; ++l, asval += (int)(*(value + l)));

	return asval % *size;
}

int loadFactor(int *amount, int *size){
	float refactorVal = .85;
	if (((float)*amount / *size) > refactorVal){
		return 1;
	}
	return 0;
}
