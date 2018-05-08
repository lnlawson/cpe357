/*Name: Logan Lawson
**Assignment 3 : hencode*/

#include "hencode.h"


int main(int argc, char **argv){
	int infile = -1;
	int outfile = -1;
	int countVal = 0;
	int *count = &countVal;

	treeNode **treeList = NULL;
	PathCode **codeTable = NULL;

	initTable();
	if (argc < 3){
		outfile = 1;

	} else if (-1 == (outfile = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR))){
		perror(argv[2]);
	}
	if (-1 == (infile = open(argv[1], O_RDONLY))){
		perror(argv[1]);
		exit(-1);

	} else{
		fillTable(infile);
		treeList = buildList(treeList, count);
		if (*count == 0){
			writeHeader(outfile, infile, count);
			close(infile);
			close(outfile);
			return 0;
		}
		qsort(treeList, *count, sizeof(treeNode*), compFunction1);
		// for (int i = 0; i < *count; i++){
		// // printf("table[%d] : occur %d character %c\n", i, treeList[i]->val, treeList[i]->character);
		// }
		treeList = buildTree(treeList, count);
		codeTable = encodeTable(treeList[0]);
		writeHeader(outfile, infile, count);
		writeBits(outfile, infile, codeTable);
		freeTree(treeList[0]);
		free(treeList);
		freeTable(codeTable);
	}

	// for (int i = 0; i < 1; i++){
	// 	printf("table[%d] : occur %d character %c left %c right %c\n", i, treeList[i]->val, treeList[i]->character, 
	// 		treeList[i]->left->character, treeList[i]->right->character);	
	// }

	// for (int i = 0; i < 256; i++){
	// 	if (codeTable[i] != NULL){
	// 		printf("table[%d] : huffVal %s character %c occur %d\n", i, codeTable[i]->path, i, table[i]);	
	// 		}
	// 	}

	close(infile);
	close(outfile);
	return 0;
	//FreeTable(table, 127);
}

//Function for initializing the whole table to 0s
void initTable(void){
	for (int i = 0; i < 256; i++){
		table[i] = 0;
	}
}

void fillTable(int infile){
   uint8_t *temp = NULL;
   int chRead;
   uint8_t c;
   if( NULL==(temp=malloc(1000 * sizeof(uint8_t))) ) { 
	   	perror(__FUNCTION__);
	   	exit(-1);
		}
	chRead = read(infile, temp, 1000);
	while ( (chRead) > 0){
		for (int i = 0; i < chRead; ++i){
			c = temp[i];
			// printf("%d\n", c);
			// if (c < 0 || c > 255){
			// continue;
			// }
			table[c] += 1;
		}
		chRead = read(infile, temp, 1000);
		// printf("%d\n", chRead);
	}
	free(temp);
}

treeNode **buildList(treeNode **list, int *count){
	// int count = 0;
	int buffSize = 40;
	treeNode **treeList = list;
	treeNode *tempNode = NULL;
	if( NULL==(treeList=realloc(treeList, buffSize * sizeof(treeNode*))) ) { 
	   perror(__FUNCTION__);
	   exit(-1);
	}
	for (int i = 0; i < 256; ++i){
		if (table[i] > 0){
			if( NULL==(tempNode=malloc(sizeof(treeNode))) ) { 
	   		perror(__FUNCTION__);
	   		exit(-1);
			}
			treeList[*count] = tempNode;
			treeList[*count]->character = (char)i;
			treeList[*count]->val = table[i];
			treeList[*count]->left = NULL;
			treeList[*count]->right = NULL;
			*count += 1;
			if ((*count) == buffSize){
				buffSize *=2;
				if( NULL==(treeList=realloc(treeList, buffSize * sizeof(treeNode*))) ) { 
	   		perror(__FUNCTION__);
	   		exit(-1);
				}
			}
		}
	}
	if (*count == 0){
		return treeList;
	}

	if( NULL==(treeList=realloc(treeList, *count * sizeof(treeNode*))) ) { 
	   perror(__FUNCTION__);
	   exit(-1);
	}
	return treeList;
}

