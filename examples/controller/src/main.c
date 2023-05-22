#include <stdbool.h>

#include <timer.h>
#include <input.h>
#include <gpu.h>
#include "graphics.h"

#define FPS 60
#define FRAMETIME ((1.0/FPS)*1000)
#define PLAYERSIZE 10

#define BLACK 0b000
#define WHITE 0b001
#define GRAY 0b111

// palette
uint16_t palette[8] = {COLOR_TO_GPIO(0b000, 0b000, 0b000), \
                       COLOR_TO_GPIO(0b111, 0b111, 0b111), \
                       COLOR_TO_GPIO(0b111, 0b111, 0b000), \
                       COLOR_TO_GPIO(0b111, 0b000, 0b000), \
                       COLOR_TO_GPIO(0b110, 0b001, 0b001), \
                       COLOR_TO_GPIO(0b000, 0b111, 0b000), \
                       COLOR_TO_GPIO(0b000, 0000, 0b111), \
                       COLOR_TO_GPIO(0b011, 0b011, 0b011)};

uint8_t start(void) {
    gpu_update_palette(palette);
    Surface sur = surf_create(160, 120);
    while (true) {
        int basex = 3;
        int base_y[4] = {3, 3 + 8, 3 + 16, 3 + 24};
        int button_x[8] = {4, 0, 2, 2, 8, 8, 12, 14};
        int button_y[8] = {2, 2, 4, 0, 3, 1, 2, 2};

        // player movement
        surf_fill(&sur, BLACK);
        for (int player = 0; player < 4; player++) {
            for (int button = 0; button < 8; button++) {
                surf_set_pixel(&sur, basex + button_x[button], base_y[player] + button_y[button], GRAY);
            }
            surf_set_pixel(&sur, basex + 20, base_y[player] + 2, GRAY);
        }
        for (int player = 0; player < 4; player++) {
            for (int button = 0; button < 8; button++) {
                if (input_get_button(player, button)) {
                    surf_set_pixel(&sur, basex + button_x[button], base_y[player] + button_y[button], WHITE);
                }
            }
            if (input_is_available(player)) {
                surf_set_pixel(&sur, basex + 20, base_y[player] + 2, WHITE);
            }
        }

        gpu_block_frame();
        gpu_blank(BACK_BUFFER, 0);
        gpu_send_buf(BACK_BUFFER, sur.w, sur.h, 0, 0, sur.d);
        gpu_swap_buf();
    }
}
