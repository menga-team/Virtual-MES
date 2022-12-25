#include <vmes.h>
#include <timer.h>

// if delta-time is above 65 seconds I have more important concerns than overflowing
uint16_t deltatime;
uint64_t last;
uint64_t now;

void update() {
    // delta time
    now = time_ms();
    deltatime = now - last;
    last = now;

    // do something

    // fps cap
    if (16 - deltatime > 0) {
        sleep_ms(16 - deltatime);
    }
}