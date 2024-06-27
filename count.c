#include "headers.h"

int countOccurrences(const char *string, char target) {
    int count = 0;
    int length = strlen(string);

    for (int i = 0; i < length; i++) {
        if (string[i] == target) {
            count++;
        }
    }

    return count;
}