#ifndef VMES_GPU_INTERNAL_H
#define VMES_GPU_INTERNAL_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

#define _VMES_COLOR(red, green, blue) (uint16_t)( \
((red & 0b100) >> 1) | ((red & 0b010) << 9) | ((red & 0b001) << 11) | \
((green & 0b100) << 10) | ((green & 0b010) << 12) | ((green & 0b001) << 14) | \
((blue & 0b100) << 5) | ((blue & 0b010) << 7) | ((blue & 0b001) << 9) \
)
#define _VMES_PALETTE_SET(palette, index, r, g, b) memcpy(palette+index*BPP, (const unsigned char []){r, g, b}, 3)
#define _VMES_PALETTE_GET_R(palette, index) palette[index*3]
#define _VMES_PALETTE_GET_G(palette, index) palette[index*3 + 1]
#define _VMES_PALETTE_GET_B(palette, index) palette[index*3 + 2]

// mes buffer
#define WIDTH 160
#define HEIGHT 120
#define BPP 3
#define PIXEL_MASK ((1 << BPP) - 1)

// sdl surface
#define WINDOW_SCALE 3 // mes buffer pixel to screen pixel ratio
#define _VMES_FPS 120
#define _VMES_FRAMETIME (1.0/_VMES_FPS)
#define _VMES_BPP 32
#define _VMES_BUFFERSIZE WIDTH*HEIGHT*(_VMES_BPP/8)
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#define RBIT 3
#define GBIT 2
#define BBIT 1
#define ABIT 0

extern uint8_t* _vmes_gpu_buffer1;
extern uint8_t* _vmes_gpu_buffer2;
extern bool* _vmes_gpu_buffer_switch;
uint8_t* _vmes_color_palette;
uint8_t* _vmes_gpu_front_buffer();
uint8_t* _vmes_gpu_back_buffer();

/// initialize gpu virtualization
void _vmes_gpu_init(uint8_t* sdl_buffer1, uint8_t* sdl_buffer2, bool* buffer_switch);

/// set pixel of 32 bpp sdl buffer
void _vmes_gpu_setpixel(uint8_t* sdl_buffer, uint8_t x, uint8_t y, uint8_t color);

/// retrieve pixel from 3 bpp mes buffer
uint8_t _vmes_gpu_getpixel(uint8_t* mes_buffer, uint8_t x, uint8_t y);

#endif //VMES_GPU_INTERNAL_H