#ifndef INODE_H
#define INODE_H

#include <stdint.h>
#include "block.h"

extern uint64_t INODES_SIZE;

// typedef struct {
// 	uint64_t id;
// 	uint64_t references;
// 	uint8_t is_used;
// 	uint8_t is_link;
// 	uint8_t is_dir;
// 	uint64_t parent_node;
// 	uint64_t reference_node;
// 	char name[8]; // TODO move to superblock
// 	uint64_t *child_nodes;
// 	uint64_t *blocks;
// } inode_t;

typedef struct {
	char *name;
	uint64_t id;
	uint64_t references;
	uint8_t is_link;
	uint8_t is_dir;
	void *parent_node;
	void *child_nodes;
	uint64_t size;
	uint8_t *data;
	void *next;
	void *prev;
	void *original;
} inode_t;

short inodes_init();
short inodes_save();
short inodes_free();

short inode_new();
short inode_mkdir(inode_t *parent, char *name, inode_t *res);
short inode_mklink(inode_t *original, inode_t *parent, char* name, inode_t *res);
short inode_touch(inode_t *parent, char *name, inode_t *res);
short inode_rm(inode_t *node);
short inode_free();
short inode_get_size(uint64_t *size);

#endif
