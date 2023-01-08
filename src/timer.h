#ifndef VMES_TIMER_H
#define VMES_TIMER_H

#include <stdint.h>

uint32_t timer_get_ms(void);

void timer_block_ms(uint32_t milliseconds);

#endif //VMES_TIMER_H