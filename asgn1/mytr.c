/*Name: Logan Lawson
**Assignment 1 : mytr.c*/

#include "mytr.h"

int main(int argc, char const *argv[]){

int normal_flag = 0;
int curC;
int curTC;

//printf("hiiii\n");

if (argc < 3){
	if (argv[1][0] == '-' && argv[1][1] != 'd'){
		fprintf(stderr, "\ntr: invalid option -- '%s'\nTry 'tr --help' for more information.", &argv[1][1]);
		return 1;
	}
	else {
		fprintf(stderr, "\ntr: missing operand after '%s'\nTwo strings must be given when translating.\nTry 'tr --help' for more information.", argv[1]);
		return 1;
	 }
}
else if (argc == 3){
	if (argv[1][0] == '-' && argv[1][1] != 'd'){
		fprintf(stderr, "\ntr: invalid option -- '%s'\nTry 'tr --help' for more information.", &argv[1][1]);
		return 1;
	}
}
else if (argc > 3){
	fprintf(stderr, "\ntr: extra operand '%s'\nTry 'tr --help' for more information.", argv[1]);
	return 1;
}

//initialize arr for translation
for (int j = 0; j < 256; ++j){
	transarr[j] = j;
	}

	for (int i = 1; i < argc; i++)
	{
		normal_flag = (!strcmp(argv[1], "-d")) ?	-1 : 1;
		//printf("%s\n", argv[i]);
		//printf("%d\n", normal_flag);
	}

		//printf("lol\n");
		int len1 = strlen(argv[2]);

		if (normal_flag == 1){
			for (int c = 0, cc = 0; (int)argv[1][c] != 0; ++c, ++cc)
			{
				int curT = (int)argv[1][c];
				if (curT == 92){
					curT = escapeHelper((int)argv[1][++c]);
				}
				
				if (cc < len1){
					curTC = (int)argv[2][cc];
					if (curTC == 92){
						curTC = escapeHelper((int)argv[2][++cc]);
					}
				}
				
				//printf("%c\n", transarr[curT]);
				transarr[curT] = curTC;
				//printf("%c\n", transarr[curT]);
			}
		}

		else if (normal_flag == -1){
			for (int k = 0; (int)argv[2][k] != 0; ++k)
			{
				int curT = (int)argv[2][k];
				if (curT == 92){
					curT = escapeHelper((int)argv[2][++k]);
				}
				transarr[curT] = -1;
			}	
		}

	curC = getchar();

	while(curC != EOF){
		if (transarr[curC] == -1){
			curC = getchar();
			continue;
		}
		putchar(transarr[curC]);
		curC = getchar();
	}
	return 0;
}

int escapeHelper(int escChar){
	switch(escChar){
		case 'n' :
			return 10;
			break;
		case 't' :
			return 9;
			break;
		case 92 : // '\'
			return 92;
			break;
	}
	return escChar;
}