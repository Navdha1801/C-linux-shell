#include "headers.h"
#include "globals.h"

// Function to add a process to the list
void addProcess(struct ProcessInfo processes[], pid_t pid, const char* command, const char* state, int* numProcesses,const char*type,const char*argument) {
    struct ProcessInfo* process = &processes[*numProcesses];
    process->pid = pid;
    strncpy(process->command, command, sizeof(process->command));
    strncpy(process->state, state, sizeof(process->state));
    strncpy(process->type, type, sizeof(process->type));
    if(argument!=NULL){
    strncpy(process->argument,argument, sizeof(process->argument));
    }
    (*numProcesses)++;
}

void updateProcessState(struct ProcessInfo processes[], pid_t pid, const char* newState, int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].pid == pid) {
            strncpy(processes[i].state, newState, sizeof(processes[i].state));
            processes[i].state[sizeof(processes[i].state) - 1] = '\0'; // Ensure null-termination
            break; // Process found and updated, exit the loop
        }
    }
}

int compareProcesses(const void* a, const void* b) {
    return ((struct ProcessInfo*)a)->pid - ((struct ProcessInfo*)b)->pid;
}

// Function to print processes in order of pid
void printProcesses(const struct ProcessInfo processes[], int numProcesses,int append,char*filename,char*token) {
    // Create a copy of the processes array to sort
    struct ProcessInfo* sortedProcesses = malloc(numProcesses * sizeof(struct ProcessInfo));
    if (sortedProcesses == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    memcpy(sortedProcesses, processes, numProcesses * sizeof(struct ProcessInfo));

    // Sort the array based on pid
    qsort(sortedProcesses, numProcesses, sizeof(struct ProcessInfo), compareProcesses);

    if (append == 0) {
    // Print the sorted processes to the terminal
    for (int i = 0; i < numProcesses; i++) {
        printf("[%d] : %s %s(%s) - %s\n", sortedProcesses[i].pid, sortedProcesses[i].command, sortedProcesses[i].argument, sortedProcesses[i].type, sortedProcesses[i].state);
    }
} else {
    // Redirect the sorted processes information to the specified file
    FILE* file;
    if(strcmp(token,">>")==0){
     file = fopen(filename, "a");
    }
    else{
        file = fopen(filename, "w");
    }
    if (file != NULL) {
        for (int i = 0; i < numProcesses; i++) {
            fprintf(file, "[%d] : %s %s(%s) - %s\n", sortedProcesses[i].pid, sortedProcesses[i].command, sortedProcesses[i].argument, sortedProcesses[i].type, sortedProcesses[i].state);
        }
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file for append: %s\n", filename);
    }
}

    // Free the memory allocated for the sorted array
    free(sortedProcesses);
}
void removeProcess(struct ProcessInfo processes[], int *numProcesses, int index) {
    if (index < 0 || index >= *numProcesses) {
        return;
    }

    for (int i = index; i < (*numProcesses - 1); i++) {
        processes[i] = processes[i + 1];
    }

    (*numProcesses)--;
}
void update_process_state(pid_t pid, const char* new_state) {
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].pid == pid) {
            strncpy(processes[i].state, new_state, sizeof(processes[i].state));
            break;
        }
    }
}
void update_process_state1(pid_t pid, const char* new_type) {
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].pid == pid) {
            strncpy(processes[i].type, new_type, sizeof(processes[i].type));
            break;
        }
    }
}
