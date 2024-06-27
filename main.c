#include "headers.h"
#include "seek.h"
#include "proclore.h"
#include "checkint.h"
#include "count.h"
#include "signal.h"
#include "activities.h"
#include "man.h"
#include <sys/time.h>
#define MAX_BACKGROUND_PROCESSES 10

int g=0;
int count=0;
int value=0;
int execution_time=0;
int track;
char bansal[MAX_INPUT_LENGTH];
 int num_background = 0;
struct ProcessInfo processes[MAX_INPUT_LENGTH];
int numProcesses=0;
int maintain=0;
pid_t background_pids[MAX_BACKGROUND_PROCESSES]; // Array to store background process IDs
pid_t foreground_process_group = -1; // Initialize with an invalid process group
struct termios orig_termios;
int running = 1; // Flag to control the loop
int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);

    char path[PATH_MAX];
    char prompt[MAX_INPUT_LENGTH + PATH_MAX + 10];
    // Get the user's information
    struct passwd *pw = getpwuid(getuid());
    if (!pw) {
        perror("getpwuid");
        return 1;
    }
    const char *username = pw->pw_name;

    // Get the system name
    struct utsname unameData;
    if (uname(&unameData) == -1) {
        perror("uname");
        return 1;
    }
    const char *systemname = unameData.nodename;

    // Get the initial directory
    char initialDir[PATH_MAX];
    if (getcwd(initialDir, sizeof(initialDir)) == NULL) {
        perror("getcwd");
        return 1;
    }
    char** store=NULL;
    store=(char**)malloc(PATH_MAX*sizeof(char*));
    for(int i=0;i<PATH_MAX;i++){
        store[i]=(char*)malloc(1000*sizeof(char));
    }
     char** store1=NULL;
    store1=(char**)malloc(MAX_COMMANDS*sizeof(char*));
    for(int i=0;i<MAX_COMMANDS;i++){
        store1[i]=(char*)malloc(MAX_INPUT_LENGTH*sizeof(char));
    }
    char** store2=NULL;
    store2=(char**)malloc(100*sizeof(char*));
    for(int i=0;i<100;i++){
        store2[i]=(char*)malloc(MAX_INPUT_LENGTH*sizeof(char));
    }
     char** store3=NULL;
    store3=(char**)malloc(100*sizeof(char*));
    for(int i=0;i<100;i++){
        store3[i]=(char*)malloc(MAX_INPUT_LENGTH*sizeof(char));
    }
    int a=0;
    int status;
    char* contain;
    //pid_t background_pids[MAX_BACKGROUND_PROCESSES]; // Array to store background process IDs
    while (1) {

        // Get the current directory
        if (getcwd(path, sizeof(path)) == NULL) {
            perror("getcwd");
            return 1;
        }

        // Create and print the prompt
        const char *relPath = getRelativePath(path, initialDir);
        if(execution_time<=2){
        snprintf(prompt, sizeof(prompt), "<%s@%s:%s>", username, systemname, relPath);
        printf("%s ", prompt);
        }
        else{
             snprintf(prompt, sizeof(prompt), "<%s@%s:%s %s :%d>", username, systemname, relPath,bansal,execution_time);
        printf("%s ", prompt);
        }
        // Read user input
        char userInput[MAX_INPUT_LENGTH];
         if (fgets(userInput, sizeof(userInput), stdin) == NULL){
            printf("Exiting MyShell...\n");
            kill(0, SIGTERM); 
            sleep(1); 

            exit(0);
        }
        int pipes=countOccurrences(userInput,'|');
        if(pipes!=0){
                char *commands[MAX_COMMANDS];
                   int numCommands = 0;
              char *token = strtok(userInput, "|");
    while (token != NULL && numCommands < MAX_COMMANDS) {
       
        commands[numCommands++] = token;
        token = strtok(NULL, "|");
    }

    if (numCommands <2 || strcmp(commands[1],"  ")==0) {
        //fprintf(stderr, "Invalid use of pipe\n");
        printf("invalid use of pipe\n");
        //return 1;
    }

    int pipefds[numCommands - 1][2];

    for (int i = 0; i < numCommands - 1; i++) {
        if (pipe(pipefds[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < numCommands; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {  
            if (i > 0) {
                close(pipefds[i - 1][1]);  
                dup2(pipefds[i - 1][0], STDIN_FILENO);  
                close(pipefds[i - 1][0]);  
            }

            if (i < numCommands - 1) {
                close(pipefds[i][0]);  
                dup2(pipefds[i][1], STDOUT_FILENO);  
                close(pipefds[i][1]);  
            }

            execlp("/bin/sh", "sh", "-c", commands[i], NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {  
            if (i > 0) {
                close(pipefds[i - 1][0]);  
                close(pipefds[i - 1][1]);  
            }
        }
    }

    for (int i = 0; i < numCommands - 1; i++) {
        close(pipefds[i][0]);  
        close(pipefds[i][1]);
    }
    for (int i = 0; i < numCommands; i++) {
        wait(NULL);
    }

        }
        else{
        // Remove newline from input
        userInput[strcspn(userInput, "\n")] = '\0';
         for (int i = 0; i < num_background; i++) {
            int status;
           pid_t ended_pid = waitpid(background_pids[i], &status, WNOHANG);
            if (ended_pid > 0) {
                if (WIFEXITED(status)) {
                    printf("Background process %d exited normally\n", ended_pid);
                } else {
                    printf("Background process %d exited abnormally\n", ended_pid);
                }
                // Update the state of the process to "Stopped"
                updateProcessState(processes, ended_pid, "Stoppedf", numProcesses);

                // Remove the ended process from the array
                for (int j = i; j < num_background - 1; j++) {
                    background_pids[j] = background_pids[j + 1];
                }
                num_background--;
                i--; // Adjust index after removing an element
            }
        }
//}

        char input[MAX_INPUT_LENGTH];
        char input5[MAX_INPUT_LENGTH];
        char input11[MAX_INPUT_LENGTH];
        strcpy(input,userInput);
        strcpy(input5,userInput);
        strcpy(input11,userInput);
        int y=countOccurrences(userInput, ';');
        //printf("%d\n",y);
        char contain1[MAX_INPUT_LENGTH];
        char input1[MAX_INPUT_LENGTH];
        char input3[MAX_INPUT_LENGTH];
        char input4[MAX_INPUT_LENGTH];
        // Tokenize input using space and tab characters
        char* token = strtok(userInput, " \t");
        //printf("%s\n",token);
      
        while (token != NULL) {
            //printf("work\n");
              //track=index%MAX_COMMANDS;
              //if(y==0){
             if(count>MAX_COMMANDS && value%MAX_COMMANDS==0){
                if(strcmp(token,"pastevents")!=0 &&strcmp(token,";")!=0 && strcmp(input,store1[14])!=0 && strstr(input,"pastevents")==NULL){
                    track=value%MAX_COMMANDS; 
                    int n= countOccurrences(input, ';');
                strcpy(store1[track],input);
                count++;
                value++;
                    
                    
            }
            }
           
            else if(count<=MAX_COMMANDS && value%MAX_COMMANDS==0){
                if(strcmp(token,"pastevents")!=0 && strcmp(token,";")!=0 && strstr(input,"pastevents")==NULL){
                    track=value%MAX_COMMANDS;
                strcpy(store1[track],input);
                count++;
                value++;
               
            }
            }
            
            else{
                //printf("work2\n");
            if(strcmp(token,"pastevents")!=0 &&strcmp(token,";")!=0 && strcmp(input,store1[(value%MAX_COMMANDS)-1])!=0 && strstr(input,"pastevents")==NULL){ 
                //printf("more\n");
                track=value%MAX_COMMANDS;
                //printf("why\n");
                strcpy(store1[track],input);
                count++;
                value++;
                
            }
            }
            //printf("work1\n");
              //}
            
              if (strcmp(token, ";") == 0) {

            } else if (strcmp(token, "warp") == 0) {
                // Execute the "warp" command with arguments
                execution_time=0;
                token = strtok(NULL, " \t");
               // printf("%s\n",token);
                if (token == NULL || strcmp(token,";")==0) {
                    chdir(initialDir);
                    strcpy(store[g],initialDir);
                    g++;
                    printf("%s\n", initialDir);
                }
                
                while (token != NULL) {
                    //printf("%s\n",token);
                    if(strcmp(token,";")==0 || strcmp(token,">")==0 || strcmp(token,">>")==0){
                        break;
                    }
                    char*copydir=executeWarp(token, initialDir, store);
                    //printf("%s\n",copydir);
                    //token = strtok(NULL, " \t");
                    if(copydir==NULL){
                        //printf("hell\n");
                        token=NULL;
                    }
                    else{
                    strcpy(token,copydir);
                    }
                    
                }
            } else if (strcmp(token, "peek") == 0) {
                execution_time=0;
                token = strtok(NULL, " \t");
                bool allFlag = false;
                bool longFlag = false;

                // Check for flags
                while (token != NULL && token[0] == '-' && token[1]!='\0') {
                    for (int i = 1; token[i] != '\0'; i++) {
                        if (token[i] == 'a') {
                            allFlag = true;
                        } else if (token[i] == 'l') {
                            longFlag = true;
                        }
                    }
                    token = strtok(NULL, " \t");
                }
                 char copy[PATH_MAX];
                 char*filename;
                 int append=0;
                if (token == NULL) {
                    token = ".";
                }
                else if( strcmp(token,";")==0){
                     token = ".";
                }
                else if(strcmp(token,">")==0 || strcmp(token,">>")==0){
                    token =".";
                }
                else if(strcmp(token,"~")==0){
                    strcpy(token,initialDir);
                  
                }
                else if(token[0]=='~'){
                    strcpy(copy,initialDir);
                    strcat(copy,token+1);
                    strcpy(token,copy);
                    
                }
                else if(strcmp(token,"..")==0){
                    if(getcwd(copy,sizeof(copy))!=NULL){
                        char*last= strrchr(copy, '/');
                        copy[strlen(copy)-strlen(last)]='\0';
                        strcpy(token,copy);
                       
                    }
                }
                else if(strcmp(token,"-")==0){
                    strcpy(token,store[g-2]);
                    
                }
                else if(token[0]=='/'){
                
                }
                else{
                    char*di;
                    if(getcwd(di,sizeof(di))!=NULL){
                    strcpy(copy,di);
                    strcat(copy,"/");
                    strcat(copy,token);
                    strcpy(token,copy);
                    }
                }
                 listFiles(token, allFlag, longFlag);
            }
            else if(strcmp(token,"pastevents")==0){
                execution_time=0;
                int ae;
                token=strtok(NULL, " \t");
                if(token==NULL || strcmp(token,";")==0){
                if(count>0){
                if(count<=MAX_COMMANDS){
                    for(int z=0;z<count;z++){
                        printf("%s\n",store1[z]);
                    }
                }
                else{
                    for(int z=track+1;z<MAX_COMMANDS;z++){

                        printf("%s\n",store1[z]);
                    }
                    for(int z=0;z<track+1;z++){
                        printf("%s\n",store1[z]);
                    }
                }
                }
                }
                else if(strcmp(token,">")==0 || strcmp(token,">>")==0){
                    if(count>0){
                        char*filename=strtok(NULL, " \t");
                        if (count <= MAX_COMMANDS) {
    FILE *outputFile; 
    if(strcmp(token,">")==0){
    outputFile = fopen(filename, "w");
    }
    else{
        outputFile = fopen(filename, "a");
    }
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
    }
    for (int z = 0; z < count; z++) {
        fprintf(outputFile, "%s\n", store1[z]);
    }
    fclose(outputFile); 
} else {
     FILE *outputFile;
    if(strcmp(token,">")==0){
    outputFile = fopen(filename, "w");
    }
    else{
        outputFile = fopen(filename, "a");
    }
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename); 
    }
    for (int z = track + 1; z < MAX_COMMANDS; z++) {
        fprintf(outputFile, "%s\n", store1[z]); 
    }
    for (int z = 0; z <= track; z++) {
        fprintf(outputFile, "%s\n", store1[z]); 
    }
    fclose(outputFile);
}

                    }
                }
                else if(strcmp(token,"purge")==0){
                    count=0;
                    value=0;
                }
                else if(strcmp(token,"execute")==0){
                    token=strtok(NULL, " \t");
                    ae=atoi(token);
                    //printf("hello5\n");
                    //printf("%d\n",ae);
                    if(count<=MAX_COMMANDS){
                        //printf("ya\n");
                      exe(store1[count-ae],store1,store,initialDir,store3);
                      //printf("yah\n");
                    }
                    else{
                        if(track-(ae-1)>=0){
                            exe(store1[track-(ae-1)],store1,store,initialDir,store3);
                        }
                        else{
                            exe(store1[MAX_COMMANDS-(track-(ae-1))],store1,store,initialDir,store3);
                        }
                    }
                
                int i;
                for(i=0;i<strlen(input11);i++){
                    if(ae==(int)(input11[i]-'0')){
                        break;
                    }
                }
                token=strtok(input11+i, " \t");
                }
            }
            else if(strcmp(token,"seek")==0){
                int append=0;
                execution_time=0;
                token=strtok(NULL, " \t");
                int file=0;
                int dir=0;
                int eflag=0;
                while(token!=NULL && token[0]=='-'){
                     if(token[1]=='f'){
                        file=1;
                     }
                     else if(token[1]=='d'){
                        dir=1;
                     }
                     else if(token[1]=='e'){
                           eflag=1;
                     }
                     token=strtok(NULL, " \t");
                }
                char search[MAX_INPUT_LENGTH]; 
                strcpy(search,token);
                char navdha[MAX_INPUT_LENGTH];
                char* token11;
                token=strtok(NULL, " \t");
                if(token==NULL){
                    //token=".";
                    //printf("%s\n",token);
                    token11 = malloc(1000); // Allocate memory for "."
    if (token11 != NULL) {
        strcpy(token11, ".");
        //printf("%s\n", token11);
    } else {
        perror("malloc");
    }
                }
                else if(strcmp(token,">")==0 || strcmp(token,">>")==0){
                    //printf("bhai\n");
                     token11 = malloc(1000); // Allocate memory for "."
    if (token11 != NULL) {
        strcpy(token11, ".");
        //printf("%s\n", token11);
    } else {
        perror("malloc");
    }
                }
                else{
                strcpy(token11,token);
                }
                 if (strcmp(token11,".")==0 || strcmp(token11,";")==0) {
                //token = ".";
                if(getcwd(navdha,sizeof(navdha))!=NULL){
                        //printf("%s\n",navdha);
                        strcpy(token11,navdha);
                        //printf("%s\n",token);
                    }
                 }
                 if(strcmp(token11,"~")==0){
                    strcpy(token11,initialDir);
                 }
                 if(token11[0]=='.' && token11[1]!='\0'){
                    if(getcwd(navdha,sizeof(navdha))!=NULL){
                        strcat(navdha,token11+1);
                        strcpy(token11,navdha);
                    }
                 }
                 char directory[MAX_INPUT_LENGTH];
                 if(token!=NULL && strcmp(token,">")!=0 && strcmp(token,">>")!=0){
                 token=strtok(NULL, " \t");
                 }
                 strcpy(directory,token11);
                 if(token==NULL){
                seekCommand(search, directory, file,dir,eflag,append,store3,NULL,NULL );
                 }
                else if( strcmp(token,">")==0 || strcmp(token,">>")==0){
                           append=1;
                           char*filename=strtok(NULL, " \t");
                           seekCommand(search, directory, file,dir,eflag,append,store3,filename,token );
                 }
                 else{
                seekCommand(search, directory, file,dir,eflag,append,store3,NULL,NULL );
                 }
                maintain=0;
            }
            else if(strcmp(token,"echo")==0 ){
                char C;
                char D;
                char token311[MAX_INPUT_LENGTH];
                const char*token312;
                char tokennav[MAX_INPUT_LENGTH];
                strcpy(tokennav,input5);
                if(countOccurrences(input5,';')==0){
                 //strcpy(token311,input5+5);
                   char*position = strstr(tokennav, "echo");
                   //printf("%s\n",position);
                   strcpy(token311,position+5);
                   //printf("%c\n",token311[strlen(token311)-1]);
                   C=token311[strlen(token311)-1];
                   if(C!='&'){
                    int jy=countOccurrences(token311,'>');
                    int jb=countOccurrences(token311,'>>');
                    if(jy==0 && jb==0){
                     pid_t pid2 = fork();

            if (pid2 == 0) {
                // Child process
                execlp("echo","echo",token311,(char*)NULL );
                perror("exec");
                exit(EXIT_FAILURE);
            } else if (pid2 > 0) {
                // Parent process
                int status;
                foreground_process_group=pid2;
                waitpid(pid2, &status, 0);
                if (WIFEXITED(status)) {
            addProcess(processes, pid2, token, "Stoppedf", &numProcesses,"foreground",token311);
            foreground_process_group=-1;
        }
      else  if (WIFSTOPPED(status)) {
            addProcess(processes, pid2, token, "Stopped", &numProcesses,"background",token311);
            foreground_process_group=-1;
        }
        else if (WIFSIGNALED(status)) {
            addProcess(processes, pid2, token, "Stoppedf", &numProcesses,"foreground",token311);
            foreground_process_group=-1;
        }
            }
            
        else {
                perror("fork");
            }
                    }
                    else{
                        int i;
                        char sn[MAX_INPUT_LENGTH];
                        char navu='\0';
                        char*navu1;
                        for( i=0;i<strlen(token311);i++){
                            if(token311[i]=='>' && token311[i+1]!='>'){
                                navu=token311[i];
                                strcpy(sn,token311+i+2);//sn contains filename
                                token311[i]='\0';
                                break;
                            }
                            else if(token311[i]=='>' && token311[i+1]=='>'){
                                strcpy(sn,token311+i+3);//sn contains filename
                                token311[i]='\0';
                                break;
                            }
                        }
            int original_stdout = dup(STDOUT_FILENO);
            if (sn != NULL) {
                int mode = navu== '>'  ? O_WRONLY | O_CREAT | O_TRUNC : O_WRONLY | O_CREAT | O_APPEND;
                int outputFile = open(sn, mode, 0644); // Open the file with permissions 0644
                //printf("nav\n");
                //printf("%d\n",outputFile);
                if (outputFile != -1) {
                    // Redirect stdout to the file
                    fflush(stdout); // Flush the standard output buffer
                    dup2(outputFile, STDOUT_FILENO);
                     fprintf(stdout, "%s\n", token311);
                    close(outputFile);
                } else {
                    perror("Error opening file for redirection");
                }
            } else {
                fprintf(stderr, "Missing filename for redirection > or >>\n");
            }
            dup2(original_stdout, STDOUT_FILENO);
            close(original_stdout);

                    }
                   }
                   else{
                    token311[strlen(token311)-1]='\0';
                    pid_t pid13 = fork();
    if (pid13 == 0) {
    execlp("echo", "echo", token311, (char *)NULL);  // Use execlp for simplicity
    
    perror("execlp");  // Print error if execlp fails
    exit(1);
       
    } else if (pid13 > 0) {
        
        if (num_background < MAX_BACKGROUND_PROCESSES) {
            addProcess(processes, pid13, "echo", "Running", &numProcesses,"background",token311);
            
                background_pids[num_background] = pid13;
                num_background++;
                printf("%d\n", pid13);
            } else {
                printf("Maximum number of background processes reached\n");
            }
    } else {
        perror("fork");
    }
                   }
                }
                else{
                    token312=strtok(NULL, ";");
                    printf("%c\n",token312[strlen(token312)-2]);
                    D=token312[strlen(token312)-2];
                    if(D!='&'){
                     pid_t pid2 = fork();

            if (pid2 == 0) {
                // Child process
                execlp("echo","echo",token312,(char*)NULL );
                perror("exec");
                exit(EXIT_FAILURE);
            } else if (pid2 > 0) {
                // Parent process
                int status;
                 foreground_process_group=pid2;
                waitpid(pid2, &status, 0);
                if (WIFEXITED(status)) {
            // The foreground process has completed
            addProcess(processes, pid2, token, "Stoppedf", &numProcesses,"foreground",token312);
            foreground_process_group=-1;
        }
        else if (WIFSTOPPED(status)) {
            // The foreground process has completed
            addProcess(processes, pid2, token, "Stopped", &numProcesses,"background",token312);
            foreground_process_group=-1;
        }
        else if (WIFSIGNALED(status)) {
            // The foreground process has completed
            addProcess(processes, pid2, token, "Stoppedf", &numProcesses,"foreground",token312);
            foreground_process_group=-1;
        }
            }
            
        else {
                perror("fork");
            }
                   }
                   else{
                    pid_t pid13 = fork();
    if (pid13 == 0) {
    execlp("echo", "echo", token312, (char *)NULL);  // Use execlp for simplicity
    
    perror("execlp");  // Print error if execlp fails
    exit(1);
       
    } else if (pid13 > 0) {
        
        if (num_background < MAX_BACKGROUND_PROCESSES) {
            addProcess(processes, pid13, "echo", "Running", &numProcesses,"background",token312);
            
                background_pids[num_background] = pid13;
                num_background++;
                printf("%d\n", pid13);
            } else {
                printf("Maximum number of background processes reached\n");
            }
    } else {
        perror("fork");
    }
                   }
                }
                
            }
            else if(strcmp(token,"pwd")==0 || strcmp(token,"gedit")==0 || strcmp(token,"vim")==0){
                     char*tokenc=strtok(NULL, " \t");
                     if(tokenc!=NULL && strcmp(tokenc,"&")==0){
                      
            pid_t pid13 = fork();
    if (pid13 == 0) {
    execlp(token, token, (char *)NULL);
    
    perror("execlp");
    exit(1);
       
    } else if (pid13 > 0) {
        
        if (num_background < MAX_BACKGROUND_PROCESSES) {
            addProcess(processes, pid13, token, "Running", &numProcesses,"background",NULL);
            
                background_pids[num_background] = pid13;
                num_background++;
                printf("%d\n", pid13);
            } else {
                printf("Maximum number of background processes reached\n");
            }
    } else {
        perror("fork");
    }
                     }
                     else if(tokenc!=NULL && strcmp(tokenc,">")==0){
                        char*filename=strtok(NULL, " \t");
                        char buf[MAX_INPUT_LENGTH];
                        if (getcwd(buf, sizeof(buf)) != NULL){
                            FILE *outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
    }
        fprintf(outputFile, "%s\n",buf);
    
    fclose(outputFile);
                        }
                     }
                     else if(tokenc!=NULL && strcmp(tokenc,">>")==0){
                        char*filename=strtok(NULL, " \t");
                        char buf[MAX_INPUT_LENGTH];
                        if (getcwd(buf, sizeof(buf)) != NULL){
                            FILE *outputFile = fopen(filename, "a");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
    }
        fprintf(outputFile, "%s\n",buf);
    
    fclose(outputFile);
                        }
                     }
                     else{
    pid_t pid3 = fork();

            if (pid3 == 0) {
                     execlp(token,token,(char*)NULL );
                
                perror("exec");
                exit(EXIT_FAILURE);
            } else if (pid3 > 0) {
                int status;
                foreground_process_group=pid3;
                waitpid(pid3, &status,WUNTRACED );
                if (WIFEXITED(status)) {
            addProcess(processes, pid3, token, "Stoppedf", &numProcesses,"foreground",NULL);
            foreground_process_group=-1;
        }
        else if(WIFSTOPPED(status)){
            addProcess(processes, pid3, token, "Stopped", &numProcesses,"background",NULL);
            foreground_process_group=-1;
        }
        else if (WIFSIGNALED(status)) {
        //printf("Process terminated by signal: %d\n", WTERMSIG(status));
        addProcess(processes, pid3, token, "Stoppedf", &numProcesses, "foreground", NULL);
        foreground_process_group = -1;
    }
            } else {
                perror("fork");
            }
                     }
            }
            else if(strcmp(token,"ping")==0){
                int trust=0;
                 int processpid=atoi(strtok(NULL, " \t"));
                 int signal=atoi(strtok(NULL, " \t"));
                 if(signal%32==9){
                    int i;
                    for(i=0;i<numProcesses;i++){
                        if (processes[i].pid == processpid) {
                            trust=1;
                        // Check if the process is in a stopped state
                        if (strcmp(processes[i].state, "Stoppedf") == 0) {
                            printf("Process with PID %d is already stoppedf. Removing from array.\n", processpid);
                            removeProcess(processes, &numProcesses, i);
                        } else {
                            // Send SIGKILL to the specified process
                            if (kill(processpid, SIGKILL) == 0) {
                                printf("Sent SIGKILL to process with PID %d\n", processpid);
                                // Remove the process from the array
                                removeProcess(processes, &numProcesses, i);
                            } else {
                                perror("kill");
                            }
                        }
                        break;    
                        
                    }
                    }
                    if (i == numProcesses && trust==0) {
                    printf("No such process with PID %d\n", processpid);
                }
                 }
                 else if(signal%32==17 || signal%32==19 || signal%32==23){
                    pid_t target_pid = processpid;
    if (kill(target_pid, SIGSTOP) == 0) {
        printf("Sent SIGSTOP to process with PID %d\n", target_pid);
        update_process_state(target_pid, "Stopped");
    } else {
        perror("kill");
    }

                 }
                 else if(signal%32==18 || signal%32==20 || signal%32==24){
                     pid_t target_pid = processpid;
    if (kill(target_pid, SIGTSTP) == 0) {
        printf("Sent SIGTSTP to process with PID %d\n", target_pid);
        update_process_state(target_pid, "Stopped");
    } else {
        perror("kill");
    }
                 }
                 else if(signal%32==19 || signal%32==18 || signal%32==25){
                      pid_t target_pid = processpid;
    if (kill(target_pid, SIGCONT) == 0) {
        printf("Sent SIGCONT to process with PID %d\n", target_pid);
        update_process_state(target_pid, "Running");
    } else {
        perror("kill");
    }
                 }
                }else if(strcmp(token,"cat")==0){
                 token=strtok(NULL, " \t");
                 if(strcmp(token,"<")==0){
                    token=strtok(NULL, " \t");
                 }
                 char*tokens=strtok(NULL, " \t");
                  if (tokens == NULL) {
        char filePath[PATH_MAX]; // Define a buffer for the file path
        snprintf(filePath, sizeof(filePath), "%s/%s", getcwd(NULL, 0), token);
        //printf("%s\n",filePath);
        pid_t pid39 = fork();

        if (pid39 == 0) {
            // Child process
            if(access(filePath, F_OK) != -1){
            execlp("cat", "cat", filePath, (char *)NULL);
            perror("exec");
            exit(EXIT_FAILURE);
            }
            else{
                 printf("No such input file found!\n");
            }
        } else if (pid39 > 0) {
            // Parent process
            int status;
            foreground_process_group=pid39;
            waitpid(pid39, &status, 0);
            if (WIFEXITED(status)) {
                // The foreground process has completed
                addProcess(processes, pid39, "cat", "Stoppedf", &numProcesses,"foreground",token);
                foreground_process_group=-1;
            }
           else if (WIFSTOPPED(status)) {
                                 addProcess(processes, pid39, "cat", "Stopped", &numProcesses,"background",token);
                        }
           else if (WIFSIGNALED(status)) {
                                 addProcess(processes, pid39, "cat", "Stoppedf", &numProcesses,"foreground",token);
                        }

        } else {
            perror("fork");
        }
    } else {
        //fprintf(stderr, "Usage: cat <filename>\n");
        char*filename1=strtok(NULL, " \t");
                 if (filename1 != NULL) {
                        int mode = strcmp(tokens, ">") == 0 ? O_WRONLY | O_CREAT | O_TRUNC : O_WRONLY | O_CREAT | O_APPEND;

                        pid_t pid = fork();

                        if (pid == 0) {
                            // Child process
                            int outputFile = open(filename1, mode, 0644); 

                            if (outputFile != -1) {
                                // Redirect stdout to the file
                                dup2(outputFile, STDOUT_FILENO);
                                execlp("cat", "cat",token, NULL);  
                                perror("exec");
                                exit(EXIT_FAILURE);
                                close(outputFile);
                            } else {
                                perror("Error opening file for redirection");
                                exit(EXIT_FAILURE);
                            }
                        } else if (pid > 0) {
                            // Parent process
                            int status;
                            waitpid(pid, &status, 0);
                            if (WIFEXITED(status)) {
                                 addProcess(processes, pid, "cat", "Stoppedf", &numProcesses,"foreground",token);
                                //printf("Command executed successfully.\n");
                        }
                        else if (WIFSTOPPED(status)) {
                                 addProcess(processes, pid, "cat", "Stopped", &numProcesses,"background",token);
                                //printf("Command executed successfully.\n");
                        }
                        else if (WIFSIGNALED(status)) {
                                 addProcess(processes, pid, "cat", "Stoppedf", &numProcesses,"foreground",token);
                                //printf("Command executed successfully.\n");
                        }
                            }
                         else {
                            perror("fork");
                        }
                
                    }
                     else {
                        printf("Missing output filename for redirection > or >>.\n");
                    }

    }            
                 
            }
            else if(strcmp(token,"wc")==0){
                char filename[MAX_INPUT_LENGTH];
                token=strtok(NULL, " \t");
                //printf("%s\n",token);
                if(strcmp(token,"<")==0){
                    token=strtok(NULL, " \t");
                     strcpy(filename,token);
                }
                else{
                    //printf("hel\n");
                    strcpy(filename,token);
                     //printf("hel\n");
                }
                //printf("%s\n",filename);
                token=strtok(NULL, " \t");
                if(token==NULL){
                  if (filename != NULL) {
        pid_t pid39 = fork();

        if (pid39 == 0) {
            // Child process
            if(access(filename, F_OK) != -1){
            execlp("wc", "wc", filename, (char *)NULL);
            perror("exec");
            exit(EXIT_FAILURE);
            }
            else{
                printf("no such input file found!\n");
            }
        } else if (pid39 > 0) {
            // Parent process
            int status;
            waitpid(pid39, &status, 0);
            foreground_process_group=pid39;
            if (WIFEXITED(status)) {
                // The foreground process has completed
                addProcess(processes, pid39, "wc", "Stoppedf", &numProcesses,"foreground",filename);
                foreground_process_group=-1;
            }
        } else {
            perror("fork");
        }
    }    
          
                }
                else if(strcmp(token,">")==0 || strcmp(token,">>")==0){
                 char*filename1=strtok(NULL, " \t");
                 if (filename1 != NULL) {
                        int mode = strcmp(token, ">") == 0 ? O_WRONLY | O_CREAT | O_TRUNC : O_WRONLY | O_CREAT | O_APPEND;

                        pid_t pid = fork();

                        if (pid == 0) {
                            // Child process
                            int outputFile = open(filename1, mode, 0644); 

                            if (outputFile != -1) {
                                // Redirect stdout to the file
                                dup2(outputFile, STDOUT_FILENO);
                                execlp("wc", "wc",filename, NULL);  
                                perror("exec");
                                exit(EXIT_FAILURE);
                                close(outputFile);
                            } else {
                                perror("Error opening file for redirection");
                                exit(EXIT_FAILURE);
                            }
                        } else if (pid > 0) {
                            // Parent process
                            int status;
                            waitpid(pid, &status, 0);
                            if (WIFEXITED(status)) {
                                 addProcess(processes, pid, "wc", "Stoppedf", &numProcesses,"foreground",filename);
                                //printf("Command executed successfully.\n");
                        }
                        else if (WIFSTOPPED(status)) {
                                 addProcess(processes, pid, "wc", "Stopped", &numProcesses,"background",filename);
                                //printf("Command executed successfully.\n");
                        }
                        else if (WIFSIGNALED(status)) {
                                 addProcess(processes, pid, "wc", "Stoppedf", &numProcesses,"foreground",filename);
                                //printf("Command executed successfully.\n");
                        }
                            }
                         else {
                            perror("fork");
                        }
                
                    }
                     else {
                        printf("Missing output filename for redirection > or >>.\n");
                    }
                } 
                }
             else if(strcmp(token,"sleep")==0){
                strcpy(bansal,token);
                token=strtok(NULL, " \t");
               char* tokend=strtok(NULL, " \t");
               //printf("%s\n",tokend);
           if(tokend!=NULL && strcmp(tokend,"&")==0){
            //printf("nav\n");
            pid_t pid13 = fork();
    if (pid13 == 0) {
    execlp("sleep", "sleep", token, (char *)NULL);  
    
    perror("execlp"); 
    exit(1);
       
    } else if (pid13 > 0) {
        
        if (num_background < MAX_BACKGROUND_PROCESSES) {

            addProcess(processes, pid13, "sleep", "Running", &numProcesses,"background",token);
            
                background_pids[num_background] = pid13;
                num_background++;
                printf("%d\n", pid13);
            } else {
                printf("Maximum number of background processes reached\n");
            }
    } else {
        perror("fork");
    }
        
       }         
            else{
               //printf("navdha\n");
     struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);

        pid_t pid1 = fork();
                  if (pid1 == 0) {
            execlp(bansal, bansal,token, (char *)NULL);
            perror("exec");
            exit(EXIT_FAILURE);
        } else if (pid1 > 0) {
            int status;
            foreground_process_group = pid1;
            waitpid(pid1, &status, WUNTRACED);
            gettimeofday(&end_time, NULL);
            execution_time = (int)(end_time.tv_sec - start_time.tv_sec);
            if (WIFEXITED(status)) {
            addProcess(processes, pid1, "sleep", "Stoppedf", &numProcesses,"foreground",token);
            //printf("g\n");
             foreground_process_group = -1;
        }
        else if (WIFSTOPPED(status)) {
            addProcess(processes, pid1, "sleep", "Stopped", &numProcesses,"background",token);
            //printf("g\n");
             foreground_process_group = -1;
        }
         else if (WIFSIGNALED(status)) {
            addProcess(processes, pid1, "sleep", "Stoppedf", &numProcesses,"foreground",token);
            //printf("g\n");
             foreground_process_group = -1;
        }  
        }
        
        else {
            perror("fork");
        }

            }
            }
            else if(strcmp(token,"emacs")==0){
                token=strtok(NULL, " \t");
                char*check1=strtok(NULL, " \t");
                if(check1!=NULL && strcmp(check1,"&")==0){
                   pid_t pid13 = fork();
    if (pid13 == 0) {
    execlp("emacs", "emacs", token, (char *)NULL);  
    
    perror("execlp"); 
    exit(1);
       
    } else if (pid13 > 0) {
        
        if (num_background < MAX_BACKGROUND_PROCESSES) {

            addProcess(processes, pid13, "emacs", "Running", &numProcesses,"background",token);
            
                background_pids[num_background] = pid13;
                num_background++;
                printf("%d\n", pid13);
            } else {
                printf("Maximum number of background processes reached\n");
            }
    } else {
        perror("fork");
    }
        
                }
                else{
                pid_t pid1 = fork();
                  if (pid1 == 0) {
            execlp("emacs", "emacs",token, (char *)NULL);
            perror("exec");
            exit(EXIT_FAILURE);
        } else if (pid1 > 0) {
            int status;
            foreground_process_group = pid1;
            waitpid(pid1, &status, WUNTRACED);
           
            if (WIFEXITED(status)) {
            addProcess(processes, pid1, "emacs", "Stoppedf", &numProcesses,"foreground",token);
            //printf("g\n");
             foreground_process_group = -1;
        }
        else if (WIFSTOPPED(status)) {
            addProcess(processes, pid1, "emacs", "Stopped", &numProcesses,"background",token);
            //printf("g\n");
             foreground_process_group = -1;
        }
         else if (WIFSIGNALED(status)) {
            addProcess(processes, pid1, "emacs", "Stoppedf", &numProcesses,"foreground",token);
            //printf("g\n");
             foreground_process_group = -1;
        }  
        }
        
        else {
            perror("fork");
        }
            }
            }
            else if(strcmp(token,"bg")==0){
                  char* pid_str = strtok(NULL, " \t\n");
            if (pid_str == NULL) {
                printf("Usage: bg <pid>\n");
                continue;
            }
            pid_t pidb = atoi(pid_str);
            if (process_exists(pidb)){
                 if (kill(pidb, SIGCONT) == 0) {
                printf("Resumed the process with PID %d, previously stopped in the background, now in the background.\n", pidb);
                update_process_state(pidb, "Running");
            } else {
                perror("kill");
            }
            }
            else{
            int so;
            for( so=0;so<numProcesses;so++){
                if(processes[so].pid==pidb){
                    break;
                }
            }
            if(so==numProcesses){
                printf("no such process exists\n");
            }
            else{
               if(processes[so].argument==NULL){
                 pid_t pid13 = fork();
    if (pid13 == 0) {
    execlp(processes[so].command,processes[so].command , (char *)NULL);
    
    perror("execlp");
    exit(1);
       
    } else if (pid13 > 0) {
        
        if (num_background < MAX_BACKGROUND_PROCESSES) {
            //addProcess(processes, pid13, processes[so].command, "Running", &numProcesses,"background",NULL);
                 update_process_state(pid13,"Running");
                background_pids[num_background] = pid13;
                num_background++;
                printf("%d\n", pid13);
            } else {
                printf("Maximum number of background processes reached\n");
            }
    } else {
        perror("fork");
    }
               }
               else{
                 pid_t pid13 = fork();
    if (pid13 == 0) {
    execlp(processes[so].command,processes[so].command ,processes[so].argument, (char *)NULL);
    
    perror("execlp");
    exit(1);
       
    } else if (pid13 > 0) {
        
        if (num_background < MAX_BACKGROUND_PROCESSES) {
            //addProcess(processes, pid13, processes[so].command, "Running", &numProcesses,"background",processes[so].argument);
                 update_process_state(pid13,"Running");
                background_pids[num_background] = pid13;
                num_background++;
                printf("%d\n", pid13);
            } else {
                printf("Maximum number of background processes reached\n");
            }
    } else {
        perror("fork");
    }
               }
            }
            }
            }
            else if(strcmp(token,"fg")==0){
                char* pid_str = strtok(NULL, " \t\n");
            if (pid_str == NULL) {
                printf("Usage: fg <pid>\n");
                continue;
            }
            pid_t pid222 = atoi(pid_str);
            if (process_exists(pid222)) {
                //printf("he\n");
                int h;
                for(int k=0;k<numProcesses;k++){
                    if(pid222==processes[k].pid){
                          h=k;
                          break;
                    }
                }
                if(strcmp(processes[h].state,"Running")==0){
                int status;
                if (waitpid(pid222, &status, 0) != -1) {
                    printf("executed the process with pid %d running in background earlier in foreground.\n", pid222);
                    update_process_state(pid222, "Stoppedf");
                    update_process_state1(pid222, "foreground");

                } else {
                    perror("waitpid");
                }
                }
                else
            // Send a SIGCONT signal to resume the process
            if (kill(pid222, SIGCONT) == 0 &&  waitpid(pid222, &status, 0)!=-1) {
                printf("Resumed the process with PID %d, previously stopped in the background, now in the foreground.\n", pid222);
                update_process_state(pid222, "Stoppedf");
                update_process_state1(pid222, "foreground"); 
            } else {
                perror("kill");
            }

                }
             else {
                int sofi;
                for(sofi=0;sofi<numProcesses;sofi++){
                    if(pid222==processes[sofi].pid){
                        break;
                    }
                }
                if(sofi==numProcesses){
                printf("No such process found with PID %d\n", pid222);
                }
                else{
                    if(processes[sofi].argument!=NULL){
                         pid_t pid39 = fork();

        if (pid39 == 0) {
            // Child process
            execlp(processes[sofi].command,processes[sofi].command, processes[sofi].argument, (char *)NULL);
            perror("exec");
            exit(EXIT_FAILURE);
        } else if (pid39 > 0) {
            // Parent process
            int status;
            waitpid(pid39, &status, 0);
            foreground_process_group=pid39;
            if (WIFEXITED(status)) {
                // The foreground process has completed
                addProcess(processes, pid39, processes[sofi].command, "Stoppedf", &numProcesses,"foreground",processes[sofi].argument);
                foreground_process_group=-1;
            }
        } else {
            perror("fork");
        }
                    }
                    else{
                        pid_t pid39 = fork();

        if (pid39 == 0) {
            // Child process
            execlp(processes[sofi].command,processes[sofi].command, (char *)NULL);
            perror("exec");
            exit(EXIT_FAILURE);
        } else if (pid39 > 0) {
            // Parent process
            int status;
            waitpid(pid39, &status, 0);
            foreground_process_group=pid39;
            if (WIFEXITED(status)) {
                // The foreground process has completed
                addProcess(processes, pid39, processes[sofi].command, "Stoppedf", &numProcesses,"foreground",NULL);
                foreground_process_group=-1;
            }
        } else {
            perror("fork");
        }
                    }
                }
            }
            }
            else if(strcmp(token,"proclore")==0){
                int append=0;
                 token=strtok(NULL, " \t");
                 if(token==NULL || strcmp(token,";")==0){
                     printf("pid: %d\n", getpid());
                     print_process_info("self",append,NULL);
                 }
                 else if(strcmp(token,">")==0 || strcmp(token,">>")==0){
                    append=1;
                    char*filename=strtok(NULL, " \t");
                    FILE* file;
                    if(strcmp(token,">")==0){
                     file = fopen(filename, "w");
                    }
                    else{
                        file = fopen(filename, "a");
                    }
                if (file != NULL) {
                    fprintf(file, "pid: %d\n", getpid());
                    fclose(file);
                } else {
                    fprintf(stderr, "Error opening file: %s\n", filename);
                }
                     //printf("pid: %d\n", getpid());
                     print_process_info("self",append,filename);
                 }
                 else{
                    char tokenl[MAX_INPUT_LENGTH];
                    strcpy(tokenl,token);
                    token=strtok(NULL, " \t");
                    if(token==NULL){
                     printf("pid: %s\n", tokenl);
                     print_process_info(tokenl,append,NULL);
                    }
                    else if(strcmp(token,";")==0){
                     printf("pid: %s\n", tokenl);
                     print_process_info(tokenl,append,NULL);
                    }
                    else if(strcmp(token,">")==0 || strcmp(token,">>")==0){
                      append=1;
                    char*filename=strtok(NULL, " \t");
                    FILE* file;
                    if(strcmp(token,">")==0){
                     file = fopen(filename, "w");
                    }
                    else{
                        file = fopen(filename, "a");
                    }
                if (file != NULL) {
                    fprintf(file, "pid: %s\n", tokenl);
                    fclose(file);
                } else {
                    fprintf(stderr, "Error opening file: %s\n", filename);
                }
                     print_process_info(tokenl,append,filename);
                    }
                 }
            }
            else if(strcmp(token,"activities")==0){
                int append=0;
                token=strtok(NULL, " \t");
                 if(token==NULL){
                printProcesses(processes, numProcesses,append,NULL,NULL);
                 }
                 else if(strcmp(token,";")==0){
                printProcesses(processes, numProcesses,append,NULL,NULL);
                 }
                 else if(strcmp(token,">")==0 || strcmp(token,">>")==0){
                    append=1;
                    char*filename=strtok(NULL, " \t");
                    printProcesses(processes, numProcesses,append,filename,token);
                 }
            }
            else if(strcmp(token,"neonate")==0){
                   token=strtok(NULL, " \t");
                   token=(strtok(NULL, " \t"));
                   int time_arg=atoi(token);
                   enableRawMode();
    printf("Press 'x' to exit\n");

    while (running) {

        if (kbhit()) {
            char c;
            if (read(STDIN_FILENO, &c, 1) == -1) die("read");
            if (c == 'x') {
                running = 0;
                break; // Exit the loop when 'x' is pressed
            }
        }
        pid_t pid = getMostRecentProcessID();
        printf("%d\n", pid);

        sleep(time_arg);
    }

    disableRawMode(); // Ensure raw mode is disabled before exiting
    running =1;
            }
            else if(strcmp(token,"iMan")==0){
                int append1=0;
                token=strtok(NULL, " \t");
                char*token1=strtok(NULL, " \t");
                if(token1==NULL){
                fetchManPage(token,append1,NULL,NULL);
                }
                else if(strcmp(token1,">")==0 || strcmp(token1,">>")==0){
                    append1=1;
                    char*filename=strtok(NULL, " \t");
                    fetchManPage(token,append1,filename,token1);
                }
                else{
                    fetchManPage(token,append1,NULL,NULL);
                }
            }
            else{
                char go[MAX_INPUT_LENGTH];
                strcpy(go,token);
                if(is_integer(go)==0 && strcmp(token,"vim")!=0 && strstr(input11,"echo")==NULL && strcmp(token,"gedit")!=0 && strstr(input11,"peek")==NULL && strstr(input11,"seek")==NULL){
                printf("ERROR : %s is not a valid command\n",token);
                break;
                }
            }
            //printf("hell\n");
            if(a<100 && token!=NULL){
            strcpy(store2[a],token);
            a++;
            }
            //printf("helloji\n");
            // Get the next token
            token = strtok(NULL, " \t");
            //if(token!=NULL){
                //printf("hello\n");
            //printf("%s\n",token);
            //}

        }
    }          
    }
    return 0;
}
