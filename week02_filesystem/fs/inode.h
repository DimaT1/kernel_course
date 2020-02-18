#ifndef INODE_H
#define INODE_H

#include <stdint.h>
#include "block.h"

uint64_t INODES_SIZE;

typedef struct {
	uint64_t id;
	uint64_t references;
	uint8_t is_used;
	uint8_t is_link;
	uint8_t is_dir;
	uint64_t parent_node;
	uint64_t reference_node;
	char name[256];
	uint64_t *child_nodes;
	uint64_t *blocks;
} inode_t;

short inodes_init();
short inodes_save();
short inodes_free();

short inode_new();
short inode_mkdir();
short inode_mklink();
short inode_touch();
short inode_rm();
short inode_get_text();
short inode_set_text();
short inode_free();
short inode_get_size();

#endif
