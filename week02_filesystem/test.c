#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "fs/disk.h"
#include "fs/superblock.h"
#include "fs/block.h"
#include "fs/inode.h"
#include "fs/block_table.h"

void disk_test()
{
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
}

void superblock_test()
{
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
}

void block_table_test()
{
	uint64_t block;
	uint64_t i;
	short used;

	DISK_PATH = "./images/block_table_too_small";
	assert(disk_mount() == 0);
	assert(read_superblock() == 0);
	assert(BLOCK_COUNT == 42);
	assert(INODE_COUNT == 0);
	assert(BLOCK_SIZE == 1);
	assert(block_table_init() == 3);
	assert(block_table_get_first_unused(&block) == 1);
	assert(disk_umount() == 0);

	DISK_PATH = "./images/block_table";
	assert(disk_mount() == 0);
	assert(read_superblock() == 0);
	assert(BLOCK_COUNT == 42);
	assert(INODE_COUNT == 0);
	assert(BLOCK_SIZE == 1);
	assert(block_table_init() == 0);
	assert(BLOCK_TABLE_LEN == 6);

	for (i = 0; i < 8; ++i) {
		assert(block_table_check_used(i, &used) == 0);
		assert(used == 1);
	}

	assert(block_table_get_first_unused(&block) == 0);
	assert(block == 8);

	assert(block_table_check_used(8, &used) == 0);
	assert(used == 0);

	assert(BLOCK_FREE == 4);

	assert(block_table_set_used(8, 1) == 0);
	assert(block_table_check_used(8, &used) == 0);
	assert(used == 1);
	assert(BLOCK_FREE == 3);

	assert(block_table_get_first_unused(&block) == 0);
	assert(block == 9);

	assert(block_table_set_used(9, 1) == 0);
	assert(block_table_check_used(9, &used) == 0);
	assert(used == 1);
	assert(BLOCK_FREE == 2);

	assert(block_table_get_first_unused(&block) == 0);
	assert(block == 16);

	assert(block_table_set_used(9, 0) == 0);
	assert(block_table_get_first_unused(&block) == 0);
	assert(block == 9);
	assert(BLOCK_FREE == 3);

	assert(block_table_set_used(8, 0) == 0);
	assert(block_table_get_first_unused(&block) == 0);
	assert(block == 8);
	assert(BLOCK_FREE == 4);

	assert(block_table_save() == 0);
	assert(block_table_free() == 0);
	/* TODO load saved tests */

	assert(write_superblock() == 0);
	assert(disk_umount() == 0);
}

void block_test()
{
	block_t *a;
	block_t *b;
	block_t *c;

	DISK_PATH = "./images/blocks";
	assert(disk_mount() == 0);
	assert(read_superblock() == 0);
	assert(BLOCK_COUNT == 16);
	assert(INODE_COUNT == 2);
	assert(BLOCK_FREE == 15);
	assert(INODE_FREE == 0);
	assert(BLOCK_SIZE == 10);
	assert(INODE_SIZE == 2);

	assert(block_table_init() == 0);
	assert(BLOCK_TABLE_LEN == 2);

	assert(inodes_init() == 0);
	assert(blocks_init() == 0);

	assert(BLOCKS_SHIFT == 54);

	a = block_create();
	b = block_create();
	c = block_create();

	get_free_block(a);
	get_free_block(b);
	get_free_block(c);

	block_disk_free(a);
	block_disk_free(b);
	block_disk_free(c);

	assert(block_read(b) == 0);

	assert(b->data[0] == 0xAB);
	assert(b->data[1] == 0xCD);

	b->data[1] = 0xFA;
	assert(block_write(b) == 0);
	b->data[1] = 0x00;
	assert(block_read(b) == 0);
	assert(b->data[0] == 0xAB);
	assert(b->data[1] == 0xFA);
	b->data[1] = 0xCD;
	assert(block_write(b) == 0);
	b->data[1] = 0x00;
	assert(block_read(b) == 0);
	assert(b->data[0] == 0xAB);
	assert(b->data[1] == 0xCD);

	block_free(a);
	block_free(b);
	block_free(c);

	assert(block_table_free() == 0);
	assert(write_superblock() == 0);
	assert(disk_umount() == 0);
}

void inode_test()
{

}

int main()
{
	disk_test();
	superblock_test();
	block_table_test();
	block_test();
	inode_test();
	puts("All tests passed");
}
