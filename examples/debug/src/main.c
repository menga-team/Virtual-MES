#include <stdbool.h>
#include <math.h>

#include <timer.h>
#include <controller.h>
#include <gpu.h>

#define FPS 60
#define FRAMETIME ((1.0/FPS)*1000)
#define SIZE 10

/// round value up to the next multiple of a certain number
int roundup(int number, int multiple) {
    if (multiple == 0) return number;
    int remainder = number % multiple;
    if (remainder == 0) return number;
    return number + multiple - remainder;
}

/// returns the number of bytes needed to save a buffer of given dimensions
int bufferbytes(uint8_t width, uint8_t height) {
    return roundup(ceil((width*height*BPP) / BPBFLOAT), 3);
}

uint8_t start(void) {
    printf("mes_main called\n");

    uint32_t deltatime;
    uint32_t stop;
    uint32_t start;

    uint8_t* rectangle = malloc(bufferbytes(SIZE, SIZE));
    memset(rectangle, 0xFF, bufferbytes(SIZE, SIZE));

    uint8_t rect2[6] = {0b11111111, 0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b11100000};
    uint8_t* rect2ptr = (uint8_t*) &rect2;

    start = timer_get_ms();
    printf("about to start loop\n");

    uint8_t buttons[] = {BUTTON_UP, BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT};
    uint8_t colors[] = {_VMES_MAGENTA, _VMES_CYAN, _VMES_YELLOW, _VMES_GREEN};
    uint8_t arrowx[] = {    10, 10, 10, 10, 10,9, 11, 8, 12,
                            10, 10, 10, 10, 10, 9, 11, 8, 12,
                            8, 8, 10, 11, 12, 9, 9, 10, 10,
                            8, 9, 10, 11, 12, 11, 11, 10, 10};
    uint8_t arrowy[] = {10, 11, 12, 13, 14, 11, 11, 12, 12,
                        20, 21, 22, 23, 24, 23, 23, 22, 22,
                        32, 32, 32, 32, 32, 33, 31, 34, 30,
                        42, 42, 42, 42, 42,41, 43, 40, 44};

    while(true) {
        // clear buffer
        gpu_blank(BACK_BUFFER, 0);

        // render arrows
        for (int i = 0; i < 4; i++) {
            if (controller_get_button_by_controller_and_index(0, buttons[i])) {
                for (int j = 0; j < 9; j++) {
                    _vmes_gpu_setpixel(_vmes_gpu_back_buffer(), arrowx[9*i + j], arrowy[9*i + j], colors[i]);
                }
            }
        }

        // draw stuff
        gpu_send_buf(BACK_BUFFER, SIZE, SIZE, 50, 50, rectangle);
        gpu_send_buf(BACK_BUFFER, 3, 3, 5, 5, rect2ptr);

        // swap buffers
        gpu_swap_buf();

        // timing
        stop = timer_get_ms();
        deltatime = stop - start;
        if (deltatime < FRAMETIME) {
            timer_block_ms(FRAMETIME - deltatime);
        }
        start = timer_get_ms();
    }
}
