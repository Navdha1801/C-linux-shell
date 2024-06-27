#include "headers.h"
#include "seekfile.h"
void seekCommand(const char *search, const char *targetDir, int isFileFlag, int isDirectoryFlag,int Eflag,int append,char**store3,char*filename,char*t) {
       
       if(isFileFlag==1 && isDirectoryFlag==1){
        if(append==0){
            printf("Invalid flags!\n");
        }
        else{
            FILE* file1;
            if(strcmp(t,">>")==0){
             file1 = fopen(filename, "a");
            }
            else{
                 file1 = fopen(filename, "w");
            }
    if (file1 != NULL) {
        fprintf(file1, "Invalid flags!\n");
        fclose(file1);
    } else {
        fprintf(stderr, "Error opening file for append: %s\n", filename);
    }
        }
            return;
         }
         int countf=0;
         int countd=0;
         char changedir[MAX_INPUT_LENGTH];
    printf("Searching for '%s' in '%s':\n", search, targetDir);
    listFilesInDirectory(targetDir, search, isFileFlag, isDirectoryFlag,targetDir,&countf,&countd,changedir,store3,append);
    if(countf==0 && countd==0){
        if(append==0){
        printf("No match found!\n");
        }
        else{
            FILE* file1;
            if(strcmp(t,">>")==0){
             file1 = fopen(filename, "a");
            }
            else{
                 file1 = fopen(filename, "w");
            }
    if (file1 != NULL) {
        fprintf(file1, "No match found!\n");
        fclose(file1);
    } else {
        fprintf(stderr, "Error opening file for append: %s\n", filename);
    }
        }
    }
    if(append==1){
        FILE*file2;
        if(strcmp(t,">>")==0){
            file2=fopen(filename,"a");
        }
        else{
            file2=fopen(filename,"w");
        }
        if(file2!=NULL){
            for (int i = 0; i < maintain; i++) {
        fprintf(file2, "%s\n", store3[i]);
    }
          fclose(file2);
        }
        else{
             fprintf(stderr, "Error opening file for append: %s\n", filename);
        }
    }
    if(countf==0 && countd==1 && Eflag==1){
         if (access(changedir, X_OK) == -1) {
        perror("access");
        printf("Missing permissions for task!\n");
        
    }
    if (chdir(changedir) == -1) {
        perror("chdir");
    
    }
    }
    if(countf==1 && countd==0 && Eflag==1){
        char write2[MAX_INPUT_LENGTH];
        if(getcwd(write2,sizeof(write2))!=NULL){
            char* write;
        write=strrchr(changedir, '/');
        changedir[strlen(changedir)-strlen(write)]='\0';
        chdir(changedir);
        char write1[MAX_INPUT_LENGTH];
        strcpy(write1,write+1);
           FILE *file = fopen(write1, "r");
    if (file == NULL) {
        perror("fopen");
    }

    // Read and print the content of the file
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if(append==0){
        printf("%s\n", buffer);
        }
        else{
             FILE* file1;
            if(strcmp(t,">>")==0){
             file1 = fopen(filename, "a");
            }
            else{
                 file1 = fopen(filename, "w");
            }
    if (file1 != NULL) {
        fprintf(file1,"%s", buffer);
        fclose(file1);
    } else {
        fprintf(stderr, "Error opening file for append: %s\n", filename);
    }
        }
    }

    // Close the file
    fclose(file);
        }
        chdir(write2);
    }
}