#ifndef VMES_GPU_INTERNAL_H
#define VMES_GPU_INTERNAL_H

#include <stdint.h>
#include <stdbool.h>

#include <SDL.h>

#define FONT_TOFU0 "\x00"
#define FONT_BUTTONA "\x01"
#define FONT_BUTTONB "\x02"
#define FONT_BUTTONUP "\x03"
#define FONT_BUTTONDOWN "\x04"
#define FONT_BUTTONLEFT "\x05"
#define FONT_BUTTONRIGHT "\x06"
#define FONT_SELECT0 "\x07"
#define FONT_SELECT1 "\x08"
#define FONT_SELECT2 "\x09"
#define FONT_START0 "\x0A"
#define FONT_START1 "\x0B"
#define FONT_START2 "\x0C"
#define FONT_BUTTONBRACKETLEFT "\x0D"
#define FONT_BUTTONBRACKETRIGHT "\x0E"
#define FONT_AMOGUS "\x0F"
#define FONT_FPS0 "\x10"
#define FONT_FPS1 "\x11"
#define FONT_EXCLAMATIONQUESTIONMARK "\x12"
#define FONT_EXCLAMATIONMARKDOUBLE "\x13"
#define FONT_EXCLAMATIONMARKTRIPLE "\x14"
#define FONT_TFO0 "\x15"
#define FONT_TFO1 "\x16"
#define FONT_TFO2 "\x17"
#define FONT_ARROWUP "\x18"
#define FONT_ARROWDOWN "\x19"
#define FONT_ARROWRIGHT "\x1A"
#define FONT_ARROWLEFT "\x1B"
#define FONT_MENGA0 "\x1C"
#define FONT_MENGA1 "\x1D"
#define FONT_MENGA2 "\x1E"
#define FONT_MENGA3 "\x1F"
#define FONT_SPACE "\x20"
#define FONT_EXCLAMATIONMARK "\x21"
#define FONT_QUOTE "\x22"
#define FONT_HASHTAG "\x23"
#define FONT_DOLLAR "\x24"
#define FONT_PERCENT "\x25"
#define FONT_AMPERSAND "\x26"
#define FONT_APOSTROPHE "\x27"
#define FONT_LEFTPARENTHESIS "\x28"
#define FONT_RIGHTPARENTHESIS "\x29"
#define FONT_ASTERISK "\x2A"
#define FONT_PLUS "\x2B"
#define FONT_COMMA "\x2C"
#define FONT_MINUS "\x2D"
#define FONT_FULLSTOP "\x2E"
#define FONT_SLASH "\x2F"
#define FONT_0 "\x30"
#define FONT_1 "\x31"
#define FONT_2 "\x32"
#define FONT_3 "\x33"
#define FONT_4 "\x34"
#define FONT_5 "\x35"
#define FONT_6 "\x36"
#define FONT_7 "\x37"
#define FONT_8 "\x38"
#define FONT_9 "\x39"
#define FONT_COLON "\x3A"
#define FONT_SEMICOLON "\x3B"
#define FONT_LESSTHAN "\x3C"
#define FONT_EQUALS "\x3D"
#define FONT_GREATERTHAN "\x3E"
#define FONT_QUESTIONMARK "\x3F"
#define FONT_AT "\x40"
#define FONT_UPPERCASEA "\x41"
#define FONT_UPPERCASEB "\x42"
#define FONT_UPPERCASEC "\x43"
#define FONT_UPPERCASED "\x44"
#define FONT_UPPERCASEE "\x45"
#define FONT_UPPERCASEF "\x46"
#define FONT_UPPERCASEG "\x47"
#define FONT_UPPERCASEH "\x48"
#define FONT_UPPERCASEI "\x49"
#define FONT_UPPERCASEJ "\x4A"
#define FONT_UPPERCASEK "\x4B"
#define FONT_UPPERCASEL "\x4C"
#define FONT_UPPERCASEM "\x4D"
#define FONT_UPPERCASEN "\x4E"
#define FONT_UPPERCASEO "\x4F"
#define FONT_UPPERCASEP "\x50"
#define FONT_UPPERCASEQ "\x51"
#define FONT_UPPERCASER "\x52"
#define FONT_UPPERCASES "\x53"
#define FONT_UPPERCASET "\x54"
#define FONT_UPPERCASEU "\x55"
#define FONT_UPPERCASEV "\x56"
#define FONT_UPPERCASEW "\x57"
#define FONT_UPPERCASEX "\x58"
#define FONT_UPPERCASEY "\x59"
#define FONT_UPPERCASEZ "\x5A"
#define FONT_LEFTSQUAREBRACKET "\x5B"
#define FONT_BACKSLASH "\x5C"
#define FONT_RIGHTSQUAREBRACKET "\x5D"
#define FONT_CARET "\x5E"
#define FONT_UNDERSCORE "\x5F"
#define FONT_BACKTICK "\x60"
#define FONT_LOWERCASEA "\x61"
#define FONT_LOWERCASEB "\x62"
#define FONT_LOWERCASEC "\x63"
#define FONT_LOWERCASED "\x64"
#define FONT_LOWERCASEE "\x65"
#define FONT_LOWERCASEF "\x66"
#define FONT_LOWERCASEG "\x67"
#define FONT_LOWERCASEH "\x68"
#define FONT_LOWERCASEI "\x69"
#define FONT_LOWERCASEJ "\x6A"
#define FONT_LOWERCASEK "\x6B"
#define FONT_LOWERCASEL "\x6C"
#define FONT_LOWERCASEM "\x6D"
#define FONT_LOWERCASEN "\x6E"
#define FONT_LOWERCASEO "\x6F"
#define FONT_LOWERCASEP "\x70"
#define FONT_LOWERCASEQ "\x71"
#define FONT_LOWERCASER "\x72"
#define FONT_LOWERCASES "\x73"
#define FONT_LOWERCASET "\x74"
#define FONT_LOWERCASEU "\x75"
#define FONT_LOWERCASEV "\x76"
#define FONT_LOWERCASEW "\x77"
#define FONT_LOWERCASEX "\x78"
#define FONT_LOWERCASEY "\x79"
#define FONT_LOWERCASEZ "\x7A"
#define FONT_LEFTCURLYBRACKET "\x7B"
#define FONT_PIPE "\x7C"
#define FONT_RIGHTCURLYBRACKET "\x7D"
#define FONT_TILDE "\x7E"
#define FONT_TOFU127 "\x7F"
#define FONT_TOFU128 "\x80"
#define FONT_TOFU129 "\x81"
#define FONT_TOFU130 "\x82"
#define FONT_TOFU131 "\x83"
#define FONT_TOFU132 "\x84"
#define FONT_TOFU133 "\x85"
#define FONT_TOFU134 "\x86"
#define FONT_TOFU135 "\x87"
#define FONT_TOFU136 "\x88"
#define FONT_TOFU137 "\x89"
#define FONT_TOFU138 "\x8A"
#define FONT_TOFU139 "\x8B"
#define FONT_TOFU140 "\x8C"
#define FONT_TOFU141 "\x8D"
#define FONT_TOFU142 "\x8E"
#define FONT_TOFU143 "\x8F"
#define FONT_TOFU144 "\x90"
#define FONT_TOFU145 "\x91"
#define FONT_TOFU146 "\x92"
#define FONT_TOFU148 "\x94"
#define FONT_TOFU149 "\x95"
#define FONT_TOFU150 "\x96"
#define FONT_TOFU151 "\x97"
#define FONT_TOFU152 "\x98"
#define FONT_TOFU153 "\x99"
#define FONT_TOFU154 "\x9A"
#define FONT_TOFU155 "\x9B"
#define FONT_TOFU156 "\x9C"
#define FONT_TOFU157 "\x9D"
#define FONT_TOFU158 "\x9E"
#define FONT_TOFU159 "\x9F"
#define FONT_TOFU160 "\xA0"
#define FONT_TOFU161 "\xA1"
#define FONT_TOFU162 "\xA2"
#define FONT_TOFU163 "\xA3"
#define FONT_TOFU164 "\xA4"
#define FONT_TOFU165 "\xA5"
#define FONT_TOFU166 "\xA6"
#define FONT_TOFU167 "\xA7"
#define FONT_TOFU168 "\xA8"
#define FONT_LEFTHOOKBRACKET "\xA9"
#define FONT_RIGHTHOOKBRACKET "\xAA"
#define FONT_SPEAKERMUTE "\xAB"
#define FONT_SPEAKER "\xAC"
#define FONT_LIGHTNING "\xAD"
#define FONT_LEFTGUILLEMET "\xAE"
#define FONT_RIGHTGUILLEMET "\xAF"
#define FONT_SHADE0 "\xB0"
#define FONT_SHADE1 "\xB1"
#define FONT_SHADE2 "\xB2"
#define FONT_BOX0 "\xB3"
#define FONT_BOX1 "\xB4"
#define FONT_BOX2 "\xB5"
#define FONT_BOX3 "\xB6"
#define FONT_BOX4 "\xB7"
#define FONT_BOX5 "\xB8"
#define FONT_BOX6 "\xB9"
#define FONT_BOX7 "\xBA"
#define FONT_BOX8 "\xBB"
#define FONT_BOX9 "\xBC"
#define FONT_BOX10 "\xBD"
#define FONT_BOX11 "\xBE"
#define FONT_BOX12 "\xBF"
#define FONT_BOX13 "\xC0"
#define FONT_BOX14 "\xC1"
#define FONT_BOX15 "\xC2"
#define FONT_BOX16 "\xC3"
#define FONT_BOX17 "\xC4"
#define FONT_BOX18 "\xC5"
#define FONT_BOX19 "\xC6"
#define FONT_BOX20 "\xC7"
#define FONT_BOX21 "\xC8"
#define FONT_BOX22 "\xC9"
#define FONT_BOX23 "\xCA"
#define FONT_BOX24 "\xCB"
#define FONT_BOX25 "\xCC"
#define FONT_BOX26 "\xCD"
#define FONT_BOX27 "\xCE"
#define FONT_BOX28 "\xCF"
#define FONT_BOX29 "\xD0"
#define FONT_BOX30 "\xD1"
#define FONT_BOX31 "\xD2"
#define FONT_BOX32 "\xD3"
#define FONT_BOX33 "\xD4"
#define FONT_BOX34 "\xD5"
#define FONT_BOX35 "\xD6"
#define FONT_BOX36 "\xD7"
#define FONT_BOX37 "\xD8"
#define FONT_BOX38 "\xD9"
#define FONT_BOX39 "\xDA"
#define FONT_BOX40 "\xDB"
#define FONT_BOX41 "\xDC"
#define FONT_BOX42 "\xDD"
#define FONT_BOX43 "\xDE"
#define FONT_BOX44 "\xDF"
#define FONT_BOX45 "\xE0"
#define FONT_BOX46 "\xE1"
#define FONT_BOX47 "\xE2"
#define FONT_BOX48 "\xE3"
#define FONT_BOX49 "\xE4"
#define FONT_BOX50 "\xE5"
#define FONT_BOX51 "\xE6"
#define FONT_BOX52 "\xE7"
#define FONT_BOX53 "\xE8"
#define FONT_TOFU233 "\xE9"
#define FONT_TOFU234 "\xEA"
#define FONT_TOFU235 "\xEB"
#define FONT_TOFU236 "\xEC"
#define FONT_TOFU237 "\xED"
#define FONT_TOFU238 "\xEE"
#define FONT_TOFU239 "\xEF"
#define FONT_TOFU240 "\xF0"
#define FONT_TOFU241 "\xF1"
#define FONT_TOFU242 "\xF2"
#define FONT_TOFU243 "\xF3"
#define FONT_TOFU244 "\xF4"
#define FONT_TOFU245 "\xF5"
#define FONT_TOFU246 "\xF6"
#define FONT_TOFU247 "\xF7"
#define FONT_TOFU248 "\xF8"
#define FONT_TOFU249 "\xF9"
#define FONT_TOFU250 "\xFA"
#define FONT_TOFU251 "\xFB"
#define FONT_TOFU252 "\xFC"
#define FONT_TOFU253 "\xFD"
#define FONT_TOFU254 "\xFE"
#define FONT_TOFU255 "\xFF"

