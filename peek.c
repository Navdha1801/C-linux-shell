#include "headers.h"

void listFiles(const char *path, bool allFlag, bool longFlag) {
    DIR *dir;
    struct dirent **entryList;
    int numEntries;
    
    numEntries = scandir(path, &entryList, NULL, alphasort);
    if (numEntries == -1) {
        perror("scandir");
        return;
    }
    
    for (int i = 0; i < numEntries; i++) {
        struct dirent *entry = entryList[i];
        char fullPath[PATH_MAX];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        if (!allFlag && entry->d_name[0] == '.') {
            continue; // Skip hidden files and directories if -a flag not present
        }

        struct stat fileStat;
        if (lstat(fullPath, &fileStat) == -1) {
            perror("lstat");
            continue;
        }

        if (longFlag) {
            printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf(" %ld ", (long)fileStat.st_nlink);
            
            struct passwd *pw = getpwuid(fileStat.st_uid);
            printf("%s ", (pw) ? pw->pw_name : "");

            struct group *grp = getgrgid(fileStat.st_gid);
            printf("%s ", (grp) ? grp->gr_name : "");

            printf("%lld ", (long long)fileStat.st_size);
            
            struct tm *timeinfo;
            timeinfo = localtime(&fileStat.st_mtime);
            printf("%02d-%02d-%04d %02d:%02d ", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
                                                timeinfo->tm_hour, timeinfo->tm_min);
        }

        if (S_ISDIR(fileStat.st_mode)) {
            if (longFlag) {
                printf("d");
            }
            printf("\033[1;34m%s\033[0m\n", entry->d_name); // Blue color for directories
            //printf("hello\n");
        } else if (fileStat.st_mode & S_IXUSR) {
            if (longFlag) {
                printf("x");
            }
            printf("\033[1;32m%s\033[0m\n", entry->d_name); // Green color for executables
        } else {
            printf("\033[0m%s\033[0m\n", entry->d_name);
        }
        //printf("nav\n");
 free(entry);
    }
    //printf("she\n");
    closedir(dir);
    //printf("he\n");
}