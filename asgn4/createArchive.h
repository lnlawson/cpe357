#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
#include <dirent.h>
#include <ftw.h>



void procFile(FILE *file, FILE *arc);
int buildHeader(const struct stat *input_s, const char *name, FILE *arc);
int bigProc(const char *name, const struct stat *input_s, int type);
void procDir(const char *name);


