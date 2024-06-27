#include "seek.h"
#include "count.h"
#include "globals.h"
#include "headers.h"
#include "man.h"
void exe(char*str,char**store1,char**store,char*initialDir,char**store3){
char *str1111 = malloc(strlen(str) + 1); // +1 for the null terminator
char *str2 = malloc(strlen(str) + 1);

    strcpy(str1111,str);
    strcpy(str2,str);    
  char*hello=strtok(str2, " \t");
  if(count>MAX_COMMANDS && value%MAX_COMMANDS==0){
                if(strcmp(hello,"pastevents")!=0 &&strcmp(hello,";")!=0 && strcmp(str1111,store1[14])!=0){
                    track=value%MAX_COMMANDS;
                strcpy(store1[track],str1111);
                count++;
                value++;
            }
            }
           
            else if(count<=MAX_COMMANDS && strcmp(hello,";")!=0 && value%MAX_COMMANDS==0){
                if(strcmp(hello,"pastevents")!=0){
                    track=value%MAX_COMMANDS;
                strcpy(store1[track],str1111);
                //printf("hell1\n");
                count++; 
                value++;
            }
            }
            
            else{ 
            if(strcmp(hello,"pastevents")!=0 && strcmp(hello,";")!=0 && strcmp(str1111,store1[(value%MAX_COMMANDS)-1])!=0){
                track=value%MAX_COMMANDS;
                strcpy(store1[track],str1111);
                //printf("hello\n");
                //printf("%s\n",store1[track]);
                count++;
                value++;
            }
            }
            
            if (strcmp(hello, "warp") == 0) {
                // Execute the "warp" command with arguments
                execution_time=0;
                hello = strtok(NULL, " \t");
               // printf("%s\n",token);
                if (hello == NULL || strcmp(hello,";")==0) {
                    chdir(initialDir);
                    strcpy(store[g],initialDir);
                    g++;
                    printf("%s\n", initialDir);
                }
                
                while (hello != NULL) {
                    //printf("%s\n",token);
                    if(strcmp(hello,";")==0 || strcmp(hello,">")==0 || strcmp(hello,">>")==0){
                        break;
                    }
                    char*copydir=executeWarp(hello, initialDir, store);
                    //printf("%s\n",copydir);
                    //token = strtok(NULL, " \t");
                    if(copydir==NULL){
                        //printf("hell\n");
                        hello=NULL;
                    }
                    else{
                    strcpy(hello,copydir);
                    }
                    
                }
            }
            else if(strcmp(hello,"peek")==0){
                 hello = strtok(NULL, " \t");
                bool allFlag = false;
                bool longFlag = false;

                // Check for flags
                while (hello != NULL && hello[0] == '-' && hello[1]!='\0') {
                    for (int i = 1; hello[i] != '\0'; i++) {
                        if (hello[i] == 'a') {
                            allFlag = true;
                        } else if (hello[i] == 'l') {
                            longFlag = true;
                        }
                    }
                    hello = strtok(NULL, " \t");
                }
                 char copy[PATH_MAX];
                if (hello == NULL) {
                    hello = ".";
                    
                }
                else if(strcmp(hello,"~")==0){
                    strcpy(hello,initialDir);
                  
                }
                else if(hello[0]=='~'){
                    strcpy(copy,initialDir);
                    strcat(copy,hello+1);
                    strcpy(hello,copy);
                    
                }
                else if(strcmp(hello,"..")==0){
                    if(getcwd(copy,sizeof(copy))!=NULL){
                        char*last= strrchr(copy, '/');
                        copy[strlen(copy)-strlen(last)]='\0';
                        strcpy(hello,copy);
                       
                    }
                }
                else if(strcmp(hello,"-")==0){
                    strcpy(hello,store[g-2]);
                    
                }
                else if(hello[0]=='/'){
                
                }
                else{
                    char*di;
                    if(getcwd(di,sizeof(di))!=NULL){
                    strcpy(copy,di);
                    strcat(copy,"/");
                    strcat(copy,hello);
                    strcpy(hello,copy);
                    }
                }
                 listFiles(hello, allFlag, longFlag);
            }
           
              else if(strcmp(hello,"seek")==0){
                int append=0;
                execution_time=0;
                hello=strtok(NULL, " \t");
                int file=0;
                int dir=0;
                int eflag=0;
                while(hello!=NULL && hello[0]=='-'){
                     if(hello[1]=='f'){
                        file=1;
                     }
                     else if(hello[1]=='d'){
                        dir=1;
                     }
                     else if(hello[1]=='e'){
                           eflag=1;
                     }
                     hello=strtok(NULL, " \t");
                }
                char search[MAX_INPUT_LENGTH]; 
                strcpy(search,hello);
                char navdha[MAX_INPUT_LENGTH];
                char* token11;
                hello=strtok(NULL, " \t");
                if(hello==NULL){
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
                else if(strcmp(hello,">")==0 || strcmp(hello,">>")==0){
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
                strcpy(token11,hello);
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
                 if(hello!=NULL && strcmp(hello,">")!=0 && strcmp(hello,">>")!=0){
                 hello=strtok(NULL, " \t");
                 }
                 strcpy(directory,token11);
                 if(hello==NULL){
                seekCommand(search, directory, file,dir,eflag,append,store3,NULL,NULL );
                 }
                else if( strcmp(hello,">")==0 || strcmp(hello,">>")==0){
                           append=1;
                           char*filename=strtok(NULL, " \t");
                           seekCommand(search, directory, file,dir,eflag,append,store3,filename,hello );
                 }
                 else{
                seekCommand(search, directory, file,dir,eflag,append,store3,NULL,NULL );
                 }
                maintain=0;
            }
            else if(strcmp(hello,"echo")==0 ){
                char C;
                char D;
                char token311[MAX_INPUT_LENGTH];
                const char*token312;
                char tokennav[MAX_INPUT_LENGTH];
                strcpy(tokennav,str);
                if(countOccurrences(str,';')==0){
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
            addProcess(processes, pid2, hello, "Stoppedf", &numProcesses,"foreground",token311);
            foreground_process_group=-1;
        }
      else  if (WIFSTOPPED(status)) {
            addProcess(processes, pid2, hello, "Stopped", &numProcesses,"background",token311);
            foreground_process_group=-1;
        }
        else if (WIFSIGNALED(status)) {
            addProcess(processes, pid2, hello, "Stoppedf", &numProcesses,"foreground",token311);
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
            addProcess(processes, pid2, hello, "Stoppedf", &numProcesses,"foreground",token312);
            foreground_process_group=-1;
        }
        else if (WIFSTOPPED(status)) {
            // The foreground process has completed
            addProcess(processes, pid2, hello, "Stopped", &numProcesses,"background",token312);
            foreground_process_group=-1;
        }
        else if (WIFSIGNALED(status)) {
            // The foreground process has completed
            addProcess(processes, pid2, hello, "Stoppedf", &numProcesses,"foreground",token312);
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
            
               else if(strcmp(hello,"pwd")==0 || strcmp(hello,"gedit")==0 || strcmp(hello,"vim")==0){
                     char*tokenc=strtok(NULL, " \t");
                     if(tokenc!=NULL && strcmp(tokenc,"&")==0){
                      
            pid_t pid13 = fork();
    if (pid13 == 0) {
    execlp(hello, hello, (char *)NULL);
    
    perror("execlp");
    exit(1);
       
    } else if (pid13 > 0) {
        
        if (num_background < MAX_BACKGROUND_PROCESSES) {
            addProcess(processes, pid13, hello, "Running", &numProcesses,"background",NULL);
            
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
                     execlp(hello,hello,(char*)NULL );
                
                perror("exec");
                exit(EXIT_FAILURE);
            } else if (pid3 > 0) {
                int status;
                foreground_process_group=pid3;
                waitpid(pid3, &status,WUNTRACED );
                if (WIFEXITED(status)) {
            addProcess(processes, pid3, hello, "Stoppedf", &numProcesses,"foreground",NULL);
            foreground_process_group=-1;
        }
        else if(WIFSTOPPED(status)){
            addProcess(processes, pid3, hello, "Stopped", &numProcesses,"background",NULL);
            foreground_process_group=-1;
        }
        else if (WIFSIGNALED(status)) {
        //printf("Process terminated by signal: %d\n", WTERMSIG(status));
        addProcess(processes, pid3, hello, "Stoppedf", &numProcesses, "foreground", NULL);
        foreground_process_group = -1;
    }
            } else {
                perror("fork");
            }
                     }
            }
            
            else if(strcmp(hello,"sleep")==0){
                strcpy(bansal,hello);
                hello=strtok(NULL, " \t");
               char* tokend=strtok(NULL, " \t");
               //printf("%s\n",tokend);
           if(tokend!=NULL && strcmp(tokend,"&")==0){
            //printf("nav\n");
            pid_t pid13 = fork();
    if (pid13 == 0) {
    execlp("sleep", "sleep", hello, (char *)NULL);  
    
    perror("execlp"); 
    exit(1);
       
    } else if (pid13 > 0) {
        
        if (num_background < MAX_BACKGROUND_PROCESSES) {

            addProcess(processes, pid13, "sleep", "Running", &numProcesses,"background",hello);
            
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
            execlp(bansal, bansal,hello, (char *)NULL);
            perror("exec");
            exit(EXIT_FAILURE);
        } else if (pid1 > 0) {
            int status;
            foreground_process_group = pid1;
            waitpid(pid1, &status, WUNTRACED);
            gettimeofday(&end_time, NULL);
            execution_time = (int)(end_time.tv_sec - start_time.tv_sec);
            if (WIFEXITED(status)) {
            addProcess(processes, pid1, "sleep", "Stoppedf", &numProcesses,"foreground",hello);
            //printf("g\n");
             foreground_process_group = -1;
        }
        else if (WIFSTOPPED(status)) {
            addProcess(processes, pid1, "sleep", "Stopped", &numProcesses,"background",hello);
            //printf("g\n");
             foreground_process_group = -1;
        }
         else if (WIFSIGNALED(status)) {
            addProcess(processes, pid1, "sleep", "Stoppedf", &numProcesses,"foreground",hello);
            //printf("g\n");
             foreground_process_group = -1;
        }  
        }
        
        else {
            perror("fork");
        }

            }
            }
             else if(strcmp(hello,"activities")==0){
                int append=0;
                hello=strtok(NULL, " \t");
                 if(hello==NULL){
                printProcesses(processes, numProcesses,append,NULL,NULL);
                 }
                 else if(strcmp(hello,";")==0){
                printProcesses(processes, numProcesses,append,NULL,NULL);
                 }
                 else if(strcmp(hello,">")==0 || strcmp(hello,">>")==0){
                    append=1;
                    char*filename=strtok(NULL, " \t");
                    printProcesses(processes, numProcesses,append,filename,hello);
                 }
            }
            else if(strcmp(hello,"iMan")==0){
                int append1=0;
                hello=strtok(NULL, " \t");
                char*token1=strtok(NULL, " \t");
                if(token1==NULL){
                fetchManPage(hello,append1,NULL,NULL);
                }
                else if(strcmp(token1,">")==0 || strcmp(token1,">>")==0){
                    append1=1;
                    char*filename=strtok(NULL, " \t");
                    fetchManPage(hello,append1,filename,token1);
                }
                else{
                    fetchManPage(hello,append1,NULL,NULL);
                }
            }
             else if(strcmp(hello,"neonate")==0){
                   hello=strtok(NULL, " \t");
                   hello=(strtok(NULL, " \t"));
                   int time_arg=atoi(hello);
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
            else if(strcmp(hello,"proclore")==0){
                int append=0;
                 hello=strtok(NULL, " \t");
                 if(hello==NULL || strcmp(hello,";")==0){
                     printf("pid: %d\n", getpid());
                     print_process_info("self",append,NULL);
                 }
                 else if(strcmp(hello,">")==0 || strcmp(hello,">>")==0){
                    append=1;
                    char*filename=strtok(NULL, " \t");
                    FILE* file;
                    if(strcmp(hello,">")==0){
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
                    strcpy(tokenl,hello);
                    hello=strtok(NULL, " \t");
                    if(hello==NULL){
                     printf("pid: %s\n", tokenl);
                     print_process_info(tokenl,append,NULL);
                    }
                    else if(strcmp(hello,";")==0){
                     printf("pid: %s\n", tokenl);
                     print_process_info(tokenl,append,NULL);
                    }
                    else if(strcmp(hello,">")==0 || strcmp(hello,">>")==0){
                      append=1;
                    char*filename=strtok(NULL, " \t");
                    FILE* file;
                    if(strcmp(hello,">")==0){
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
            else if(strcmp(hello,"wc")==0){
                char filename[MAX_INPUT_LENGTH];
                hello=strtok(NULL, " \t");
                //printf("%s\n",token);
                if(strcmp(hello,"<")==0){
                    hello=strtok(NULL, " \t");
                     strcpy(filename,hello);
                }
                else{
                    //printf("hel\n");
                    strcpy(filename,hello);
                     //printf("hel\n");
                }
                //printf("%s\n",filename);
                hello=strtok(NULL, " \t");
                if(hello==NULL){
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
                else if(strcmp(hello,">")==0 || strcmp(hello,">>")==0){
                 char*filename1=strtok(NULL, " \t");
                 if (filename1 != NULL) {
                        int mode = strcmp(hello, ">") == 0 ? O_WRONLY | O_CREAT | O_TRUNC : O_WRONLY | O_CREAT | O_APPEND;

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
                else if(strcmp(hello,"cat")==0){
                 hello=strtok(NULL, " \t");
                 if(strcmp(hello,"<")==0){
                    hello=strtok(NULL, " \t");
                 }
                 char*tokens=strtok(NULL, " \t");
                  if (tokens == NULL) {
        char filePath[PATH_MAX]; // Define a buffer for the file path
        snprintf(filePath, sizeof(filePath), "%s/%s", getcwd(NULL, 0), hello);
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
                addProcess(processes, pid39, "cat", "Stoppedf", &numProcesses,"foreground",hello);
                foreground_process_group=-1;
            }
           else if (WIFSTOPPED(status)) {
                                 addProcess(processes, pid39, "cat", "Stopped", &numProcesses,"background",hello);
                        }
           else if (WIFSIGNALED(status)) {
                                 addProcess(processes, pid39, "cat", "Stoppedf", &numProcesses,"foreground",hello);
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
                                execlp("cat", "cat",hello, NULL);  
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
                                 addProcess(processes, pid, "cat", "Stoppedf", &numProcesses,"foreground",hello);
                                //printf("Command executed successfully.\n");
                        }
                        else if (WIFSTOPPED(status)) {
                                 addProcess(processes, pid, "cat", "Stopped", &numProcesses,"background",hello);
                                //printf("Command executed successfully.\n");
                        }
                        else if (WIFSIGNALED(status)) {
                                 addProcess(processes, pid, "cat", "Stoppedf", &numProcesses,"foreground",hello);
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

            }