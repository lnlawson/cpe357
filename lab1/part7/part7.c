/*Name: Logan Lawson
 *Lab 1 : Part 3*/

#include <stdio.h>

int main(int argc, char const *argv[])
{
	for(int i=0; i<argc; i++){
		if (argv[i][0] == '-')
		printf("%s\n", argv[i]);
	}

	return 0;
}