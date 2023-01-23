#include "gpu.h"
#include "gpu_internal.h"

// =========================== VMES ===========================

uint8_t* _vmes_gpu_buffer1 = NULL;
uint8_t* _vmes_gpu_buffer2 = NULL;
bool* _vmes_gpu_buffer_switch = NULL;
uint8_t* _vmes_color_palette = NULL;
uint8_t* _vmes_gpu_front_buffer() {if (*_vmes_gpu_buffer_switch) return _vmes_gpu_buffer1; else return _vmes_gpu_buffer2;}
uint8_t* _vmes_gpu_back_buffer() {if (*_vmes_gpu_buffer_switch) return _vmes_gpu_buffer2; else return _vmes_gpu_buffer1;}
uint8_t* _vmes_blank_buffer = NULL;

void _vmes_gpu_init(uint8_t* sdl_buffer1, uint8_t* sdl_buffer2, bool* buffer_switch) {
    _vmes_gpu_buffer1 = sdl_buffer1;
    _vmes_gpu_buffer2 = sdl_buffer2;
    _vmes_gpu_buffer_switch = buffer_switch;
    _vmes_color_palette = malloc(8*3); // 8 distinct colors * 3 values (RGB) per color
    _vmes_blank_buffer = malloc((WIDTH*HEIGHT*3) / 8);
    // default color palette
    _VMES_PALETTE_SET(_vmes_color_palette, 0, 0b000, 0b000, 0b000); // black
    _VMES_PALETTE_SET(_vmes_color_palette, 1, 0b111, 0b111, 0b111); // white
    _VMES_PALETTE_SET(_vmes_color_palette, 2, 0b111, 0b000, 0b000); // red
    _VMES_PALETTE_SET(_vmes_color_palette, 3, 0b000, 0b111, 0b000); // green
    _VMES_PALETTE_SET(_vmes_color_palette, 4, 0b000, 0b000, 0b111); // blue
    _VMES_PALETTE_SET(_vmes_color_palette, 5, 0b111, 0b111, 0b000); // yellow
    _VMES_PALETTE_SET(_vmes_color_palette, 6, 0b111, 0b000, 0b111); // magenta
    _VMES_PALETTE_SET(_vmes_color_palette, 7, 0b000, 0b111, 0b111); // cyan
}

void _vmes_gpu_setpixel(uint8_t* sdl_buffer, uint8_t x, uint8_t y, uint8_t color) {
    sdl_buffer[y*WIDTH*(_VMES_BPP/8) + x*(_VMES_BPP/8) + RBIT] = (uint8_t) round((_VMES_PALETTE_GET_R(_vmes_color_palette, color)/7.0)*255);
    sdl_buffer[y*WIDTH*(_VMES_BPP/8) + x*(_VMES_BPP/8) + GBIT] = (uint8_t) round((_VMES_PALETTE_GET_G(_vmes_color_palette, color)/7.0)*255);
    sdl_buffer[y*WIDTH*(_VMES_BPP/8) + x*(_VMES_BPP/8) + BBIT] = (uint8_t) round((_VMES_PALETTE_GET_B(_vmes_color_palette, color)/7.0)*255);
    sdl_buffer[y*WIDTH*(_VMES_BPP/8) + x*(_VMES_BPP/8) + ABIT] = 255;
}

uint8_t _vmes_gpu_getpixel(uint8_t* mes_buffer, uint8_t width, uint8_t x, uint8_t y) {
    uint16_t pos = y * width + x;
    uint32_t pixels = (*(uint32_t *) (mes_buffer + (pos / 8) * BPP));
    return (pixels >> ((7 - (pos % 8)) * BPP)) & ((1 << BPP) - 1);
}

// =========================== MES ============================

void gpu_print_text(Buffer buffer, uint8_t ox, uint8_t oy, uint8_t foreground, uint8_t background, const char *text) {

}

void gpu_reset(void) {

}

void gpu_blank(Buffer buffer, uint8_t blank_with) {
    memset(_vmes_blank_buffer, blank_with, (WIDTH*HEIGHT*3) / 8);
    gpu_send_buf(buffer, WIDTH, HEIGHT, 0, 0, _vmes_blank_buffer);
}

void gpu_swap_buf(void) {
    *_vmes_gpu_buffer_switch = !*_vmes_gpu_buffer_switch;
}

void gpu_send_buf(Buffer buffer, uint8_t width, uint8_t height, uint8_t posx, uint8_t posy, void *pixels) {
    uint8_t* sdl_buffer;
    if (buffer == FRONT_BUFFER) sdl_buffer = _vmes_gpu_front_buffer();
    else sdl_buffer = _vmes_gpu_back_buffer();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            _vmes_gpu_setpixel(sdl_buffer, j+posx, i+posy, _vmes_gpu_getpixel((uint8_t*) pixels, width, j, i));
        }
    }
}

void gpu_display_buf(uint8_t xx, uint8_t yy, uint8_t ox, uint8_t oy, void *pixels) {

}