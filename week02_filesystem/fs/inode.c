#include <memory.h>
#include <stdlib.h>


#include "inode.h"
#include "superblock.h"


uint64_t INODES_SIZE;

inode_t *inodes;

short inodes_init()
{
	INODES_SIZE = INODE_COUNT * INODE_SIZE;
	return 0;
}

short inodes_init();
short inodes_save();
short inodes_free();

short inode_new()
{
	return -1;
}

short inode_mkdir(inode_t* parent, char* name, inode_t* res)
{
	if (parent == NULL)
		return 1;

	inode_t *buf = parent;
	while (buf->is_link) {
		buf = buf->original;
		// TODO: check for cycle
	}

	if (!buf->is_dir)
		return 2;

	res = (inode_t *) malloc(sizeof(inode_t));
	res->is_dir = 1;
	res->is_link = 0;
	res->name = name;
	res->parent_node = parent;
	res->next = NULL;
	res->child_nodes = NULL;

	res->next = buf->child_nodes;
	buf->child_nodes = (void*)res;

	return 0;
}

short inode_mklink(inode_t *original, inode_t *parent, char *name, inode_t *res)
{
	if (parent == NULL)
		return 1;

	inode_t *buf = parent;
	while (buf->is_link) {
		buf = buf->original;
		// TODO: check for cycle
	}

	if (!buf->is_dir)
		return 2;

	res = (inode_t *) malloc(sizeof(inode_t));
	res->is_dir = 0;
	res->is_link = 1;
	res->original = original;
	original->references += 1;
	res->name = name;
	res->parent_node = parent;
	res->next = NULL;
	res->child_nodes = NULL;

	res->next = buf->child_nodes;
	buf->child_nodes = (void*)res;

	return 0;
}


short inode_touch(inode_t* parent, char* name, inode_t* res)
{
	if (parent == NULL)
		return 1;

	inode_t *buf = parent;
	while (buf->is_link) {
		buf = buf->original;
		// TODO: check for cycle
	}

	if (!buf->is_dir)
		return 2;

	res = (inode_t *) malloc(sizeof(inode_t));
	res->is_dir = 0;
	res->is_link = 0;

	res->next = buf->child_nodes;
	buf->child_nodes = (void*)res;
	res->name = name;
	res->parent_node = parent;
	res->child_nodes = NULL;

	return 0;
}


short inode_rm(inode_t* node)
{
	if (node == NULL)
		return 1;

	if (node->is_link) {
		((inode_t*)(node->original))->references -= 1;
		if (((inode_t*)(node->original))->references == 0) {
			inode_rm(node->original);
		}
		free(node->name);
		return 0;
	}

	if (node->is_dir) {
		inode_t *buf = (inode_t*) node->child_nodes;
		while (buf) {
			inode_t *kek = buf->next;
			inode_rm(buf);
			buf = kek;
		}
		free(node->name);
		return 0;
	}

	inode_t *buf = ((inode_t*) node->parent_node)->child_nodes;
	while (buf->next != node) {
		buf = buf->next;
	}
	buf->next = node->next;
	free(node->name);
	free(node->data);
	return 0;
}


short inode_free()
{
	return -1;
}


short inode_get_size(uint64_t *size)
{
	return -1;
}

