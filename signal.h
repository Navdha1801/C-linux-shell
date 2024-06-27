#ifndef __SIGNAL_H
#define __SIGNAL_H
#include <sys/types.h>
void sigint_handler(int signum);
void sigtstp_handler(int signum);
int process_exists(pid_t pid);
#endif