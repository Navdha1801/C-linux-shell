#include "headers.h"

void listFilesInDirectory(const char *dirPath, const char *search, int isFileFlag, int isDirectoryFlag,const char*basepath,int* countf,int* countd,char*changedir,char**store3,int append) {
    DIR *dir = opendir(dirPath);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char filePath[PATH_MAX];
        snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);

        struct stat fileInfo;
        if (stat(filePath, &fileInfo) == -1) {
            perror("stat");
            continue;
        }
        char navu[MAX_INPUT_LENGTH];
        char navu1[MAX_INPUT_LENGTH];
         if(isFileFlag==0 && isDirectoryFlag==0){
            //printf("reached\n");
            //printf("%s\n",search);
        if ( S_ISREG(fileInfo.st_mode)) {
            if (strstr(entry->d_name, search) !=NULL) {
                (*countf)++;
                navu[0]='.';
                strcpy(navu+1,filePath+strlen(basepath));
                if(append==0){
                printf("\033[0;32m%s\033[0m\n", navu);
                }
                else{
                 strcpy(store3[maintain++],navu);
                }
                strcpy(changedir,filePath);
            }
        }
      else  if ( S_ISDIR(fileInfo.st_mode)) {
            if (strcmp(entry->d_name, search) ==0) {
                (*countd)++;
                 navu1[0]='.';
                  strcpy(navu1+1,filePath+strlen(basepath));
                  if(append==0){
                printf("\033[0;34m%s\033[0m\n", navu1);
                  }
                  else{
                    strcpy(store3[maintain++],navu1);
                  }
                strcpy(changedir,filePath);
            }
            listFilesInDirectory(filePath, search, isFileFlag, isDirectoryFlag,basepath,countf,countd,changedir,store3,append);
        }
        
         }
         else if(isFileFlag==0 && isDirectoryFlag==1){
            if ( S_ISREG(fileInfo.st_mode)) {
            if (strstr(entry->d_name, search) !=NULL) {
                //printf("\033[0;32m%s\033[0m\n", filePath);
            }
        }

      else  if ( S_ISDIR(fileInfo.st_mode)) {
            if (strcmp(entry->d_name, search) ==0) {
                //printf("\033[0;34m%s\033[0m\n", filePath);
                (*countd)++;
                navu1[0]='.';
                  strcpy(navu1+1,filePath+strlen(basepath));
                  if(append==0){
                printf("\033[0;34m%s\033[0m\n", navu1);
                  }
                  else{
                    strcpy(store3[maintain++],navu1);
                  }
                strcpy(changedir,filePath);
            }
            listFilesInDirectory(filePath, search, isFileFlag, isDirectoryFlag,basepath,countf,countd,changedir,store3,append);
        }
         }
         else if(isFileFlag==1 && isDirectoryFlag==0){
             if ( S_ISREG(fileInfo.st_mode)) {
            if (strstr(entry->d_name, search) !=NULL) {
                //printf("\033[0;32m%s\033[0m\n", filePath);
                (*countf)++;
                 navu[0]='.';
                strcpy(navu+1,filePath+strlen(basepath));
                if(append==0){
                printf("\033[0;32m%s\033[0m\n", navu);
                }
                else{
                    strcpy(store3[maintain++],navu);
                }
                strcpy(changedir,filePath);
            }
        }

      else  if ( S_ISDIR(fileInfo.st_mode)) {
            if (strcmp(entry->d_name, search) ==0) {
                //printf("\033[0;34m%s\033[0m\n", filePath);
            }
            listFilesInDirectory(filePath, search, isFileFlag, isDirectoryFlag,basepath,countf,countd,changedir,store3,append);
        }
         }
        
    }

    closedir(dir);
}