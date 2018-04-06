/*Name: Logan Lawson
**Assignment 1 : mytr.c*/

#include "mytr.h"

int main(int argc, char const *argv[]){

int normal_flag = 0;
int curC;

printf("hiiii\n");

//initialize arr for translation
for (int j = 0; j < 256; ++j){
	transarr[j] = j;
	}

	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-d")){
			normal_flag = -1;
		}

		printf("%s\n", argv[i]);

		if ((int)argv[i][0] == 39 && (int)argv[i+1][0] == 39){

				printf("lol\n");

			for (int c = 1; (int)argv[i][c] != 39; ++c)
			{
				int curT = (int)argv[i][c];
				int curTC;
				if ((int)argv[i+1][c] != 39){
					curTC = (int)argv[i+1][c];
				}

				transarr[curT] = curTC;
				printf("%c\n", transarr[curT]);
				printf("hi\n");
			}
			normal_flag = 1;
		}
	}

/*
	curC = getchar();

	while(normal_flag && curC != EOF){

	}*/
	return 0;
}
