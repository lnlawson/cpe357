#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IFREG 0100000
#define IFDIR 0040000
#define IFCHR 0020000
#define IFBLK 0060000
#define IFIFO 0010000
#define IFLNK 0120000

char *getType(mode_t mode) {
   if(mode & IFREG)
      return "Regular File";
   if(mode & IFDIR)
      return "Directory";
   if(mode & IFCHR)
      return "Character Device";
   if(mode & IFBLK)
      return "Block Device";
   if(mode & IFIFO)
      return "FIFO";
   if(mode & IFLNK)
      return "Symbolic Link";
   return "NA";
}

char *getAccess(mode_t mode, char *access) {
   if(mode & IFREG)
      access[0] = '-';
   if(mode & IFDIR)
      access[0] = 'd';
   if(mode & IFCHR)
      access[0] = 'c';
   if(mode & IFBLK)
      access[0] = 'b';
   if(mode & IFIFO)
      access[0] = 'p';
   if(mode & IFLNK)
      access[0] = 'l';

   if(!(mode & 00400))
      access[1] = '-';
   if(!(mode & 00200))
      access[2] = '-';

   if(mode & 0004000) {
      if(mode & 00100) {
         access[3] = 's';
      }
      else {
         access[3] = 'S';
      }
   }
   else {
      if(!(mode & 00100))
         access[3] = '-';
   }

   if(!(mode & 00040))
      access[4] = '-';
   if(!(mode & 00020))
      access[5] = '-';

   if(mode & 0002000) {
      if(mode & 00010) {
         access[6] = 's';
      }
      else {
         access[6] = 'S';
      }
   }
   else {
      if(!(mode & 00010))
         access[6] = '-';
   }
   if(!(mode & 00004))
      access[7] = '-';
   if(!(mode & 00002))
      access[8] = '-';
   if(!(mode & 00001))
      access[9] = '-';
   return access;
}

void printStats(char *fname) {
   struct stat *stats  = malloc(sizeof(struct stat));
   char *access = malloc(sizeof(char) * 10);
   strncpy(access, "-rwxrwxrwx", 10);
   stat(fname, stats);
   printf("File: '%s'\n", fname);
   printf("Type: %s\n", getType(stats->st_mode));
   printf("Size: %d\n", (int) (stats->st_size));
   printf("Inode: %d\n", (int) (stats->st_ino));
   printf("Links: %d\n", (int) (stats->st_nlink));
   printf("Access: %s\n", getAccess(stats->st_mode, access));
   printf("\n");
   free(stats);
}

int main(int argc, char **argv) {
   int i;
   for(i = 1; i < argc; i++) {
      printStats(argv[i]);
   }
   return 0;
}
