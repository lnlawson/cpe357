/*Name: Logan Lawson
**Assignment 1 : mytr.c*/

#include "mytr.h"

int main(int argc, char const *argv[]){

int normal_flag = 0;
int curC;

//initialize arr for translation
for (int j = 0; j < 256; ++j){
	transarr[j] = j;
	}

	for (int i = 0; i < argc; i++)
	{
		if (argv[i] == "-d")
			normal_flag = -1;

		if ((argv[i][0] && argv[i+1][0]) == "'"){
			for (int c = 1; argv[i][c] != "'"; ++c)
			{
				int curT = (int)argv[i][c]
				int curTC;
				if (argv[i+1][c] != "'"){
					curTC = (int)argv[i+1][c];
				}

				transarr[curT] = curTC;
				printf("%c\n", transarr[curT]);
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
