#include <stdio.h>
#include <stdlib.h>

#include "superblock.h"
#include "disk.h"


uint64_t BLOCK_COUNT;
uint64_t INODE_COUNT;
uint64_t BLOCK_FREE;
uint64_t INODE_FREE;
uint64_t BLOCK_SIZE;
uint64_t INODE_SIZE;
uint64_t MAX_NAME_LEN;

short read_superblock()
{
	if (fseek(DISK_FILE, 0, SEEK_SET) != 0)
		return 1;

	uint64_t superblock[SUPERBLOCK_PARAMETERS];

	if (fread(superblock, SUPERBLOCK_ATOM, SUPERBLOCK_PARAMETERS,
		  DISK_FILE) != SUPERBLOCK_PARAMETERS)
		return 2;

	BLOCK_COUNT = superblock[0];
	INODE_COUNT = superblock[1];
	BLOCK_FREE = superblock[2];
	INODE_FREE = superblock[3];
	BLOCK_SIZE = superblock[4];
	INODE_SIZE = superblock[5];
	MAX_NAME_LEN = superblock[6];

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
	superblock[6] = MAX_NAME_LEN;

	if (fwrite(superblock, SUPERBLOCK_ATOM, SUPERBLOCK_PARAMETERS,
		   DISK_FILE) != SUPERBLOCK_PARAMETERS)
		return 2;

	return 0;
}