treeNode **buildTree(treeNode **list, int *count){
	treeNode **treeList = list;
	int tempCount = *count;
	// printf("%d\n", tempCount);
	treeNode *tempNode = NULL;
	treeNode *tempA = NULL;
	treeNode *tempB = NULL;
	char topChar;
	// int sum;
	while (tempCount > 1){
		tempA = treeList[0];
		tempB = treeList[1];
		if( NULL==(tempNode=malloc(sizeof(treeNode))) ) { 
	   	perror(__FUNCTION__);
	   	exit(-1);
		}
		tempNode->val = (tempA->val + tempB->val);
		// printf("sum: %d\n", tempNode->val);
		if ((tempA->character - tempB->character) < 0){
			topChar = tempA->character;
		} else { topChar = tempB->character;}
		tempNode->character = topChar;
		tempNode->left = tempA;
		tempNode->right = tempB;
		tempCount -= 1;
		treeList[0] = tempNode;
		treeList[1] = NULL;
		qsort(treeList, *count, sizeof(treeNode*), compFunction2);
		// for (int i = 0; i < tempCount; i++){
		// printf("table[%d] : occur %d character %c\n", i, treeList[i]->val, treeList[i]->character);
		// }
		// printf("\n");

		// printf("%d\n", tempCount);
	}
	treeList = realloc(treeList, tempCount * sizeof(treeNode*));
	return treeList;
}

PathCode  **encodeTable(treeNode *list){
	PathCode **codeTable = calloc( 256, sizeof(PathCode*));
	char *tempCode = NULL;
	tempCode = malloc(256 * sizeof(char));
	for (int i = 0; i < 256; ++i){
		if (table[i] > 0){
			codeTable[i] = malloc(sizeof(PathCode));
			tempCode = getPath(list, i, tempCode, 0);
			strcpy(codeTable[i]->path, tempCode);
			codeTable[i]->len = strlen(codeTable[i]->path);
			// printf("0x%02x: %s\n", i, codeTable[i]->path);
		} 
	}
	free(tempCode);
	return codeTable;
}


char *getPath(treeNode *node, char character, char *path, int index){
	char *p;
	if (node->character == character && node->left == NULL && node->right == NULL){
		path[index] = '\0';
		return path;
	}
	if (node->left != NULL){
		path[index] = '0';
		p = getPath(node->left, character, path, index + 1);
		if (p != NULL){
			return p;
		}
	}	
	path[index] = '1';
	if (node->right != NULL) {
			return getPath(node->right, character, path, index + 1);
	}
	return NULL;
}

void writeHeader(int outfile, int infile, int *count){

	// lseek(infile, 0, SEEK_SET);
	if (0 > (lseek(infile, 0, SEEK_SET))){
		perror(__FUNCTION__);
	}

	if (0 == (write(outfile, count, 4))){
		perror(__FUNCTION__);
	}
	for (int i = 0; i < 256; ++i){
		if (table[i] > 0){
			if (0 == (write(outfile, &i, 1))){
			perror(__FUNCTION__);
			}
			if (0 == (write(outfile, (table + i), 4))){
			perror(__FUNCTION__);
			}
		}
	}
}

void writeBits(int outfile, int infile, PathCode **codeTable){
	int buffSize = 40;
	int bits = 0;
	int totalBits = 0;
	char *bitBuffer = NULL;
	int tempByte; 
	int byteCount = 0;

	char *tempCharBuf = NULL;
  	unsigned int chRead;
   uint8_t temp;

	if( NULL==(bitBuffer=realloc(bitBuffer, buffSize * sizeof(treeNode*))) ) { 
	   perror(__FUNCTION__);
	   exit(-1);
	}

   if( NULL==(tempCharBuf=malloc(1000 * sizeof(char))) ) { 
	   	perror(__FUNCTION__);
	   	exit(-1);
		}
	// read(infile, temp, 1000);
	chRead = read(infile, tempCharBuf, 1000);
	while ( (chRead) > 0){
		for (int i = 0; i < chRead; ++i){
			temp = tempCharBuf[i];
			if (temp < 0 || temp > 255){
			continue;
			}

			if (bits + codeTable[temp]->len > buffSize){
				buffSize *= 2;
				if( NULL==(bitBuffer=realloc(bitBuffer, buffSize * sizeof(treeNode*))) ) { 
				   perror(__FUNCTION__);
				   exit(-1);
				}
			}
			strncpy((bitBuffer+bits), codeTable[temp]->path, codeTable[temp]->len);
			bits += codeTable[temp]->len;
			if ((bits % 8) == 0){
				bitBuffer[bits] = '\0';
				// printf("buffer: %s\n", bitBuffer);
				// printf("bits: %d\n", bits);
				byteCount = bits / 8;
				// printf("byteCount: %d\n", byteCount);
				for (int i = 0; i < byteCount; ++i){
					tempByte = calcBinInt((bitBuffer + (i * 8)));
					// printf("tempByte: %d\n", tempByte);
					if (0 == (write(outfile, &tempByte, 1))){
						perror(__FUNCTION__);
					}
				}
				totalBits += bits;
				bits = 0;
			}
		}

		chRead = read(infile, tempCharBuf, 1000);	
	}

	if (bits % 8){
		int pad = 8 - bits;
		for (int j = 0; j < pad; ++j){
			bitBuffer[bits+j] = '0';
		}
		bitBuffer[bits + pad] = '\0';
		// printf("%s\n", bitBuffer);
		tempByte = calcBinInt(bitBuffer);
		// printf("tempByte: %d\n", tempByte);
		if (0 == (write(outfile, &tempByte, 1))){
			perror(__FUNCTION__);
		}
	}
	free(tempCharBuf);
	free(bitBuffer);

}

