#ifndef VMES_TIMER_H
#define VMES_TIMER_H

#include <cstdint>

void _timer_start();

uint64_t time_ms();

void sleep_ms(uint16_t milliseconds);

#endif //VMES_TIMER_H