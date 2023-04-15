#ifndef VMES_INPUT_INTERNAL_H
#define VMES_INPUT_INTERNAL_H

#include <stdbool.h>
#include <stdint.h>

extern bool _vmes_controller_buttons[32];

extern bool _vmes_controller_active[4];

extern const uint8_t _vmes_controller_button_key_map[32];

void _vmes_controller_update();

#endif //VMES_INPUT_INTERNAL_H
