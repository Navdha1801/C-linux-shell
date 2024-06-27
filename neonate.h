#ifndef __NEONATE_H
#define __NEONATE_H
void die(const char *s);
void disableRawMode();
void enableRawMode();
int kbhit();
int getMostRecentProcessID();
#endif