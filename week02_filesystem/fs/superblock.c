#include <stdio.h>
#include <stdlib.h>

#include "superblock.h"
#include "disk.h"

short read_superblock()
{
	if (fseek(DISK_FILE, 0, SEEK_SET) != 0)
		return 1;

	uint64_t superblock[SUPERBLOCK_PARAMETERS];

	if (fread(superblock, SUPERBLOCK_ATOM, SUPERBLOCK_PARAMETERS,
		  DISK_FILE) != SUPERBLOCK_PARAMETERS)
		return 1;

	BLOCK_COUNT = superblock[0];
	INODE_COUNT = superblock[1];
	BLOCK_FREE = superblock[2];
	INODE_FREE = superblock[3];
	BLOCK_SIZE = superblock[4];
	INODE_SIZE = superblock[5];

	return 0;
}

short write_superblock()
{
	if (fseek(DISK_FILE, 0, SEEK_SET) != 0)
		return 1;

	uint64_t superblock[SUPERBLOCK_PARAMETERS];

	superblock[0] = BLOCK_COUNT;
	superblock[1] = INODE_COUNT;
	superblock[2] = BLOCK_FREE;
	superblock[3] = INODE_FREE;
	superblock[4] = BLOCK_SIZE;
	superblock[5] = INODE_SIZE;

	if (fwrite(superblock, SUPERBLOCK_ATOM, SUPERBLOCK_PARAMETERS,
		   DISK_FILE) != SUPERBLOCK_PARAMETERS)
		return 1;

	return 0;
}
