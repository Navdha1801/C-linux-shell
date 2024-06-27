#include "headers.h"

 int is_integer(const char *str) {
    char *endptr;
    long value = strtol(str, &endptr, 10);

    // Check if conversion was successful and if there are no trailing characters
    return *endptr == '\0' && value != 0;
}
