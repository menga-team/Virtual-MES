#ifndef VMES_CONTROLLER_H
#define VMES_CONTROLLER_H

#include <cstdint>

extern uint8_t _vmes_controller_buttons[32];

extern uint8_t _vmes_controller_active[4];

extern const uint8_t *_vmes_controller_keyboard_state;

extern const uint8_t _vmes_controller_button_key_map[32];

void _vmes_controller_update();

/**
 * Gets button state by controller index and button index.
 * @param controller: index of controller
 * @param button: index of button
 *
 * @return: button state
 */
uint8_t controller_get_button(int controller, int button);

/*
 * gets array of controller statuses
 *
 * @return: array of controller status
 */
uint8_t * controller_get_statuses();


#endif //VMES_CONTROLLER_H