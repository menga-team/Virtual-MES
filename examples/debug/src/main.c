#include <stdbool.h>
#include <math.h>

#include <mes.h>
#include <timer.h>
#include <input.h>
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
    printf("start called\n");
    uint32_t deltatime;
    uint32_t stop;
    uint32_t start;

    // palette testing
    uint16_t* grayscale = malloc(16);
    grayscale[0] = _COLOR(0b000, 0b000, 0b000);
    grayscale[1] = _COLOR(0b001, 0b001, 0b001);
    grayscale[2] = _COLOR(0b010, 0b010, 0b010);
    grayscale[3] = _COLOR(0b011, 0b011, 0b011);
    grayscale[4] = _COLOR(0b100, 0b100, 0b100);
    grayscale[5] = _COLOR(0b101, 0b101, 0b101);
    grayscale[6] = _COLOR(0b110, 0b110, 0b110);
    grayscale[7] = _COLOR(0b111, 0b111, 0b111);

    uint16_t* standard = malloc(16);
    standard[0] = _COLOR(0b000, 0b000, 0b000);
    standard[1] = _COLOR(0b111, 0b111, 0b111);
    standard[2] = _COLOR(0b111, 0b000, 0b000);
    standard[3] = _COLOR(0b000, 0b111, 0b000);
    standard[4] = _COLOR(0b000, 0b000, 0b111);
    standard[5] = _COLOR(0b111, 0b111, 0b000);
    standard[6] = _COLOR(0b111, 0b000, 0b111);
    standard[7] = _COLOR(0b000, 0b111, 0b111);

    //                     66777888    34445556    11122233
    uint8_t rainbow[3] ={0b01110111, 0b00111001, 0b00000101};

    // buffer testing
    uint8_t* rectangle = malloc(bufferbytes(SIZE, SIZE));
    memset(rectangle, 0xFF, bufferbytes(SIZE, SIZE));
    uint8_t rect2[6] = {0b11111111, 0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b11100000};
    uint8_t* rect2ptr = (uint8_t*) &rect2;

    // controller testing
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

    uint8_t* player = malloc(39);
    memset(player, 0xFF, 39);
    uint8_t playerx = 0;
    uint8_t playery = 0;

    start = timer_get_ms();
    printf("about to start loop\n");

    while(true) {

        // test exit codes
        if (input_get_button(0, BUTTON_START)) return CODE_EXIT;
        else if (input_get_button(0, BUTTON_SELECT)) { timer_block_ms(1000); return CODE_RESTART;};

        // clear buffer
        gpu_blank(BACK_BUFFER, 0);

        // test controller
        for (int i = 0; i < 4; i++) {
            if (input_get_button(0, buttons[i])) {
                for (int j = 0; j < 9; j++) {
                    _vmes_gpu_setpixel(_vmes_gpu_back_buffer(), arrowx[9*i + j], arrowy[9*i + j], colors[i]);
                }
            }
        }

        // test gpu reset
        if (input_get_button(0, BUTTON_A) && input_get_button(0, BUTTON_B)) gpu_reset();

        // test palette change
        if (input_get_button(0, BUTTON_A)) gpu_update_palette(grayscale);
        if (input_get_button(0, BUTTON_B)) gpu_update_palette(standard);

        // player movement
        if (input_get_button(0, BUTTON_UP)) {if (playery > 0) playery--;}
        else if (input_get_button(0, BUTTON_DOWN)) {if (playery < HEIGHT-10) playery++;}
        else if (input_get_button(0, BUTTON_LEFT)) {if (playerx > 0) playerx--;}
        else if (input_get_button(0, BUTTON_RIGHT)) {if (playerx < WIDTH-10) playerx++;}

        // player rendering
        gpu_send_buf(BACK_BUFFER, 10, 10, playerx, playery, player);

        // draw stuff
        gpu_send_buf(BACK_BUFFER, SIZE, SIZE, 50, 50, rectangle);
        gpu_send_buf(BACK_BUFFER, 3, 3, 5, 5, rect2ptr);
        gpu_send_buf(BACK_BUFFER, 8, 1, 2, 2, rainbow);

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
