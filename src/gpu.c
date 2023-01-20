#include "gpu.h"
#include "gpu_internal.h"

// =========================== VMES ===========================

uint8_t* _vmes_gpu_buffer1 = NULL;
uint8_t* _vmes_gpu_buffer2 = NULL;
bool* _vmes_gpu_buffer_switch = NULL;
uint8_t* _vmes_color_palette = NULL;
uint8_t* _vmes_gpu_front_buffer() {if (*_vmes_gpu_buffer_switch) return _vmes_gpu_buffer1; else return _vmes_gpu_buffer2;}
uint8_t* _vmes_gpu_back_buffer() {if (*_vmes_gpu_buffer_switch) return _vmes_gpu_buffer2; else return _vmes_gpu_buffer1;}

void _vmes_gpu_init(uint8_t* sdl_buffer1, uint8_t* sdl_buffer2, bool* buffer_switch) {
    _vmes_gpu_buffer1 = sdl_buffer1;
    _vmes_gpu_buffer2 = sdl_buffer2;
    _vmes_gpu_buffer_switch = buffer_switch;
    _vmes_color_palette = malloc(8*3); // 8 distinct colors at 3bpp * 3 values (RGB) per color

    // default color palette
    _VMES_PALETTE_SET(_vmes_color_palette, 0, 0b000, 0b000, 0b000); // black
    _VMES_PALETTE_SET(_vmes_color_palette, 1, 0b000, 0b000, 0b000); // white
    _VMES_PALETTE_SET(_vmes_color_palette, 2, 0b000, 0b000, 0b000); // red
    _VMES_PALETTE_SET(_vmes_color_palette, 3, 0b000, 0b000, 0b000); // green
    _VMES_PALETTE_SET(_vmes_color_palette, 4, 0b000, 0b000, 0b000); // blue
    _VMES_PALETTE_SET(_vmes_color_palette, 5, 0b000, 0b000, 0b000); // yellow
    _VMES_PALETTE_SET(_vmes_color_palette, 6, 0b000, 0b000, 0b000); // magenta
    _VMES_PALETTE_SET(_vmes_color_palette, 7, 0b000, 0b000, 0b000); // cyan
}

void _vmes_gpu_setpixel(uint8_t* sdl_buffer, uint8_t x, uint8_t y, uint8_t color) {
    sdl_buffer[y*WIDTH*(_VMES_BPP/8)+x+RBIT] = _VMES_PALETTE_GET_R(_vmes_color_palette, color);
    sdl_buffer[y*WIDTH*(_VMES_BPP/8)+x+GBIT] = _VMES_PALETTE_GET_G(_vmes_color_palette, color);
    sdl_buffer[y*WIDTH*(_VMES_BPP/8)+x+BBIT] = _VMES_PALETTE_GET_B(_vmes_color_palette, color);
    sdl_buffer[y*WIDTH*(_VMES_BPP/8)+x+ABIT] = 255;
}

uint8_t _vmes_gpu_getpixel(uint8_t* mes_buffer, uint8_t x, uint8_t y) {
    uint16_t position = y*WIDTH + x;
    uint32_t bytes = (*(uint32_t *) (mes_buffer + (position / 8) * BPP)) /*& 0x00FFFFFF*/;
    return (bytes >> ((7 - (position % 8)) * BPP)) & PIXEL_MASK;
}

// =========================== MES ============================

void gpu_print_text(Buffer buffer, uint8_t ox, uint8_t oy, uint8_t foreground, uint8_t background, const char *text) {

}

void gpu_reset(void) {

}

void gpu_blank(Buffer buffer, uint8_t blank_with) {

}

void gpu_swap_buf(void) {
    *_vmes_gpu_buffer_switch = !*_vmes_gpu_buffer_switch;
}

void gpu_send_buf(Buffer buffer, uint8_t width, uint8_t height, uint8_t posx, uint8_t posy, void *pixels) {
    uint8_t* sdl_buffer;
    if (buffer == FRONT_BUFFER) sdl_buffer = _vmes_gpu_front_buffer();
    else sdl_buffer = _vmes_gpu_back_buffer();
    for (int i = posy; i < posy+height; i++) {
        for (int j = posx; j < posx+width; j++) {
            _vmes_gpu_setpixel(sdl_buffer, j, i, _vmes_gpu_getpixel((uint8_t*) pixels, j, i));
        }
    }
}

void gpu_display_buf(uint8_t xx, uint8_t yy, uint8_t ox, uint8_t oy, void *pixels) {

}