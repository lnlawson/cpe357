#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "mypwd.h"

int main(int argc, char * argv[]){
	struct stat sb;
	struct dirent *ent;
	int i ;
	DIR * d;
	char buf[4096];
	char result[4096], temp[100];
	int done;
	ino_t iNode;
	result[0] = '\0';
	done = 0; 
	while(done != 1){

		i = stat(".", &sb);
		if( i != 0){
			perror("Wrong\n");
			exit(EXIT_FAILURE);
		}
		
		iNode = sb.st_ino;
		chdir("..");
		d = opendir(".");
		stat(".", &sb);
		/* tests if the child's i node is the same as the current, meaning you're in same dir */
		if(sb.st_ino == iNode){
			done = 1;
			closedir(d);
			buf[0] = '/';
			buf[1] = '\0';
			strncat(buf, result, PATH_MAX);
			strcpy(result, buf);
			break;
		}
		while((ent = readdir(d)) != NULL){
			stat(ent->d_name, &sb);
			if(sb.st_ino == iNode){
				/* Basically appends the previous directory's name to fron tof the current string */
				buf[0] = '/';
				buf[1] = '\0';
				strcpy(temp, ent->d_name);
				temp[strlen(ent->d_name)] = '\0';
				strncat(buf, temp, strlen(temp));
				strncat(buf, result, PATH_MAX);
				strcpy(result, buf);
				break;
			}
		}
		closedir(d);
	}
	printf("%s\n", result);
	return 0;
}

/*
stat on dot, get its i node from struct stat
	chdir .. then opendir ., find folder whose i node is same as 
	stop if name of directory
*/