int calcBinInt(char *byte){
	int result = 0;
	for (int i = 7, j = 0; j < 8; --i, ++j){
		if (byte[j] == '1'){
			// printf("hi\n");
			result += pow(2, i);
		}
	}
	return result;
}


void freeTree(treeNode *node){
	if (node != NULL){
		if(node->left == NULL && node->right == NULL){
			free(node);

		} else {
			freeTree(node->left);
			freeTree(node->right);
			free(node);
		}
	}
}


void freeTable(PathCode **codeTable){
	for (int i = 0; i < 256; ++i){
		if (codeTable[i]!= NULL){
			free(codeTable[i]);
		}
	}
	free(codeTable);
}

int compFunction1(const void *a, const void *b){
	int result;

	treeNode *A = (*(treeNode **)a);
	treeNode *B = (*(treeNode **)b);

	if (A == NULL && B == NULL){
		return 0;
	} else if (A != NULL && B == NULL){
		return -1;
	} else if (A == NULL && B != NULL){
		return 1;
	}

        //printf("A: %d\n",A->occur);
        //printf("B: %d\n",B->occur);
	if (B->val == A->val){
		result = A->character - B->character;
		// result = -1;
	} else{result = (A->val - B->val);}

	return result;
}

int compFunction2(const void *a, const void *b){
	int result;

	treeNode *A = (*(treeNode **)a);
	treeNode *B = (*(treeNode **)b);

	if (A == NULL && B == NULL){
		return 0;
	} else if (A != NULL && B == NULL){
		return -1;
	} else if (A == NULL && B != NULL){
		return 1;
	}
        //printf("A: %d\n",A->occur);
        //printf("B: %d\n",B->occur);
	if (B->val == A->val){
		// result = A->character - B->character;
		result = -1;
	} else{result = (A->val - B->val);}

	return result;
}


// aaaabbbbccddiiLLk


// 	int temp = getc(infile);
// 	while (temp != EOF){
// 		if (temp < 0 || temp > 255){
// 			temp = getc(infile);
// 			continue;
// 		}
// 		if (bits + codeTable[temp]->len > buffSize){
// 			buffSize *= 2;
// 			if( NULL==(bitBuffer=realloc(bitBuffer, buffSize * sizeof(treeNode*))) ) { 
// 			   perror(__FUNCTION__);
// 			   exit(-1);
// 			}
// 		}
// 		strncpy((bitBuffer+bits), codeTable[temp]->path, codeTable[temp]->len);
// 		bits += codeTable[temp]->len;
// 		if ((bits % 8) == 0){
// 			bitBuffer[bits] = '\0';
// 			// printf("buffer: %s\n", bitBuffer);
// 			// printf("bits: %d\n", bits);
// 			byteCount = bits / 8;
// 			// printf("byteCount: %d\n", byteCount);
// 			for (int i = 0; i < byteCount; ++i){
// 				tempByte = calcBinInt((bitBuffer + (i * 8)));
// 				// printf("tempByte: %d\n", tempByte);
// 				if (0 == (write(outfile, &tempByte, 1))){
// 					perror(__FUNCTION__);
// 				}
// 			}
// 			totalBits += bits;
// 			bits = 0;
// 		}

// 		temp = getc(infile);
// 	}

// 	// printf("%d\n", bits);
// 	if (bits % 8){
// 		int pad = 8 - bits;
// 		for (int j = 0; j < pad; ++j){
// 			bitBuffer[bits+j] = '0';
// 		}
// 		bitBuffer[bits + pad] = '\0';
// 		// printf("%s\n", bitBuffer);
// 		tempByte = calcBinInt(bitBuffer);
// 		// printf("tempByte: %d\n", tempByte);
// 		if (0 == (write(outfile, &tempByte, 1))){
// 			perror(__FUNCTION__);
// 		}
// 	}
// 	free(bitBuffer);
// }
