#ifndef BLOCK_TABLE_H
#define BLOCK_TABLE_H

#include <stdint.h>

extern uint64_t BLOCK_TABLE_LEN;
extern uint64_t BLOCK_TABLE_SIZE;

short block_table_init();
short block_table_check_used(uint64_t, short *);
short block_table_set_used(uint64_t, short);
short block_table_get_first_unused(uint64_t *);
short block_table_save();
short block_table_free();

#endif
