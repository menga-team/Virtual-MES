#include <string.h>
#include <stdlib.h>

#include <data.h>

uint8_t** _vmes_data_block_pointers = NULL;
uint32_t* _vmes_data_block_indices = NULL;
uint32_t _vmes_data_block_count = 0;

uint8_t* data_read_block(uint32_t index) {
    for (int i = 0; i < _vmes_data_block_count; i++) {
        if (_vmes_data_block_indices[i] == index) {
            uint8_t* block = malloc(512);
            memcpy(block, _vmes_data_block_pointers[i], 512);
            return block;
        }
    }
    return NULL;
}

void data_write_block(uint32_t index, uint8_t* block) {
    for (int i = 0; i < _vmes_data_block_count; i++) {
        if (_vmes_data_block_indices[i] == index) {
            memcpy(_vmes_data_block_pointers[i], block, 512);
            return;
        }
    }
    _vmes_data_block_indices = realloc(_vmes_data_block_indices, sizeof(uint32_t) * ++_vmes_data_block_count);
    _vmes_data_block_indices[_vmes_data_block_count-1] = index;
    _vmes_data_block_pointers = realloc(_vmes_data_block_pointers, sizeof(uint8_t**) * _vmes_data_block_count);
    uint8_t* blockptr = malloc(512);
    memcpy(blockptr, block, 512);
    _vmes_data_block_pointers[_vmes_data_block_count-1] = blockptr;
}


