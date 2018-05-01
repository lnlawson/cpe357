#include <stdio.h>
#include <stdlib.h>
#include "htable.h"


int main(int argc, char **argv){
	FILE *file = NULL;
	int *count = 0;
	treeNode **treeList = NULL;
	initTable();
	if (NULL == (file = fopen(argv[1], "r"))){
		perror(argv[1]);
	}
	else{
		fillTable(file);
		treeList = buildList(treeList, count);
	}

	for (int i = 0; i < *count; i++){
		printf("table[%d] : occur %d character %c\n", i, treeList[i]->val, treeList[i]->character);
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


