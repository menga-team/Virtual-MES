#include <rng.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

void rng_init(void) {
    srand(time(NULL));
}

uint32_t rng_u32(void) {
    return (uint32_t) lrand48();
}
