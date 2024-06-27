#ifndef HEADERS_H_
#define HEADERS_H_
#define MAX_INPUT_LENGTH 100
#define MAX_COMMANDS 15
#define MAX_BACKGROUND_PROCESSES 10
#define MAX_PATH_LENGTH 256
#define MAX_LINE_LENGTH 256
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <grp.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include<netdb.h>
#include<arpa/inet.h>
#include <curl/curl.h>
#include "globals.h"
#include "path.h"
#include "warp.h"
#include "peek.h"
#include "count.h"
#include "checkint.h"
#include "seekfile.h"
#include "seek.h"
#include "proclore.h"
#include "past.h"
#include "activities.h"
#include "neonate.h"
#include "man.h"
#include "signal.h"
#endif