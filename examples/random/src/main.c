#include <mes.h>
#include <gpu.h>
#include <rng.h>
#include <stdint.h>
#include <timer.h>

uint8_t start(void) {
    rng_init();
    while(true) {
	gpu_blank(FRONT_BUFFER, 0);
	for(uint8_t y = 0; y < 120; y += 8) {
	    for(uint8_t x = 2; x < 156; x += 6) {
		uint8_t fgcolor = rng_u32() & 0b111;
		uint8_t bgcolor = rng_u32() & 0b111;
		char character[2] = {'0' + rng_u32() % 80, 0};
		gpu_print_text(FRONT_BUFFER, x, y, fgcolor, bgcolor, character);
		timer_block_ms(10);
	    }
	}
    }
    return CODE_RESTART;
}
