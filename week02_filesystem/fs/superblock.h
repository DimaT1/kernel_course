#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include <stdint.h>
#include <fcntl.h>

#include "disk.h"

#define SUPERBLOCK_ATOM 8
#define SUPERBLOCK_PARAMETERS 7
#define SUPERBLOCK_SIZE (SUPERBLOCK_ATOM * SUPERBLOCK_PARAMETERS)

extern uint64_t BLOCK_COUNT;
extern uint64_t INODE_COUNT;
extern uint64_t BLOCK_FREE;
extern uint64_t INODE_FREE;
extern uint64_t BLOCK_SIZE;
extern uint64_t INODE_SIZE;
extern uint64_t MAX_NAME_LEN;
// TODO try to add union to simplify read/write

short read_superblock();
short write_superblock();

#endif
