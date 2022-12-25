#include "gpu.h"

#include <map>
#include <tuple>
#include <bitset>
#include <iostream>

/*

0
G LSB
G 2.MSB
G MSB
R MSB
R 2.MSB
R LSB
B MSB
B 2.MSB
B LSB
0
0
0
0
0
0

 */

std::map<uint8_t, uint16_t> _palette;

// [00000RRR], [00000GGG], [00000BBB]
std::map<uint8_t, std::tuple<uint8_t, uint8_t, uint8_t>> _easy_palette;

void set_palette(uint16_t palette[8]) {
    for (int i = 0; i < 8; i++) {
        _palette[i] = palette[i];
    }

    // WORK IN PROGRESS
    for (int i = 0; i < 8; i++) {
        _easy_palette[i] = std::make_tuple(_palette[i] >> 6, _palette[i] >> 3, _palette[i]);
        std::cout << std::bitset<8>(std::get<0>(_easy_palette[i]));
        std::cout << std::bitset<8>(std::get<1>(_easy_palette[i]));
        std::cout << std::bitset<8>(std::get<2>(_easy_palette[i]));

    }
}

void send_buffer(uint8_t buffer[7200]) {

}

void send_rectangle(uint8_t width, uint8_t length, uint8_t x, uint8_t y, uint8_t rectangle[width * length]) {

}

void swap_buffers() {

}
