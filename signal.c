#include "headers.h"

void sigint_handler(int signum) {
    if (foreground_process_group != -1) {
        // Forward SIGINT to the foreground process group
        kill(foreground_process_group, SIGINT);
    }
    else {
        printf("No foreground process to interrupt.\n");
    }
}
void sigtstp_handler(int signum) {
    if (foreground_process_group != -1) {
        // Forward SIGTSTP to the foreground process group
        kill(-foreground_process_group, SIGTSTP);
        // Change the state of the process to "Stopped"
        update_process_state(foreground_process_group,"Stopped");
        // Mark the process as a background process
        update_process_state1(foreground_process_group,"background");
        foreground_process_group = -1; // No foreground process running
    } else {
        printf("No foreground process to stop.\n");
    }
}
// Function to check if a process with the given PID exists
int process_exists(pid_t pid) {
    return kill(pid, 0) == 0;
}