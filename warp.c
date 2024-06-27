#include "headers.h"

char* executeWarp( char *path, char *initialDir,char** store) {
    char* lastSlash;
    int u;
    if (strcmp(path, "~") == 0) {
        u=chdir(initialDir);
    } else if (strcmp(path, "-") == 0) {
       u= chdir(store[g-2]);
    } else if (strcmp(path, ".") == 0) {
        // Current directory, no action needed
    } else if (strcmp(path, "..") == 0) {
        // Move to parent directory
        if(g!=0){
        lastSlash = strrchr(store[g-1], '/');
        store[g-1][strlen(store[g-1])-strlen(lastSlash)]='\0';
        u=chdir(store[g-1]);   
        }
        else{
            u=chdir("/home/navdha/gitrepo");
        } 
    } 
     else {
        // Handle other cases (absolute/relative paths)
        if(path[0]=='~'){
            char newDir[PATH_MAX];
            snprintf(newDir, sizeof(newDir), "%s%s", initialDir, path + 1);
           u= chdir(newDir);
        } else {
            u= chdir(path);
           
        }
    }
    if(u==-1){
            printf("No such directory exists!\n");
            return;
           }
    char newDir[PATH_MAX];
    if (getcwd(newDir, sizeof(newDir)) != NULL) {
        strcpy(store[g],newDir);
        g++;
        char*tokenu=strtok(NULL, " \t");
        int original_stdout = dup(STDOUT_FILENO);

        if (tokenu != NULL && (strcmp(tokenu, ">") == 0 || strcmp(tokenu, ">>") == 0)) {
            chdir(initialDir);
            char*tokenu1 = strtok(NULL, " \t"); // Get the filename for redirection
            //printf("%s\n",tokenu1);

            if (tokenu1 != NULL) {
                int mode = strcmp(tokenu, ">") == 0 ? O_WRONLY | O_CREAT | O_TRUNC : O_WRONLY | O_CREAT | O_APPEND;
                int outputFile = open(tokenu1, mode, 0644); // Open the file with permissions 0644
                //printf("nav\n");
                //printf("%d\n",outputFile);
                if (outputFile != -1) {
                    // Redirect stdout to the file
                    fflush(stdout); // Flush the standard output buffer
                    dup2(outputFile, STDOUT_FILENO);
                     fprintf(stdout, "%s\n", newDir);
                    close(outputFile);
                } else {
                    perror("Error opening file for redirection");
                }
            } else {
                fprintf(stderr, "Missing filename for redirection > or >>\n");
            }
            chdir(newDir);
        }
        else{
        printf("Changed directory to: %s\n", newDir);
        }
        // Restore the original stdout
dup2(original_stdout, STDOUT_FILENO);
close(original_stdout);

        //printf("sol\n");
        return tokenu;
    }
}