#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include <stdint.h>
#include <fcntl.h>

#include "disk.h"

uint64_t BLOCK_COUNT;
uint64_t INODE_COUNT;
uint64_t BLOCK_FREE;
uint64_t INODE_FREE;
uint64_t BLOCK_SIZE;
uint64_t INODE_SIZE;

short read_superblock();
short write_superblock();

#endif
