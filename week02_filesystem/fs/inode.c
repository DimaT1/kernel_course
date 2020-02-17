#include "inode.h"

static inode_t *inodes;

short inodes_init()
{
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
