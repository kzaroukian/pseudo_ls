#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <errno.h>
#include <string.h>

// Lab 11
// Kaylin Zaroukian and Marc Chesebro

int main(int argc, char *argv[]) 
{ 
   DIR *dirPtr; 
   struct dirent* entryPtr; 

   struct stat statBuf;
   
   char* dir;
   if (argc == 4 ) {
       dir = argv[3];
   } else if (argc == 3) {
       dir = argv[2];
   } else {
      dir = argv[1];
   }	   

   if (stat(dir, &statBuf) < 0){
   	printf("no file");
	exit(1);
   }

   if (!S_ISDIR(statBuf.st_mode)) {
      printf("Error %s is not a directory \n", dir);
      exit(1);
   }

   dirPtr = opendir (dir);
   printf("name\tsize\tgroup\n");
   while ((entryPtr = readdir (dirPtr))){

      stat(entryPtr->d_name, &statBuf);
      printf ("Name: %-20s  Size: \t %ldBytes\n", entryPtr->d_name, statBuf.st_size);
      if (argc > 2) {
	 int i = 1;
         while (i < (argc - 1)) {

            if(strcmp(argv[i],"-i") == 0) {
               printf("Inode: %ld\n", statBuf.st_ino);
	    } 
	    if (strcmp(argv[i], "-n") == 0) {
	       printf("User ID: %u, Group ID: %u\n", statBuf.st_uid, statBuf.st_gid);
	    }
	    i++;
         }	    
      }

   }

   closedir (dirPtr); 
   return 0; 
}

