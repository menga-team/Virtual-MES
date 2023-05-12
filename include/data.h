#ifndef MES_DATA_H
#define MES_DATA_H

#include <data_internal.h>

uint8_t* data_read_block(uint32_t index);

void data_write_block(uint32_t index, uint8_t* block);

#endif //MES_DATA_H
