#include <stdio.h> 
#include <dirent.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{ 
   DIR *dirPtr; 
   struct dirent *entryPtr; 

   if (argc < 2) {
   	printf("Directory name required");
   }
   
  // char* filePath;
  // getcwd(filePath, 500);
  // printf("%s\n", filePath);
  // chdir(argv[1]);
  // getcwd(filePath, 500);
  // printf("%s\n", filePath);
   struct stat statBuf2;

   if(stat(argv[1], &statBuf2) < 0) {
   	printf("Error: file not found");
	exit(1);
   }

   if (!S_ISDIR(statBuf2.st_mode)) {
	   printf("ERROR: argv[1] is not a directory");
	   exit(1);
   }


   dirPtr = opendir (argv[1]);

   struct stat statBuf;

   while ((entryPtr = readdir (dirPtr))) {
      printf ("%-20s\n", entryPtr->d_name);
     if (stat(entryPtr->d_name, &statBuf) < 0) {
      	perror("Error ");
	exit(1);
      }

     printf("File size: %d Bytes\n", statBuf.st_size);
   }

   closedir (dirPtr); 
   return 0; 
}
