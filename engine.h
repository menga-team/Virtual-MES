#ifndef VMES_ENGINE_H
#define VMES_ENGINE_H

#include <unistd.h>
#include "mestime.h"

mestime::Moment last = mestime::Clock::now();
mestime::Moment now = mestime::Clock::now();
mestime::Duration deltatime;

void update() {
    // delta time
    now = mestime::Clock::now();
    deltatime.set(last, now);
    last = now;

    // do something

    // fps cap
    if(16666 - deltatime.microseconds() > 0) {
        usleep(16666);
    }
}

#endif //VMES_ENGINE_H