// vmes palette
#define _VMES_PALETTE_SET(palette, index, r, g, b) memcpy(palette+index*3, (const unsigned char []){r, g, b}, 3)
#define _VMES_PALETTE_GET_R(palette, index) palette[index*3]
#define _VMES_PALETTE_GET_G(palette, index) palette[index*3 + 1]
#define _VMES_PALETTE_GET_B(palette, index) palette[index*3 + 2]
#define _VMES_BLACK 0
#define _VMES_WHITE 1
#define _VMES_RED 2
#define _VMES_GREEN 3
#define _VMES_BLUE 4
#define _VMES_YELLOW 5
#define _VMES_MAGENTA 6
#define _VMES_CYAN 7

// mes buffer
#define WIDTH 160
#define HEIGHT 120
#define BPP 3
#define BPB 8
#define BPBFLOAT 8.0

// sdl surface
#define _VMES_WINDOW_SCALE 5 // mes buffer pixel to screen pixel ratio
#define _VMES_FPS 480
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
#define GET_BIT(BUFFER, B) _vmes_font_get_bit((BUFFER), (B)/8, 7-(B-(((B)/8)*8)))
#define SET_BIT(BUFFER, B, V) _vmes_font_set_bit((BUFFER), (B)/8, 7-(B-(((B)/8)*8)), (V))

