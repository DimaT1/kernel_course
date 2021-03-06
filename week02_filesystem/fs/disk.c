#include <fcntl.h>

#include "disk.h"


char *DISK_PATH;
FILE *DISK_FILE;

short disk_init()
{
	DISK_PATH = NULL;
	DISK_FILE = NULL;
	return 0;
}

short disk_mount()
{
	if (DISK_FILE != NULL)
		return 1;

	DISK_FILE = fopen(DISK_PATH, "r+");
	return DISK_FILE == NULL ? 2 : 0;
}

short disk_umount()
{
	if (DISK_FILE == NULL)
		return 1;

	fclose(DISK_FILE);
	// TODO check for return value of fclose
	DISK_FILE = NULL;

	return 0;
}
