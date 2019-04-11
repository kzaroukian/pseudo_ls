#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) 
{ 
   DIR *dirPtr; 
   struct dirent* entryPtr; 

   struct stat statBuf;
   
   char* dir;
   if (argc > 2) {
       dir = argv[2];
   } else {
      dir = argv[1];
   }	   

   if (stat(dir, &statBuf) < 0){
   	printf("no file");
	exit(1);
   }

   // TODO: Check if directory or reg file
   //

   if (argc > 2) {
      // check for args
      dirPtr = opendir(argv[2]);
   } else {
     dirPtr = opendir (argv[1]);
   }
   printf("name\tsize\tinode\tuser\tgroup\n");
   while ((entryPtr = readdir (dirPtr))){

      stat(entryPtr->d_name, &statBuf);
      printf ("%-20s \t %ldBytes \t %ld \t %u \t %u\n", entryPtr->d_name, statBuf.st_size, statBuf.st_ino, statBuf.st_uid, statBuf.st_gid);
      if (argc > 2) {
         if(strcmp(argv[1],"-i") == 0) {
            printf("Inode: %ld\n", statBuf.st_ino);
	 } 
	 if (strcmp(argv[1], "-n") == 0) {
	    printf("User ID: %u\n", statBuf.st_uid);
	 }	 
      }

   }

   closedir (dirPtr); 
   return 0; 
}