extern uint8_t* _vmes_gpu_buffer1;
extern uint8_t* _vmes_gpu_buffer2;
extern bool* _vmes_gpu_buffer_switch;
extern bool* _vmes_gpu_reset;
uint8_t* _vmes_color_palette;
uint8_t* _vmes_gpu_front_buffer();
uint8_t* _vmes_gpu_back_buffer();
uint8_t* _vmes_blank_buffer;

uint8_t _vmes_font_get_bit (uint8_t* buffer, uint32_t byte, uint8_t bit);

void _vmes_font_set_bit(uint8_t* buffer, uint32_t byte, uint8_t bit, uint8_t value);

uint8_t* _vmes_get_sdl_buffer(Buffer buffer);

/// initialize gpu virtualization
void _vmes_gpu_init(uint8_t* sdl_buffer1, uint8_t* sdl_buffer2, bool* buffer_switch, bool* reset_switch);

/// set pixel of 32 bpp sdl buffer
void _vmes_gpu_setpixel(uint8_t* sdl_buffer, uint8_t x, uint8_t y, uint8_t color);

/// retrieve single pit from 3 bpp mes buffer
uint8_t _vmes_gpu_singlebit(uint8_t* mes_buffer, uint8_t width, uint8_t x, uint8_t y, uint8_t index);

/// retrieve pixel from 3 bpp mes buffer
uint8_t _vmes_gpu_getpixel(uint8_t* mes_buffer, uint8_t width, uint8_t x, uint8_t y);

#endif //VMES_GPU_INTERNAL_H