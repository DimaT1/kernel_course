#include "inode.h"
#include "superblock.h"

inode_t *inodes;

short inodes_init()
{
	INODES_SIZE = INODE_COUNT * INODE_SIZE;
	return 0;
}

short inodes_save();
short inodes_free();

short inode_new();
short inode_mkdir();
short inode_mklink()
{
	/* TODO */
	return 1;
}
short inode_touch();
short inode_rm();
short inode_get_text();
short inode_set_text();
short inode_free();
short inode_get_size();
