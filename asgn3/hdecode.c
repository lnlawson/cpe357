/*Name: Logan Lawson
**Assignment 3 : hdecode*/

#include "hdecode.h"

int main(int argc, char **argv){
	int infile = -1;
	int outfile = -1;
	int countVal = 0;
	int *count = &countVal;
	int totalBits = 0;

	treeNode **treeList = NULL;
	PathCode **codeTable = NULL;

	if (argc != 3 ){
		if (argc > 3){
			perror("usage");
			exit(-1);
		
		} else if (argc < 3){
			if (argc == 2){
				if (argv[1][1] == '-'){
					infile = 0;
					outfile = 1;
				} else {
					outfile = 0;
					if (-1 == (infile = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR))){
						perror(argv[2]);
					}
				}
			} else {
				// printf("hi\n");
				infile = 0;
				outfile = 1;
			} 
		} 
	} else {
		if (argv[1][1] == '-'){
			infile = 0;
			if (-1 == (outfile = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR))){
			perror(argv[2]);
			}
		} else{
			if (-1 == (outfile = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR))){
				perror(argv[2]);
			}
			if (-1 == (infile = open(argv[1], O_RDONLY))){
				perror(argv[1]);
			}
		}
	}
	// printf("hi\n");
	initTable();
	*count = readHeader(infile, count);
	if (*count == 1){
		char oneChar;
		int oneCharFreq;
		for (int i = 0; i < 256; ++i){
			if (table[i] > 0){
				oneChar = i;
				oneCharFreq = table[i];
				break;
			}
		}
		for (int j = 0; j < oneCharFreq; ++j){
			if (0 == (write(outfile, &oneChar, 1))){
				perror(__FUNCTION__);
			}
		}
		close(infile);
		close(outfile);
		return 0;
	}
	// for (int i = 0; i < 256; i++){
	// 	if (table[i] > 0){
	// 		printf("table[%d] : occur %d character %c\n", i, table[i], i);
	// 	}
	// }
	// printf("%d\n", *count);
	treeList = buildList(treeList);
	qsort(treeList, *count, sizeof(treeNode*), compFunction1);
	treeList = buildTree(treeList, count);
	codeTable = encodeTable(treeList[0], &totalBits);
	decode(infile, outfile, treeList[0], &totalBits);
	freeTree(treeList[0]);
	free(treeList);
	freeTable(codeTable);

	close(infile);
	close(outfile);

	return 0;
}

void initTable(void){
	for (int i = 0; i < 256; i++){
		table[i] = 0;
	}
}

int readHeader(int infile){
	uint32_t countVal = 0;
	uint32_t *occur = &countVal;
	uint8_t *character = NULL;
	uint32_t *freq = NULL;

	if( NULL==(occur=malloc(sizeof(uint32_t))) ) { 
	   	perror(__FUNCTION__);
	   	exit(-1);
	}	
	if( NULL==(character=malloc(sizeof(uint8_t))) ) { 
	   	perror(__FUNCTION__);
	   	exit(-1);
	}
	if( NULL==(freq=malloc(sizeof(uint32_t))) ) { 
   	perror(__FUNCTION__);
   	exit(-1);
	}	

	if (-1 == read(infile, occur, 4) ){
		perror(__FUNCTION__);
	}
	countVal = *occur;
	// printf("%d\n", *count);

	for (int i = 0; i < *count; ++i){

		if (-1 == read(infile, character, 1) ){
			perror(__FUNCTION__);
		}

		if (-1 == read(infile, freq, 4) ){
			perror(__FUNCTION__);
		}

		table[*character] = *freq;
	}
	free(character);
	free(freq);
	free(occur);

	return (int)*countVal;
}

