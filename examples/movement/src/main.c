#include <stdbool.h>

#include <timer.h>
#include <controller.h>
#include <gpu.h>

#include "../include/mesgraphics.h"

#define FPS 60
#define FRAMETIME ((1.0/FPS)*1000)
#define PLAYERSIZE 10

uint8_t start(void) {
    uint32_t deltatime;
    uint32_t stop;
    uint32_t start;
    RectangularBuffer player = buffer_create(PLAYERSIZE, PLAYERSIZE);
    uint8_t playerx = 0;
    uint8_t playery = 0;
    char* teststring = "amogus! " FONT_AMOGUS " amogus";
    memset(player.data, 0xFF, BUFFER_SIZE(player.width, player.height));
    start = timer_get_ms();

    while(true) {

        // player movement
        if (controller_get_button_by_controller_and_index(0, BUTTON_UP)) {if (playery > 0) playery--;}
        else if (controller_get_button_by_controller_and_index(0, BUTTON_DOWN)) {if (playery < HEIGHT-PLAYERSIZE) playery++;}
        else if (controller_get_button_by_controller_and_index(0, BUTTON_LEFT)) {if (playerx > 0) playerx--;}
        else if (controller_get_button_by_controller_and_index(0, BUTTON_RIGHT)) {if (playerx < WIDTH-PLAYERSIZE) playerx++;}

        // player rendering
        gpu_blank(BACK_BUFFER, 0);
        gpu_send_buf(BACK_BUFFER, player.width, player.height, playerx, playery, player.data);
        gpu_print_text(BACK_BUFFER, 1, 1, 1, 3, teststring);
        gpu_print_transparent_text(BACK_BUFFER, 1, 10, 1, teststring);
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
