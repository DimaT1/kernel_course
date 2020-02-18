#ifndef BLOCK_H
#define BLOCK_H

#include <stddef.h>
#include <stdint.h>

#define BLOCK_LEN_SIZE 8
#define BLOCK_POS_SIZE 8

uint64_t BLOCK_DATA_SIZE;
uint64_t BLOCK_DATA_LEN;
uint64_t BLOCKS_SHIFT;

typedef struct {
	uint64_t len;
	uint64_t pos;
	uint8_t *data;
} block_t;

short blocks_init();

block_t *block_create();

// Allocates first available block at disk
short get_free_block(block_t *);

// Sets data to RAM buffer
short block_set_buf_data(block_t *, uint8_t *, size_t);

// Writes data to disk
short block_write(block_t *);
// Reads data from disk
short block_read(block_t *);
// Frees RAM buffer
short block_free(block_t *);
// Frees data at disk
short block_disk_free(block_t *);

#endif
