#ifndef UNIQ_H
#define UNIQ_H

char *read_long_line(FILE *file);

typedef struct adj_lines{
	char *line1;
	char *line2;
} Adj_Lines;

#endif