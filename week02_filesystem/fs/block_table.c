#include <stdlib.h>
#include <stdio.h>

#include "block_table.h"

#include "disk.h"
#include "superblock.h"

#define BLOCK_TABLE_ATOM 1
#define ATOM_SIZE 8


short block_table_init()
{
	size_t buf_size;
	if (block_table != NULL)
		return 1;

	BLOCK_TABLE_LEN = (BLOCK_COUNT % ATOM_SIZE == 0) ?
				   BLOCK_COUNT / ATOM_SIZE :
				   BLOCK_COUNT / ATOM_SIZE + 1;

	BLOCK_TABLE_SIZE = BLOCK_TABLE_LEN * BLOCK_TABLE_ATOM;
	block_table = (uint8_t *)malloc(BLOCK_TABLE_SIZE);

	if (fseek(DISK_FILE, SUPERBLOCK_SIZE, SEEK_SET) != 0) {
		free(block_table);
		block_table = NULL;
		return 2;
	}

	if ((buf_size = fread(block_table, BLOCK_TABLE_ATOM, BLOCK_TABLE_LEN,
			 DISK_FILE)) != BLOCK_TABLE_LEN) {
		free(block_table);
		block_table = NULL;
		return 3;
	}

	return 0;
}

short block_table_check_used(uint64_t block, short *used)
{
	if (block_table == NULL)
		return 1;

	if (BLOCK_COUNT < block)
		return 2;

	uint64_t block_index = block / ATOM_SIZE;
	uint64_t block_shift = block % ATOM_SIZE;

	*used = block_table[block_index] & (1 << block_shift) ? 1 : 0;

	return 0;
}

short block_table_set_used(uint64_t block, short used)
{
	if (block_table == NULL)
		return 1;

	if (BLOCK_COUNT < block)
		return 2;

	uint64_t block_index = block / ATOM_SIZE;
	uint64_t block_shift = block % ATOM_SIZE;

	if (used) {
		if (!(block_table[block_index] & (1 << block_shift)))
			--BLOCK_FREE;
		block_table[block_index] |= (1 << block_shift);
	} else {
		if (block_table[block_index] & (1 << block_shift))
			++BLOCK_FREE;
		block_table[block_index] &= ~(1 << block_shift);
	}

	return 0;
}

short block_table_get_first_unused(uint64_t *block)
{
	uint64_t block_index;
	uint64_t block_shift;

	if (block_table == NULL)
		return 1;

	for (block_index = 0; block_index < BLOCK_TABLE_LEN; ++block_index) {
		if (block_index == 0xFFFF)
			continue;
		for (block_shift = 0; block_shift < ATOM_SIZE; ++block_shift) {
			if (!(block_table[block_index] & (1 << block_shift))) {
				*block = block_index * ATOM_SIZE + block_shift;
				return 0;
			}
		}
	}
	return 2;
}

short block_table_save()
{
	if (block_table == NULL)
		return 1;

	if (fseek(DISK_FILE, SUPERBLOCK_SIZE, SEEK_SET) != 0)
		return 2;

	if (fwrite(block_table, BLOCK_TABLE_ATOM, BLOCK_TABLE_LEN,
		   DISK_FILE) != BLOCK_TABLE_LEN)
		return 3;

	return 0;
}

short block_table_free()
{
	if (block_table == NULL)
		return 1;

	free(block_table);
	block_table = NULL;

	return 0;
}
