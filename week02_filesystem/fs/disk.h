#ifndef DISK_H
#define DISK_H

#include <stdio.h>

char *DISK_PATH;
FILE *DISK_FILE;

void disk_init();
short disk_mount();
short disk_umount();

#endif
