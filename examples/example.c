#include "vmes.h"
#include "timer.h"
#define FPS 60
#define FRAMETIME ((1/FPS)*1000)
#define PLAYERSIZE 10
uint32_t deltatime;
uint32_t stop;
uint32_t start;
uint8_t* player;
uint8_t playerx;
uint8_t playery;

void init() {
    playerx = 0;
    playery = 0;
    uint16_t* colors = malloc(8);
    colors[0] = 0b0000000000000000; // black
    colors[1] = 0b0000000111111111; // white
    colors[2] = 0b0000000111000000; // red
    gpu_set_palette(colors);
    player = malloc(100);
    start = timer_get_ms();
}

void update() {

    // player movement
    if (controller_get_button(0, BUTTON_UP)) {if (playery > 0) playery--;}
    else if (controller_get_button(0, BUTTON_DOWN)) {if (playery < 120-PLAYERSIZE) playery++;}
    else if (controller_get_button(0, BUTTON_LEFT)) {if (playerx > 0) playerx--;}
    else if (controller_get_button(0, BUTTON_DOWN)) {if (playerx < 160-PLAYERSIZE) playerx++;}

    // player rendering
    gpu_send_rectangle(BACK_BUFFER, playerx, playery, PLAYERSIZE, PLAYERSIZE, player);
    gpu_swap_buffers();
    // timing
    stop = timer_get_ms();
    deltatime = stop - start;
    if (deltatime < FRAMETIME) {
        timer_block_ms(FRAMETIME - deltatime);
    }
    start = timer_get_ms();
}

void end() {
    free(player);
}