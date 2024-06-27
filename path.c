#include "headers.h"
const char *getRelativePath(const char *path, const char *initialDir) {
    static char result[PATH_MAX]; 
    if (strcmp(path, initialDir) == 0) {
        return "~";
    }

    if (strncmp(path, initialDir, strlen(initialDir)) == 0) {
        snprintf(result, sizeof(result), "~%s", path + strlen(initialDir));
        return result;
    }

    return path;
}