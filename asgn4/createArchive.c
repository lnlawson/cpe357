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
#include "createArchive.h"


FILE *Archive = NULL;
//char *mode = NULL;
int c_flag = 0;

int main(int argc, char *argv[]){
   //procDir(argv[1]);
   
   int len_arcname = strlen(argv[2]);
   char *archi = malloc(len_arcname*sizeof(char));
   for (int j = 0; argv[1][j] != '\0'; j++){
      //mode[j] = argv[1][j];
      if (argv[1][j] == 'c'){
         c_flag = 1;
      }
   }

   for (int i = 0; argv[2][i] != '\0'; i++){
      archi[i] = argv[2][i];
   }


   //if trying to add to the archive

   if (c_flag == 1){
      Archive = fopen(archi, "w+");
   }
   else{
      Archive = fopen(archi, "a");
   }


   procDir(argv[3]);
   return 0;

}









void procFile(FILE *file, FILE *arc){
   int buffer;
   size_t success = fread(&buffer, 4, 1, file);
   while (success == 1){
      fputc(buffer, arc);
      success = fread(&buffer, 1, 1, file);
   }
}


int buildHeader(const struct stat *input_s, const char *name, FILE *arc){
  //if we recieved the stat of a directory then we'll return NULL 
   if (S_ISDIR(input_s->st_mode)){
      return 1;
   } 

   //finding difference between prefix and name
   int len_name = strlen(name);
   char *shortname = calloc(100, sizeof(char));
   char *prefix = calloc(155, sizeof(char));
   int i;

   printf("pre-name : %s len : %d\n", name, len_name);
   for (i = (len_name - 1); name[i] != '/' ; i--){
      if (i == 0){
         break;
      }
   }
   //printf("i : %d\n", i);
   if (i != 0){
      i++;
   }
   strcpy(shortname, (name + i));
   //printf("name : %s\n", name);
   printf("name in header : %s\n", shortname);
   if (i == 0){
      //prefix = realloc(prefix, 1*sizeof(char));
      prefix[0] = '\0';
   }
   else{
      int k;
      for (k = 0; k < i; k++){
         prefix[k] = name[k];//still working on building the prefix here 
      }
   }
   printf("prefix in header : %s\n", prefix);




   //writing stuff into header

   fwrite(shortname, sizeof(char), 100, arc);
   char *mode = calloc(8, sizeof(char));
   //strmode(input_s->st_mode, mode);
   fwrite(mode, sizeof(char), 8,arc);


   

   

   return 0;


}

int bigProc(const char *name, const struct stat *input_s, int type){
   printf("name in bigProc : %s\n", name);
   //printf("size : %zu\n", input_s->st_size);
   //name = full path for every directory and every file in every subdirectory given in the cmd line argument
   FILE *file = NULL;
   FILE *arc = NULL;

   arc = Archive;//making the global file pointer local

   if (NULL == (file = fopen(name, "r"))){
      perror(name);
      exit(-1);
   }
   int option = 0;
   option = buildHeader(input_s, name, arc);//make sure you archive this header as your building it so it happens before the next line
   if (option == 1){
      procFile(file, arc); //this archives the data directly from the procfile function.
   }
  
   
   return 0;
}




void procDir(const char *name){
   ftw(name, bigProc, FTW_D);

}


//////////////////////////////////////////////////////////////////////////



void read_header(FILE *infile){
/// Change calloc to malloc with a null assignment after read.

   // Reading NAME
   const char *NAME = calloc(100, sizeof(char));
   fread(NAME, 1, 100, infile);
   fopen(NAME, "w"); // Create file with read name

   // Reading MODE
   char *MODE = calloc(9, sizeof(char));
   fread(MODE, 1, 8, infile);

   // Reading UID
   char *UID = calloc(9, sizeof(char));
   fread(UID, 1, 8, infile);

   // Reading GID
   char *GID = calloc(9, sizeof(char));
   fread(GID, 1, 8, infile);

   // Reading SIZE
   char *SIZE = calloc(13, sizeof(char));
   fread(SIZE, 1, 12, infile);

   // Reading mtime
   char *MTIME = calloc(13, sizeof(char));
   fread(MTIME, 1, 12, infile);   

   // Reading CHKSUM
   char *CHKSUM = calloc(9, sizeof(char));
   fread(CHKSUM, 1, 8, infile);

   //Reading TYPEFLAG
   char *TYPEFLAG = calloc(2, sizeof(char));
   fread(TYPEFLAG, 1, 1, infile);

   // Reading LINKNAME
   //char *LINKNAME

   // Reading MAGIC
   char *MAGIC = calloc(6, sizeof(char));
   fread(MAGIC, 1, 6, infile);

   // Reading Version
   char *VERSION = calloc(3, sizeof(char));
   fread(VERSION, 1, 2, infile);

   // Reading UNAME
   char *UNAME = calloc(33, sizeof(char));
   fread(UNAME, 1, 32, infile);

   // Reading GNAME
   char *GNAME = calloc(33, sizeof(char));
   fread(GNAME, 1, 32, infile);

   // Reading DEVMAJOR
   char *DEVMAJOR = calloc(9, sizeof(char));
   fread(DEVMAJOR, 1, 8, infile);

   // Reading DEVMINOR
   char *DEVMINOR = calloc(9, sizeof(char));
   fread(DEVMINOR, 1, 8, infile);

   // Reading PREFIX
   char *PREFIX = calloc(156, sizeof(char));
   fread(1, 155, infile);


}