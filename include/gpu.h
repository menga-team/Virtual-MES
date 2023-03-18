#ifndef MES_GPU_H
#define MES_GPU_H

enum Buffer {
    FRONT_BUFFER = 0, BACK_BUFFER = 1
} __attribute__ ((__packed__));

typedef enum Buffer Buffer;

#include <gpu_internal.h>

void gpu_print_text(Buffer buffer, uint8_t ox, uint8_t oy, uint8_t foreground, uint8_t background, const char *text);

void gpu_print_transparent_text(Buffer buffer, uint8_t ox, uint8_t oy, uint8_t color, const char *text);

void gpu_reset(void);

void gpu_blank(Buffer buffer, uint8_t blank_with);

void gpu_swap_buf(void);

void gpu_send_buf(Buffer buffer, uint8_t width, uint8_t height, uint8_t posx, uint8_t posy, void *pixels);

void gpu_display_buf(Buffer buffer, uint8_t width, uint8_t height, uint8_t posx, uint8_t posy, void *pixels);

void gpu_update_palette(const uint16_t *palette);

#endif //MES_GPU_H
