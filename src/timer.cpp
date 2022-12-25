#include "timer.h"

#include <unistd.h>
#include <iostream>
#include <chrono>

std::chrono::time_point<std::chrono::high_resolution_clock> startpoint;

void _timer_start() {
    std::cout << "timer start" << std::endl;
    startpoint = std::chrono::high_resolution_clock::now();
}

uint64_t time_ms() {
    std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(now-startpoint);
    return duration.count();
}

void sleep_ms(uint16_t milliseconds) {
    usleep(milliseconds * 1000);
}