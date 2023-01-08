#ifndef VMES_GPU_H
#define VMES_GPU_H

#include <stdint.h>
#include <stdbool.h>

#include <SDL.h>

extern uint8_t* _vmes_gpu_buffer1;
extern uint8_t* _vmes_gpu_buffer2;
extern bool* _vmes_gpu_buffer_switch;
uint8_t* _vmes_gpu_front_buffer();
uint8_t* _vmes_gpu_back_buffer();

void _vmes_gpu_init(uint8_t* buffer1, uint8_t* buffer2, bool* buffer_switch);

enum Buffer {
    FRONT_BUFFER = 0, BACK_BUFFER = 1
} __attribute__ ((__packed__));

typedef enum Buffer Buffer;

void gpu_set_palette(uint16_t* colors);

void gpu_send_rectangle(Buffer buffer, uint8_t posx, uint8_t posy, uint8_t width, uint8_t height, const uint8_t *pixels);

void gpu_swap_buffers();

#endif //VMES_GPU_H