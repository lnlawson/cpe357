/*Name: Logan Lawson
**Assignment 2 : fw.c*/

#include "fw.h"
#include "readline.h"



int main(int argc, char const *argv[])
{
	// FILE *file;
	HashItem **hashTable = NULL;
	int tableSize = 101;
	int tableAmount = 0;
	int nAmount = 10;
	int *size = &tableSize;
	int *amount = &tableAmount;
	int *n = &nAmount;


	// if (NULL == (file = fopen(argv[1], "r"))){
	// 	perror(__FUNCTION__);
	// 	exit(-1);
	// }

   hashTable = procInput(hashTable, argc, argv, size, amount, n);
   hashTable = filterTable(hashTable, size, amount);
   qsort((void *)hashTable, *amount, sizeof(HashItem *), compFunction);

   printOutput(hashTable, amount, *n);
   // printf("done\n");
	// for (int k=0; k<*amount; ++k){
	// 		if (hashTable[k]->occur>50){
	// 		printf("hashTable[%d]: ", k);
	// 		printf("%s\n", hashTable[k]->word);
	// 		printf("occur: %d\n", hashTable[k]->occur);
	// 		}
	// }
	hashTable = FreeTable(hashTable, amount);		// changed size to amount after filtering
	free(hashTable);
	// fclose(file);
	// printf("ALL DONE!!!!!!!\n");
	return 0;
}

HashItem **procInput(HashItem **table, int agc, char const *agv[], int *size, int *amount, int *n){
   FILE *file;

   if(agc == 3 && (strcmp(agv[1], "-n") == 0)){
      table = procFile(table, stdin, size, amount);
   }
   for (int i = 1; i < agc; i++){

      if (strcmp(agv[i],"-n") == 0){
         i++;
         sscanf(agv[i], "%d", n);

      } else if ((agv[i][0] == '-') && (agv[i][1] != 'n')){
         fprintf(stderr,"\nfw: extra operand %s\n", &agv[i][1]);

      } else{
         if (NULL == (file = fopen(agv[i], "r"))){
            perror(__FUNCTION__);
            exit(-1);
         }
         table = procFile(table, file, size, amount);
      }
   }
   fclose(file);
	return table;
}

HashItem **procFile(HashItem **table, FILE *file, int *size, int *amount){
   char *current = readline(file);
   table = (HashItem**)calloc(*size, sizeof(HashItem*)); 
	if(table == NULL){
	   // printf("problem with mallocing table\n");
	   perror(__FUNCTION__);
	   exit(-1);
	}
   while (current != NULL){
   	// printf("start\n");
      table = procLine(table, current, size, amount);
      free(current);
      current = readline(file);
   }
   free(current);
   return table;
}


HashItem **procLine(HashItem **tabl, char *curline, int *size, int *amount){
		char *compTok = NULL;
		int code;
		int asval;
		HashItem **table = tabl;
		compTok = procWord(curline);
		// printf("%s\n", compTok);
			while (compTok != NULL){

				if (loadFactor(amount, size)){
					// printf("size1: %d\n", *size);
					table = reHashTable(table, size, amount);
					// printf("size2: %d\n", *size);
				}
				for (int i = 0; compTok[i] != '\0'; ++i){

					compTok[i] = tolower(compTok[i]);
					if (compTok[i+1] == '\0'){
						// printf("hiiiiiiiiiiiiiiiii\n");
						asval = asciiAdd(compTok);
						code = hashCode(asval, size);
						
						if ((table[code]) != NULL){
							cyclingHashTable(table, code, compTok, asval, size, amount, i+2, 0);
							compTok = procWord(NULL);
							break;
						}
						createItem(table, code, compTok, asval, i+2);
						*amount += 1;
						compTok = procWord(NULL);
						break;
					}
				}
			}
	return table;		
}

void printOutput(HashItem **table, int *amount, int nflag){
	int digits;
	int spaces;
	char *occurColumn;
	int temp;
	if( NULL==(occurColumn=calloc(9, sizeof(char))) ) { 
	perror(__FUNCTION__);
	exit(-1);
	}
	if (*amount < *nflag){
		temp = *amount;
	} else {temp = *nflag;}
	
	printf("The top %d words (out of %d) are:\n", nflag, *amount);
	for (int i = 0; i < temp; ++i){
		digits = 0;
		int tempOccur = table[i]->occur;
		while(tempOccur != 0)
		{
        tempOccur /= 10;
        ++digits;
    	}
    	spaces = 9 - digits;
    	for (int j = 0; j<9; ++j){
    		if (j<spaces){
    		occurColumn[j] = ' ';
    	} else if (j>= spaces){
    		occurColumn[j] = '\0';
    	}
   }
   printf("%s%d %s\n", occurColumn, table[i]->occur, table[i]->word);
   }
free(occurColumn);
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
		index = quadProbing(index, j, size);
		if (!mode){
			if (table[index] == NULL){
				createItem(table, index, paraword, asval, len);
				*amount += 1;
				break;
			
			} else if ( !(strcmp( (table[index])->word, paraword) )){
				(table[index])->occur += 1;
				break;
			}
		}
		if (mode){
			if (table[index] == NULL){
				break;
			}
		}
	}
	return index;
}

char *procWord(char *line){

	static char *curSpot;
	static int nullFlag;

	if (line != NULL){
		curSpot = line;
		nullFlag = 0;
	}
	if (nullFlag){			/////////////////
		return NULL;
	} else if (curSpot[0] == '\0'){
		return NULL;
	} ///////////////////////////

	int i = 0;
	while (isalpha(curSpot[i])){
		i++;
		if (curSpot[i] == '\0'){
			nullFlag = 1;
		}
	}
	if (!i){
		while (!isalpha(curSpot[i])){
			if (curSpot[i] == '\0'){
				nullFlag = 1;
				break;
			}
			++i;
		}
		curSpot = curSpot + i;
		return procWord(NULL);
	}
	curSpot[i] = '\0';
	++i;
	curSpot = curSpot + i;
	return curSpot - i;
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
	int result;

	if (a == NULL && b == NULL){
		return 0;
	} else if (a != NULL && b == NULL){
		return -1;
	} else if (a == NULL && b != NULL){
		return 1;
	}

	HashItem *A = (*(HashItem **)a);
	HashItem *B = (*(HashItem **)b);

	if (B->occur == A->occur){
		result = strcmp( B->word, A->word );
	} else{result = (B->occur - A->occur);}

	return result;
}
