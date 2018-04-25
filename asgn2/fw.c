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


	if (NULL == (file = fopen(argv[1], "r"))){
		perror(__FUNCTION__);
		exit(-1);
	}

   hashTable = procFile(hashTable, file, size, amount);
   hashTable = filterTable(hashTable, size, amount);
   qsort((void *)hashTable, *amount, sizeof(HashItem *), compFunction);

   printf("done\n");
	for (int k=0; k<*amount; ++k){
		//printf("maybe\n");

		//if ((hashTable[k]) != NULL){
			if (hashTable[k]->occur>5)
			{
			printf("hashTable[%d]: ", k);
			printf("%s\n", hashTable[k]->word);
			printf("occur: %d\n", hashTable[k]->occur);			}
		}
	//}
	hashTable = FreeTable(hashTable, amount);		// changed size to amount after filtering
	free(hashTable);
	fclose(file);
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
		// char *curword = NULL;
		int code;
		int asval;
		HashItem **table = tabl;
		compTok = strtok(curline, " -',./;[]<>?:\"{}()|*\n\13");
			while (compTok != NULL){
				if (loadFactor(amount, size)){
					// printf("REHASH\n");
					printf("size1: %d\n", *size);
					table = reHashTable(table, size, amount);
					printf("size2: %d\n", *size);

				}
				for (int i = 0; compTok[i] != '\0'; ++i){
					if (isdigit(compTok[i])){
						compTok = strtok(NULL, " -',./;[]<>?:\"{}|()*\n\13");
						break;
					}
					compTok[i] = tolower(compTok[i]);
					if (compTok[i+1] == '\0'){
						
						asval = asciiAdd(compTok);
						code = hashCode(asval, size);
						
						if ((table[code]) != NULL){
							// printf("herro: 4\n");
							cyclingHashTable(table, code, compTok, asval, size, amount, i+2, 0);
							compTok = strtok(NULL, " -',./;[]<>?:\"{}|()*\n\13");
							break;
						}
						// printf("herro: 5\n");
						createItem(table, code, compTok, asval, i+2);
						// printf("herro: 6\n");
						*amount += 1;
						compTok = strtok(NULL, " -',./;[]<>?:\"{}|()*\n\13");
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
			newcode = hashCode(tempTable[o]->ascival, size);
			// printf("%d\n", newcode);
			if (hashTable[newcode] != NULL){
				index = cyclingHashTable(hashTable, newcode, tempTable[o]->word, tempTable[o]->ascival, size, amount, 0, 1);	
				hashTable[index]=tempTable[o];
				hashTable[index]->occur = tempTable[o]->occur;

			} else{
				hashTable[newcode] = tempTable[o];
				hashTable[newcode]->occur = tempTable[o]->occur;

			}
		}
	}
	free(tempTable);
	return hashTable;
}																						

int cyclingHashTable(HashItem **table, int ind, char *paraword, int asval, int *size, int *amount, int len, int mode){
	int index = ind;
	for (int j = 0; table[index] != NULL; ++j){
		// printf("herro: 7\n");
		index = quadProbing(index, j, size);
		// printf("index: %d, size: %d\n", index, *size);
		if (!mode){
			// printf("herro: 8\n");
			if (table[index] == NULL){
				// printf("herro: 9\n");
				createItem(table, index, paraword, asval, len);
				// printf("herro: 10\n");
				*amount += 1;
				break;
			
			} else if ( !(strcmp( (table[index])->word, paraword) )){
				// printf("herro: 11\n");
				(table[index])->occur += 1;
				break;
			}
		}
		if (mode){
			if (table[index] == NULL){
				//createItem(table, index, paraword, mode);
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
			free(table[t]->word);
			free(table[t]);
		}
	}
	return table;
}
void createItem(HashItem **table, int index, char *word, int asval, int len){
		table[index] = malloc(sizeof(HashItem));
		(table[index])->word = malloc(len * sizeof(char));
		strcpy((table[index])->word, word);
		table[index]->ascival = asval;
		(table[index])->occur = 1;

	return;
}

int quadProbing(int index, int inc, int *size){
	int newindex;
	newindex = (index + (inc * inc)) % *size;
	return newindex; 
}

int hashCode(int asval, int *size){
	return asval % *size;
}

int asciiAdd(char *value){
	int asval = 0;
	for (int l = 0; *(value + l) != '\0'; ++l, asval += (int)(*(value + l)));

	return asval;
}

int loadFactor(int *amount, int *size){
	float refactorVal = .85;
	if (((float)*amount / *size) > refactorVal){
		return 1;
	}
	return 0;
}

HashItem **filterTable(HashItem **temptable, int *size, int *amount){
	HashItem **hashTable = NULL;
	if( NULL==(hashTable=(HashItem**)calloc(*amount, sizeof(HashItem*))) ) { 
		perror(__FUNCTION__);
		exit(-1);
	}
	for (int i = 0, j = 0; i < *size; ++i){
		if (temptable[i] == NULL){
			continue;
		} else {
			hashTable[j] = temptable[i];
			++j;
		}
	}
	free(temptable);
	return hashTable;
}

int compFunction(const void *a, const void *b){
	//(HashItem *) a = (has)

	int result;
	if (a == NULL && b == NULL){
		return 0;
	} else if (a != NULL && b == NULL){
		return -1;
	}else if (a == NULL && b != NULL){
		return 1;
	}

	HashItem *A = (*(HashItem **)a);
	HashItem *B = (*(HashItem **)b);
	// int aAsval = ((HashItem *)a)->ascival;
	// int bAsval = ((HashItem *)b)->ascival;
	//int aAlpha = (int)(((HashItem *)a)->word[0]);
	//int bAlpha = (int)(((HashItem *)b)->word[0]);
	if (B->occur == A->occur){
		result = strcmp( B->word, A->word );
	// 	// if (aAsval == bAsval){
	// 	// 	result = (aAlpha - bAlpha);
	// 	// }else{result = (aAsval - bAsval);}
		
	} else{result = (B->occur - A->occur);}

	return result;
	// if (result>0){
	// 	return 1;
	// }else if (result<0){
	// 	return -1;
	// } else{
	// 	return 0;
	// }
	//printf("%d\n", ((HashItem *)a)->occur);
}
