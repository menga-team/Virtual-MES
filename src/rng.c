#include <rng.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

void rng_init(void) {
    unsigned short tmp[3];
    tmp[0]=time(NULL);
    tmp[1]=time(NULL);
    tmp[2]=time(NULL);
    seed48(tmp);
}

uint32_t rng_u32(void) {
    return (uint32_t) lrand48();
}

