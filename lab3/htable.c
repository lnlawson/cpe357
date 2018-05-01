#include <stdio.h>
#include <stdlib.h>
#include "htable.h"


int main(int argc, char **argv){
	FILE *file = NULL;
	int countVal = 0;
	int *count = &countVal;

	treeNode **treeList = NULL;
	initTable();
	if (NULL == (file = fopen(argv[1], "r"))){
		perror(argv[1]);
	}
	else{
		fillTable(file);
		treeList = buildList(treeList, count);
		qsort(treeList, *count, sizeof(treeNode*), compFunction1);
		for (int i = 0; i < *count; i++){
		printf("table[%d] : occur %d character %c\n", i, treeList[i]->val, treeList[i]->character);
		}
		treeList = buildTree(treeList, count);
	}

	for (int i = 0; i < 1; i++){
		printf("table[%d] : occur %d character %c left %c right %c\n", i, treeList[i]->val, treeList[i]->character, 
			treeList[i]->left->character, treeList[i]->right->character);	
	}

	fclose(file);
	//FreeTable(table, 127);
}

//Function for initializing the whole table to 0s
void initTable(void){
	for (int i = 0; i < 256; i++){
		table[i] = 0;
	}
}


void fillTable(FILE *file){
   int temp = getc(file);
	while (temp != EOF){
		if (temp < 0 || temp > 255){
			temp = getc(file);
			continue;
		}
		table[temp] += 1;
		temp = getc(file);
	}
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
	if( NULL==(treeList=realloc(treeList, *count * sizeof(treeNode*))) ) { 
	   perror(__FUNCTION__);
	   exit(-1);
	}
	return treeList;
}

treeNode **buildTree(treeNode **list, int *count){
	treeNode **treeList = list;
	int tempCount = *count;
	printf("%d\n", tempCount);
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
		for (int i = 0; i < tempCount; i++){
		printf("table[%d] : occur %d character %c\n", i, treeList[i]->val, treeList[i]->character);
		}
		printf("\n");

		// printf("%d\n", tempCount);
	}
	 treeList = realloc(treeList, tempCount * sizeof(treeNode*));
	return treeList;
}

// char *encodeTable(treeNode **list, int *count){  ///////////////////////////
// 	char *codeTable = NULL;
// 	if( NULL==(codeTable=malloc(sizeof(char))) ) { 
// 	   	perror(__FUNCTION__);
// 	   	exit(-1);
// 		}
// }



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

//////////////////////////////////LINKED LIST/////////////////////////////////



/*Item *createItem(int val, int occur){
	Item *new_i = malloc(sizeof(Item*));
	(new_i)->val = val;
	(new_i)->occur = occur;
	return new_i;
}*/






/////////////////////////////////FROM STATIC TABLE IMPLEMENTATION

/*int main(int argc, char **argv){
	FILE *file = NULL;
	List *list = NULL;
	initTable();
	if (NULL == (file = fopen(argv[1], "r"))){
		perror(argv[1]);
	}
	else{
		fillTable(file);
	}

	for (int i = 0; i < 127; i++){
		printf("table[%d] : %d\n", i, table[i]);
	}

	list = buildLList(list);

	Node *temp = list->head;
	Item *tempi = NULL;
	while (temp->next != NULL){
		tempi = (Item*)temp->item;
		printf("val: %d, occur: %d\n", tempi->val, tempi->occur);
		temp = temp->next;
	}

	fclose(file);
	//FreeTable(table, 127);
}*/






/*List *buildLList(List *list){
	for (int i = 0; i < 127; i++){
		if(table[i] != 0){
		     list = insertNode(list, createItem(i, table[i]));
		}
	}
        return list;
}*/



/*List *insertNode(List *list, Item *item){
	Node *curr = NULL;
	Node *new_n = malloc(sizeof(Node*));
        new_n->item = item;
	new_n->next = NULL;
	if (list == NULL){
		list->head = new_n;
	}
	else{
		curr = list->head;
		while (curr->next != NULL){
			if(((curr->next)->item)->occur > item->occur){
				new_n->next = curr->next;
				curr->next = new_n;
			}
			curr = curr->next;
		}
	}
	return list;
}*/




/*int Comparator(const void *p, const void *q){
	return (int)(*p) - (int)(*q);
}*/




/*int Comparator(const void *a, const void *b){
	int result;

	if (a == NULL && b == NULL){
		return 0;
	} else if (a != NULL && b == NULL){
		return -1;
	} else if (a == NULL && b != NULL){
		return 1;
	}

	TableItem *A = (*(TableItem **)a);
	TableItem *B = (*(TableItem **)b);
        //printf("A: %d\n",A->occur);
        //printf("B: %d\n",B->occur);
	if (B->occur == A->occur){
		result = B->val - -A->val ;
	} 

	else{result = (B->occur - A->occur);}

	return result;
}




//Function for filling the table with letter occurences
void fillTable(FILE *file, TableItem **table){
	table = (TableItem**)(calloc(127, sizeof(TableItem*)));
	if(table == NULL){
		printf("Failed Calloc in fillTable\n");
		perror(__FUNCTION__);
		exit(-1);
	}
	temp = getc(file);
	while (temp != EOF){
		if (table[int(temp)] != NULL){
			table[(int)temp]->occur += 1;
		}
		else{
			createItem(table, int(temp));
		}
		temp = getc(file);
	}
}

void createItem(Tableitem **table, int val){
		table[val] = malloc(sizeof(TableItem));
		if (table[val] == NULL){
			printf("Failed Malloc in createItem\n");
			perror(__FUNCTION__);
			exit(-1);	
		}
		else{
			(table[val])->val = val;
			(table[val])->occur = 1;
			return;
		}
}


void FreeTable(TableItem **table, int size){
	for (int i = 0; i < size; i++){
		free(table[i]);
	}
}
*/


