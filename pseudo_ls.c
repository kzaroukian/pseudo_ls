}#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <errno.h>

int main(int argc, char *argv[]) 
{ 
   DIR *dirPtr; 
   struct dirent* entryPtr; 

   struct stat statBuf;

   if (stat(argv[1], &statBuf) < 0){
   	printf("no file");
	exit(1);
   }

   dirPtr = opendir (argv[1]);

   printf("name\tsize\tinode\tuser\tgroup\n");
   while ((entryPtr = readdir (dirPtr))){

      stat(entryPtr->d_name, &statBuf);
      printf ("%-20s \t %ldBytes \t %ld \t %u \t %u\n", entryPtr->d_name, statBuf.st_size, statBuf.st_ino, statBuf.st_uid, statBuf.st_gid);
   }
   closedir (dirPtr); 
   return 0; 
}