void decode(int infile, int outfile, treeNode *tree, int *totalbits){
	uint8_t *readBitsBuff = NULL;
	int readBytesCount = 0;
	int bitCount = 0;
	char *codeBuff = NULL;
	char *decodedChars = NULL;
	int decodedCharsCount = 0;
	int *decodeCount = &decodedCharsCount;
	treeNode *curNode = tree;
	char *byteCode = NULL;
	int total = 0;
	int totalBits;

	totalBits = *totalbits;


	if( NULL==(byteCode=malloc(8 * sizeof(char))) ) { 
		perror(__FUNCTION__);
		exit(-1);
	}

   if( NULL==(readBitsBuff=malloc(1000 * sizeof(uint8_t))) ) { 
	   	perror(__FUNCTION__);
	   	exit(-1);
	}	
	if( NULL==(codeBuff=malloc(1000 * sizeof(char))) ) { 
   		perror(__FUNCTION__);
   		exit(-1);
	}	
	if( NULL==(decodedChars=malloc(1000 * sizeof(char))) ) { 
   		perror(__FUNCTION__);
   		exit(-1);
	}	
	readBytesCount = read(infile, readBitsBuff, 1000);

	while ( (readBytesCount)  > 0){
		for (int i = 0, j = 0; i < readBytesCount; ++i, ++j){

			binIntToCode(readBitsBuff[i], byteCode);

			if ((bitCount + 8) > 1000 || ((total + bitCount + 8) / 8) == readBytesCount){

				if (((total + bitCount + 8) / 8) == readBytesCount){
					strncpy((codeBuff + bitCount), byteCode, 8);
					bitCount += 8;
				}

				for (int k = 0; k < bitCount; ++k){
					if (decodedCharsCount == 1000){
						if (0 == (write(outfile, decodedChars, 1000))){
						perror(__FUNCTION__);
						}
						decodedCharsCount = 0;
					}
		
					if (codeBuff[k] == '0'){
						curNode = curNode->left;

					} else if (codeBuff[k] == '1'){
						curNode = curNode->right;
					}

					if (curNode->left == NULL && curNode->right == NULL){
						decodedChars[decodedCharsCount] = curNode->character;
						decodedCharsCount++;
						curNode = tree;
					}

					if ((total + k + 1) == totalBits){

						if (0 == (write(outfile, decodedChars, decodedCharsCount))){
						perror(__FUNCTION__);
						}
						free(decodedChars);
						free(readBitsBuff);
						free(codeBuff);
						free(byteCode);
						return;
					}
				}
				total += bitCount;
				bitCount = 0;
			}
			strncpy((codeBuff + bitCount), byteCode, 8);
			bitCount += 8;

		}
		readBytesCount = read(infile, readBitsBuff, 1000);
	}

	if (*decodeCount > 0){

		if (0 == (write(outfile, decodedChars, *decodeCount))){
			perror(__FUNCTION__);
			}
	}

	free(decodedChars);
	free(readBitsBuff);
	free(codeBuff);
	free(byteCode);
}


// int cyclingBuffs(int bitCount, int *decodedCharsCount, int outfile, char *decodedChars, char *codeBuff, treeNode *curNode, 
// 		treeNode *tree, int total, int totalBits){

// 	for (int k = 0; k < bitCount; ++k){
// 		if (*decodedCharsCount == 1000){
// 			if (0 == (write(outfile, decodedChars, 1000))){
// 				perror(__FUNCTION__);
// 			}
// 			*decodedCharsCount = 0;
// 		}

// 		if (codeBuff[k] == '0'){
// 			curNode = curNode->left;

// 		} else if (codeBuff[k] == '1'){
// 			curNode = curNode->right;
// 		}

// 		if (curNode->left == NULL && curNode->right == NULL){
// 			decodedChars[*decodedCharsCount] = curNode->character;
// 			*decodedCharsCount++;
// 			curNode = tree;
// 		}

// 		if ((total + k + 1) == totalBits){

// 			if (0 == (write(outfile, decodedChars, *decodedCharsCount))){
// 				perror(__FUNCTION__);
// 			}
// 			return 1;
// 		}
// 	}
// 	return 0;
// }


void binIntToCode(uint8_t intCode, char *byteCode){

	int codeNum = intCode;
	
	for (int i = 7, j = 0; j < 8; --i, j++){
		if ((codeNum - pow(2, i)) < 0){
			byteCode[j] = '0';
		}	else {
			byteCode[j] = '1';
			codeNum -= pow(2, i);
		}
	}
}




// -------------------------------------------------------------------------

treeNode **buildList(treeNode **list){
	int count = 0;
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
			treeList[count] = tempNode;
			treeList[count]->character = (char)i;
			treeList[count]->val = table[i];
			treeList[count]->left = NULL;
			treeList[count]->right = NULL;
			count += 1;
			if ((count) == buffSize){
				buffSize *=2;
				if( NULL==(treeList=realloc(treeList, buffSize * sizeof(treeNode*))) ) { 
	   		perror(__FUNCTION__);
	   		exit(-1);
				}
			}
		}
	}
	if( NULL==(treeList=realloc(treeList, count * sizeof(treeNode*))) ) { 
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

PathCode  **encodeTable(treeNode *list, int *totalbits){
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
			*totalbits += (table[i] * codeTable[i]->len);
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