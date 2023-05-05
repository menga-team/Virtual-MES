#include <stdbool.h>

#include <timer.h>
#include <input.h>
#include <gpu.h>

#include "strings.h"
#include "maths.h"

#define PLAYERSIZE 10

uint8_t x(uint8_t factor) { return 8+factor*6; }
uint8_t y(uint8_t factor) { return 8+factor*8; }

uint8_t start(void) {
    uint32_t deltatime;
    uint32_t stop;
    uint32_t start;

    uint8_t* player = malloc(39); // 10 x 10 pixels
    memset(player, 0xFF, 39);
    uint8_t playerx = 0;
    bool direction = true;
    uint8_t frames = 1;
    bool last_button = false;

    while(true) {
        if (direction) playerx++;
        else playerx--;
        if (playerx == 150 || playerx == 0) direction = !direction;

        bool button = input_get_button(0, BUTTON_A);
        if (button != last_button && button) {
            frames++;
            if (frames == 9) frames = 1;
        }
        last_button = button;

        // player rendering
        gpu_blank(BACK_BUFFER, 0);
        gpu_send_buf(BACK_BUFFER, 10, 10, playerx, 50, player);
        gpu_print_text(BACK_BUFFER, x(1), y(1), 1, 0, INLINE_DECIMAL2(60/frames));
        gpu_print_text(BACK_BUFFER, x(4), y(1), 1, 0, "FPS");
        gpu_print_text(BACK_BUFFER, x(1), y(3), 1, 0, INLINE_DECIMAL2(frames));
        gpu_print_text(BACK_BUFFER, x(4), y(3), 1, 0, "FRAMES SKIPPED");
        gpu_swap_buf();

        // timing
        gpu_block_frames(frames);
    }
}
