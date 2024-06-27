#include "headers.h"
#define MAX_PATH_LENGTH 256
#define MAX_LINE_LENGTH 256
  void print_process_info(const char *pid_str,int append,char*filename) {
    char proc_path[MAX_PATH_LENGTH];
    snprintf(proc_path, sizeof(proc_path), "/proc/%s/status", pid_str);

    FILE *proc_file = fopen(proc_path, "r");
    if (proc_file == NULL) {
        perror("Error opening process status file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char status;
    char process_group[MAX_LINE_LENGTH];
    char virtual_memory[MAX_LINE_LENGTH];
    char executable_path[MAX_PATH_LENGTH];

    while (fgets(line, sizeof(line), proc_file) != NULL) {
        if (sscanf(line, "State:\t%c", &status) == 1) {
            // Process status
if (append == 0) {
    printf("process status: %c", status);
    if (status == 'R' || status == 'S' || status == 'Z') {
        if (status == 'R' && strcmp(pid_str, "1") != 0) {
            printf("+");
        }
        printf("\n");
    } else {
        printf(" (unknown)\n");
    }
} else {
    // Redirect the process status information to the specified file
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "process status: %c", status);
        if (status == 'R' || status == 'S' || status == 'Z') {
            if (status == 'R' && strcmp(pid_str, "1") != 0) {
                fprintf(file, "+");
            }
            fprintf(file, "\n");
        } else {
            fprintf(file, " (unknown)\n");
        }
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file for append: %s\n", filename);
    }
}

        } else if (sscanf(line, "PPid:\t%s", process_group) == 1) {
            // Process group
            //printf("process Group: %s\n", process_group);
            if (append == 0) {
    printf("process Group: %s\n", process_group);
} else {
    // Redirect the process group information to the specified file
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "process Group: %s\n", process_group);
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file for append: %s\n", filename);
    }
}

        } else if (sscanf(line, "VmSize:\t%s", virtual_memory) == 1) {
            // Virtual memory
            //printf("Virtual memory: %s\n", virtual_memory);
            if (append == 0) {
    printf("Virtual memory: %s\n", virtual_memory);
} else {
    // Redirect the virtual memory information to the specified file
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "Virtual memory: %s\n", virtual_memory);
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file for append: %s\n", filename);
    }
}

        }
    }

    fclose(proc_file);

    snprintf(proc_path, sizeof(proc_path), "/proc/%s/exe", pid_str);
    ssize_t len = readlink(proc_path, executable_path, sizeof(executable_path) - 1);
    if (len != -1) {
        executable_path[len] = '\0';
        //printf("executable path: %s\n", executable_path);
        if (append == 0) {
    printf("executable path: %s\n", executable_path);
} else {
    // Redirect the executable path information to the specified file
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "executable path: %s\n", executable_path);
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file for append: %s\n", filename);
    }
}

    }
}