#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include <stdint.h>
#include <fcntl.h>

#include "disk.h"

#define SUPERBLOCK_ATOM 8
#define SUPERBLOCK_PARAMETERS 6
#define SUPERBLOCK_SIZE (SUPERBLOCK_ATOM * SUPERBLOCK_PARAMETERS)

uint64_t BLOCK_COUNT;
uint64_t INODE_COUNT;
uint64_t BLOCK_FREE;
uint64_t INODE_FREE;
uint64_t BLOCK_SIZE;
uint64_t INODE_SIZE;
// TODO try to add union to simplify read/write

short read_superblock();
short write_superblock();

#endif
