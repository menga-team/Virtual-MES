#ifndef VMES_CONTROLLER_INTERNAL_H
#define VMES_CONTROLLER_INTERNAL_H

#include <stdint.h>

#define BUTTON_UP 0
#define BUTTON_LEFT 1
#define BUTTON_DOWN 2
#define BUTTON_RIGHT 3
#define BUTTON_START 4
#define BUTTON_SELECT 5
#define BUTTON_A 6
#define BUTTON_B 7

extern uint8_t _vmes_controller_buttons[32];

extern uint8_t _vmes_controller_active[4];

extern const uint8_t _vmes_controller_button_key_map[32];

void _vmes_controller_update();

#endif //VMES_CONTROLLER_INTERNAL_H