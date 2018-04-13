#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"uniq.h"


int main(int argc, char *argv[]) {
	char *fileName = argv[1];
	FILE *infile = fopen(fileName, "r");
	char *line = NULL;
	Adj_Lines *lines = (Adj_Lines*) malloc(sizeof(Adj_Lines));
	int i = 1;
	do {

		line = read_long_line(infile);

		if (line) {

			if (i == 1) {
				lines->line1 = malloc(sizeof(char) * strlen(line) + 1);
				lines->line1 = line;
				printf("%s", lines->line1);
			} else if (i == 2) {
				lines->line2 = malloc(sizeof(char) * strlen(line) + 1);
				lines->line2 = line;
			} else {
				lines->line1 = (char*) realloc(lines->line1, sizeof(char) * strlen(lines->line2) + 1);
				lines->line1 = lines->line2;
				lines->line2 = (char*) realloc(lines->line2, sizeof(char) * strlen(line) + 1);
				lines->line2 = line;
			} 
		}

		if (lines->line1 != NULL && lines->line2 != NULL) {
			while(strcmp(lines->line1, lines->line2) == 0) {
				line = read_long_line(infile);
				if (line) {
					lines->line2 = (char*) realloc(lines->line2, sizeof(char) * strlen(line) + 1);
					lines->line2 = line;
				} else {
					free(lines->line2);
					lines->line2 = NULL;
				}

				if (lines->line1 == NULL || lines->line2 == NULL) {
					break;
				}
			
			}
		}

		if (lines->line2 && line) {
			printf("%s", lines->line2);
		}


		i++;

	} while (line);

	free(lines->line1);
	free(lines->line2);	
	free(lines);

	fclose(infile);
	return 0;
}


char *read_long_line(FILE *file) {
	int i = 0;
	int j = 0;
	int c;
	char *line = malloc(10 * sizeof(char));

	do {


		c = fgetc(file);
		if (c == EOF) {
			return NULL;
		}
		line[j] = (char) c;
		i++;

		if (i == 10) {
			line = realloc(line, j + 10);
			if (line == NULL) {
				printf("realloc failed.");
			}
			i = 0;
		}
		j++;

	} while (c != '\n');

	return line;
}