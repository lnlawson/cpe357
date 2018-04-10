/*Name: Logan Lawson
**Assignment 1 : mytr.c*/

#include "mytr.h"

int main(int argc, char const *argv[]){

int normal_flag = 0;
int curC;
int curTC;
int len1 = strlen(argv[2]);

printf("hiiii\n");

//initialize arr for translation
for (int j = 0; j < 256; ++j){
	transarr[j] = j;
	}

	for (int i = 1; i < argc; i++)
	{
		normal_flag = (!strcmp(argv[i], "-d")) ?	-1 : 1;
		//printf("%s\n", argv[i]);
	}

		//printf("lol\n");

		if (normal_flag == 1){
			for (int c = 0; (int)argv[1][c] != 0; ++c)
			{
				int curT = (int)argv[1][c];
				if (c < len1){
					curTC = (int)argv[2][c];
				}

				//printf("%c\n", transarr[curT]);
				transarr[curT] = curTC;
				//printf("%c\n", transarr[curT]);
			}
		}

		else if (normal_flag == -1){
			for (int c = 0; (int)argv[2][c] != 0; ++c)
			{
				int curT = (int)argv[2][c];
				transarr[curT] = -1;
			}	
		}

	curC = getchar();

	while(curC != EOF){
		if (transarr[curC] == -1)
			continue;

		putchar(transarr[curC]);
		curC = getchar();
	}
	return 0;
}
