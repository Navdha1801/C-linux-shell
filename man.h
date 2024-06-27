#ifndef __NEONATE_H
#define __NEONATE_H
#include<sys/types.h>
void parsehtml(const char *str, size_t l);
size_t write_callback(char *ptr, size_t size, size_t member, void *userdata);
void fetchManPage(const char *command, int append, char *filename, char *token);
#endif