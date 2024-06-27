#ifndef __ACTIVITIES_H
#define __ACTIVITIES_H
#include<sys/types.h>

void addProcess(struct ProcessInfo processes[], pid_t pid, const char* command, const char* state, int* numProcesses,const char*type,const char*argument);
void updateProcessState(struct ProcessInfo processes[], pid_t pid, const char* newState, int numProcesses);
int compareProcesses(const void* a, const void* b);
void printProcesses(const struct ProcessInfo processes[], int numProcesses,int append,char*filename,char*token);
void removeProcess(struct ProcessInfo processes[], int *numProcesses, int index);
void update_process_state(pid_t pid, const char* new_state);
void update_process_state1(pid_t pid, const char* new_type);

#endif