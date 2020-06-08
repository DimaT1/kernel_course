#ifndef DISK_H
#define DISK_H

#include <stdio.h>

extern char *DISK_PATH;
extern FILE *DISK_FILE;

short disk_init();
short disk_mount();
short disk_umount();

#endif
