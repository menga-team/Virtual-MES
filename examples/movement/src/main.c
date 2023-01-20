#include <stdbool.h>

#include <timer.h>
#include <controller.h>
#include <gpu.h>

#include "../include/mesgraphics.h"

#define FPS 60
#define FRAMETIME ((1.0/FPS)*1000)
#define PLAYERSIZE 10

int mes_main( void* data) {
    uint32_t deltatime;
    uint32_t stop;
    uint32_t start;
    RectangularBuffer player = buffer_create(PLAYERSIZE, PLAYERSIZE);
    uint8_t playerx = 0;
    uint8_t playery = 0;

    memset(player.data, 0, player.width*player.height);
    start = timer_get_ms();

    while(true) {

        // player movement
        if (controller_get_button_by_controller_and_index(0, BUTTON_UP)) {if (playery > 0) playery--;}
        else if (controller_get_button_by_controller_and_index(0, BUTTON_DOWN)) {if (playery < 120-PLAYERSIZE) playery++;}
        else if (controller_get_button_by_controller_and_index(0, BUTTON_LEFT)) {if (playerx > 0) playerx--;}
        else if (controller_get_button_by_controller_and_index(0, BUTTON_DOWN)) {if (playerx < 160-PLAYERSIZE) playerx++;}

        // player rendering
        gpu_send_buf(BACK_BUFFER, player.width, player.height, playerx, playery, player.data);
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
