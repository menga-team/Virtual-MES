#include <timer.h>
#include <gpu.h>
#include <data.h>
#include <mes.h>

static uint32_t pot(uint32_t n) {if (n == 0) return 1; uint32_t r = 10; for (uint32_t i = 0; i < n-1; i++) {r *= 10;} return r;}
static uint8_t dd(uint32_t num, uint32_t n) {uint32_t r; r = num / pot(n); r = r % 10; return (uint8_t) r;}
#define INLINE_DECIMAL3(NUM) (char[]) {dd(NUM, 2)+48, dd(NUM, 1)+48, dd(NUM, 0)+48, 0}

uint8_t x(uint8_t factor) { return 8+factor*6; }
uint8_t y(uint8_t factor) { return 8+factor*8; }

uint8_t start(void) {
    gpu_blank(FRONT_BUFFER, 0);

    // write
    uint8_t* block1 = malloc(512);
    memset(block1, 0, 512);
    block1[0] = 122;
    block1[1] = 33;
    block1[367] = 244;
    block1[511] = 1;
    data_write_block(13, block1);
    free(block1);
    uint8_t* block2 = malloc(512);
    memset(block2, 0, 512);
    block2[0] = 12;
    block2[1] = 64;
    block2[367] = 100;
    block2[511] = 4;
    data_write_block(14000, block2);
    free(block1);

    // read
    uint8_t* read1 = data_read_block(13);
    gpu_print_text(FRONT_BUFFER, x(1), y(1), 1, 0, INLINE_DECIMAL3(read1[0]));
    gpu_print_text(FRONT_BUFFER, x(1), y(3), 1, 0, INLINE_DECIMAL3(read1[1]));
    gpu_print_text(FRONT_BUFFER, x(1), y(5), 1, 0, INLINE_DECIMAL3(read1[367]));
    gpu_print_text(FRONT_BUFFER, x(1), y(7), 1, 0, INLINE_DECIMAL3(read1[511]));
    free(read1);
    uint8_t* read2 = data_read_block(14000);
    gpu_print_text(FRONT_BUFFER, x(10), y(1), 1, 0, INLINE_DECIMAL3(read2[0]));
    gpu_print_text(FRONT_BUFFER, x(10), y(3), 1, 0, INLINE_DECIMAL3(read2[1]));
    gpu_print_text(FRONT_BUFFER, x(10), y(5), 1, 0, INLINE_DECIMAL3(read2[367]));
    gpu_print_text(FRONT_BUFFER, x(10), y(7), 1, 0, INLINE_DECIMAL3(read2[511]));
    free(read2);

    return CODE_FREEZEFRAME;
}
