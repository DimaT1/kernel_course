#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "fs/disk.h"
#include "fs/superblock.h"

int main()
{
	/* disk tests */
	DISK_PATH = "./images/not_exist";
	assert(disk_mount() == 2);

	DISK_PATH = "./images/too_small";
	assert(disk_mount() == 0);
	assert(disk_mount() == 1);
	assert(disk_umount() == 0);
	assert(disk_umount() == 1);
	assert(disk_umount() == 1);
	assert(disk_mount() == 0);
	assert(disk_umount() == 0);

	/* superblock tests */
	DISK_PATH = "./images/too_small";
	assert(disk_mount() == 0);
	assert(read_superblock() == 1);
	assert(disk_umount() == 0);

	DISK_PATH = "./images/superblock";
	assert(disk_mount() == 0);
	assert(read_superblock() == 0);
	BLOCK_COUNT = 42;
	INODE_COUNT = 3;
	BLOCK_SIZE = 27;
	assert(write_superblock() == 0);
	BLOCK_COUNT = 0;
	INODE_COUNT = 0;
	BLOCK_SIZE = 0;
	assert(read_superblock() == 0);
	assert(BLOCK_COUNT == 42);
	assert(INODE_COUNT == 3);
	assert(BLOCK_SIZE == 27);
	assert(disk_umount() == 0);

	puts("All tests passed");
}
