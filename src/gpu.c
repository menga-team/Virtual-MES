#include "gpu.h"

uint8_t* _vmes_gpu_buffer1 = NULL;
uint8_t* _vmes_gpu_buffer2 = NULL;
bool* _vmes_gpu_buffer_switch = NULL;
uint8_t* _vmes_gpu_front_buffer() {if (*_vmes_gpu_buffer_switch) return _vmes_gpu_buffer1; else return _vmes_gpu_buffer2;}
uint8_t* _vmes_gpu_back_buffer() {if (*_vmes_gpu_buffer_switch) return _vmes_gpu_buffer2; else return _vmes_gpu_buffer1;}

void _vmes_gpu_init(uint8_t* buffer1, uint8_t* buffer2, bool* buffer_switch) {
    _vmes_gpu_buffer1 = buffer1;
    _vmes_gpu_buffer2 = buffer2;
    _vmes_gpu_buffer_switch = buffer_switch;
}

void gpu_set_palette(uint16_t* colors) {

}

void gpu_send_rectangle(Buffer buffer, uint8_t posx, uint8_t posy, uint8_t width, uint8_t height, const uint8_t *pixels) {

}

void gpu_swap_buffers() {
    *_vmes_gpu_buffer_switch = !*_vmes_gpu_buffer_switch;
}
