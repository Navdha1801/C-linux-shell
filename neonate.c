#include "headers.h"
void die(const char *s) {
    perror(s);
    exit(1);
}
void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int kbhit() {
    struct timeval tv = { 0 };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) == 1;
}
int getMostRecentProcessID() {
    // Implement logic to get the most recently created process ID here
    // You can use system calls like fork, getpid, and waitpid to get the information
    // Return the process ID of the most recently created process
    pid_t pid = fork();
    if (pid == -1) {
        die("fork");
    } else if (pid == 0) {
        sleep(1);
        _exit(0); 
    } else {
        int status;
        waitpid(pid, &status, 0);
        return pid;
    }
}
