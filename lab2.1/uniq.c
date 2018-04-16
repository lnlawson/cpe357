#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline.h"
int main(int argc, char *argv[]){
/* read lines from stdin until there are no more lines. For each line,
* compare it to the previous line. If they are the different, print
* the previous line. If the same, discard the previous line.
*/ 
char *last, *next;
last = readline(stdin); /* read an initial line */
/* now, keep reading lines until there are no more lines */
	while ( (NULL != last) && (NULL != (next=readline(stdin) ) ) ) {
		if ( strcmp(last, next) ) { /* print the old line if different */
			fputs(last, stdout);
		}
		free(last); /* we’re done with last now */ 
		last = next;
	}

if ( last ) /* print the last line if there is one */
	fputs(last, stdout);
return 0;
}