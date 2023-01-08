#include <unistd.h>
#include <SDL_timer.h>
#include "timer.h"

uint32_t timer_get_ms() {
    return SDL_GetTicks();
}

void timer_block_ms(uint32_t milliseconds) {
    usleep(milliseconds*1000);
}
