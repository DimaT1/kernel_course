#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "block.h"
#include "superblock.h"
#include "block_table.h"
#include "disk.h"
#include "inode.h"


uint64_t BLOCK_DATA_SIZE;
uint64_t BLOCK_DATA_LEN;
uint64_t BLOCKS_SHIFT;

short blocks_init()
{
	BLOCK_DATA_SIZE = BLOCK_SIZE - 8;
	BLOCK_DATA_LEN = BLOCK_DATA_SIZE;
	BLOCKS_SHIFT = SUPERBLOCK_SIZE + BLOCK_TABLE_SIZE + INODES_SIZE;
	return 0;
}

block_t *block_create()
{
	block_t *s = (block_t *)malloc(sizeof(block_t));
	uint8_t *data = (uint8_t *)malloc(BLOCK_DATA_SIZE);
	s->data = data;
	s->pos = 0;
	s->len = 0;
	return s;
}

short get_free_block(block_t *block)
{
	uint64_t pos;

	if (block_table_get_first_unused(&pos) != 0)
		return 1;

	if (block_table_set_used(pos, 1) != 0)
		return 2;

	block->pos = pos;

	return 0;
}

short block_set_buf_data(block_t *s, uint8_t *data, size_t len)
{
	// UNSAFE
	if (data == NULL)
		return 1;
	if (BLOCK_DATA_LEN < len)
		return 2;

	memcpy(s->data, data, len);
	s->len = len;

	return 0;
}

short block_write(block_t *block)
{
	size_t position = BLOCKS_SHIFT + block->pos * BLOCK_SIZE;

	if (fseek(DISK_FILE, position, SEEK_SET) != 0)
		return 1;

	if (block->len > BLOCK_DATA_LEN)
		return 2;

	if (fwrite(&(block->len), BLOCK_LEN_SIZE, 1, DISK_FILE) != 1)
		return 3;

	if (fseek(DISK_FILE, position + BLOCK_LEN_SIZE, SEEK_SET) != 0)
		return 4;

	if (fwrite(block->data, 1, block->len, DISK_FILE) != block->len)
		return 5;

	return 0;
}

short block_read(block_t *block)
{
	uint64_t len;

	size_t position = BLOCKS_SHIFT + block->pos * BLOCK_SIZE;

	if (fseek(DISK_FILE, position, SEEK_SET) != 0)
		return 1;

	if (fread(&(len), BLOCK_LEN_SIZE, 1, DISK_FILE) != 1)
		return 2;

	if (len > BLOCK_DATA_LEN)
		return 3;

	block->len = len;

	if (fseek(DISK_FILE, position + BLOCK_LEN_SIZE, SEEK_SET) != 0)
		return 4;

	if (fread((block->data), 1, block->len, DISK_FILE) != block->len)
		return 5;

	return 0;
}

short block_free(block_t *block)
{
	free(block->data);
	block->data = NULL;
	free(block);
	block = NULL;
	return 0;
}

short block_disk_free(block_t *block)
{
	if (block_table_set_used(block->pos, 0) != 0)
		return 1;

	return 0;
}
