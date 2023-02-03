#include "gpu.h"
#include "gpu_internal.h"
#include "font.h"

// =========================== VMES ===========================

uint8_t* _vmes_gpu_buffer1 = NULL;
uint8_t* _vmes_gpu_buffer2 = NULL;
bool* _vmes_gpu_buffer_switch = NULL;
bool* _vmes_gpu_reset = NULL;
uint8_t* _vmes_color_palette = NULL;
uint8_t* _vmes_gpu_front_buffer() {if (*_vmes_gpu_buffer_switch) return _vmes_gpu_buffer1; else return _vmes_gpu_buffer2;}
uint8_t* _vmes_gpu_back_buffer() {if (*_vmes_gpu_buffer_switch) return _vmes_gpu_buffer2; else return _vmes_gpu_buffer1;}
uint8_t* _vmes_blank_buffer = NULL;

void _vmes_gpu_init(uint8_t* sdl_buffer1, uint8_t* sdl_buffer2, bool* buffer_switch, bool* reset_switch) {
    _vmes_gpu_buffer1 = sdl_buffer1;
    _vmes_gpu_buffer2 = sdl_buffer2;
    _vmes_gpu_buffer_switch = buffer_switch;
    _vmes_color_palette = malloc(8*3); // 8 distinct colors * 3 values (RGB) per color
    _vmes_blank_buffer = malloc((WIDTH*HEIGHT*3) / 8);
    _vmes_gpu_reset = reset_switch;
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

uint8_t _vmes_font_get_bit (uint8_t* buffer, uint32_t byte, uint8_t bit) {
    uint8_t data_byte = buffer[byte] >> bit;
    return data_byte & 1;
}

void _vmes_font_set_bit(uint8_t* buffer, uint32_t byte, uint8_t bit, uint8_t value) {
    uint8_t mask = 1 << bit;
    if (!value && _vmes_font_get_bit(buffer, byte, bit)) buffer[byte] &= ~mask;
    if (value && !_vmes_font_get_bit(buffer, byte, bit)) buffer[byte] |= mask;
}

uint8_t* _vmes_get_sdl_buffer(Buffer buffer) {
    uint8_t* sdl_buffer;
    if (buffer == FRONT_BUFFER) sdl_buffer = _vmes_gpu_front_buffer();
    else sdl_buffer = _vmes_gpu_back_buffer();
    return sdl_buffer;
}

// =========================== MES ============================

void gpu_print_text(Buffer buffer, uint8_t ox, uint8_t oy, uint8_t foreground, uint8_t background, const char *text) {
    uint8_t* sdl_buffer = _vmes_get_sdl_buffer(buffer);
    for (int i = 0; i < strlen(text); i++) {
        uint8_t c = text[i];
        uint8_t posx = ox+6*i;
        uint8_t posy = oy;
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 6; k++) {
                if (GET_BIT(console_font_6x8, c*64 + j*8+k)) _vmes_gpu_setpixel(sdl_buffer, posx+k, posy+j, foreground);
                else _vmes_gpu_setpixel(sdl_buffer, posx+k, posy+j, background);
            }
        }
    }
}

void gpu_print_transparent_text(Buffer buffer, uint8_t ox, uint8_t oy, uint8_t color, const char *text) {
    uint8_t* sdl_buffer = _vmes_get_sdl_buffer(buffer);
    for (int i = 0; i < strlen(text); i++) {
        uint8_t c = text[i];
        uint8_t posx = ox+6*i;
        uint8_t posy = oy;
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 6; k++) {
                if (GET_BIT(console_font_6x8, c*64 + j*8+k)) _vmes_gpu_setpixel(sdl_buffer, posx+k, posy+j, color);
            }
        }
    }
}

void gpu_reset(void) {
    *_vmes_gpu_reset = true;
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

void gpu_display_buf(Buffer buffer, uint8_t width, uint8_t height, uint8_t posx, uint8_t posy, void *pixels) {
    gpu_send_buf(buffer, width, height, posx, posy, pixels);
    gpu_swap_buf();
}