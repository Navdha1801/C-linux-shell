#ifndef GLOBALS_H
#define GLOBALS_H
#define MAX_INPUT_LENGTH 100
#define MAX_BACKGROUND_PROCESSES 10
#include<sys/types.h>
struct ProcessInfo {
    pid_t pid;
    char command[100];
    char state[10];
    char type[20];
    char argument[10];
};
extern int g; // Declare the global variable
extern int count;
extern int value;
extern int track;
extern int execution_time;
extern char bansal[MAX_INPUT_LENGTH];
extern int num_background;
extern struct ProcessInfo processes[MAX_INPUT_LENGTH]; // Array to store process information
extern int numProcesses; // Number of processes in the array
extern int maintain;
extern pid_t background_pids[MAX_BACKGROUND_PROCESSES]; // Array to store background process IDs
extern  int num_background ; // Number of background processes
extern pid_t foreground_process_group; // Initialize with an invalid process group
extern struct termios orig_termios;
extern int running; // Flag to control the loop
#endif // GLOBALS_H
