#ifndef VMES_CONTROLLER_H
#define VMES_CONTROLLER_H

#include <cstring>

// order: up left down right start select a b
uint8_t buttons[32] = { 0 };
uint8_t active_controller[4] = { 0 };

const uint8_t *state = SDL_GetKeyboardState(NULL);

const uint8_t button_key_map[32] = {
        // controller 0
        SDL_SCANCODE_W,
        SDL_SCANCODE_A,
        SDL_SCANCODE_S,
        SDL_SCANCODE_D,
        SDL_SCANCODE_Z,
        SDL_SCANCODE_X,
        SDL_SCANCODE_Q,
        SDL_SCANCODE_E,

        // controller 1
        SDL_SCANCODE_T,
        SDL_SCANCODE_F,
        SDL_SCANCODE_G,
        SDL_SCANCODE_H,
        SDL_SCANCODE_V,
        SDL_SCANCODE_B,
        SDL_SCANCODE_R,
        SDL_SCANCODE_Y,

        // controller 2
        SDL_SCANCODE_I,
        SDL_SCANCODE_J,
        SDL_SCANCODE_K,
        SDL_SCANCODE_L,
        SDL_SCANCODE_M,
        SDL_SCANCODE_COMMA,
        SDL_SCANCODE_U,
        SDL_SCANCODE_O,

        // controller 3
        SDL_SCANCODE_UP,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_LEFTBRACKET,
        SDL_SCANCODE_RIGHTBRACKET,
        SDL_SCANCODE_MINUS,
        SDL_SCANCODE_EQUALS
};

void _update_controllers() {
    for (int i = 0; i < 32; i++) {
        buttons[i] = state[button_key_map[i]];
    }
}

/*
 * gets button state by controller index and button index
 *
 * @param controller: index of controller
 * @param button: index of button
 *
 * @return: button state
 */
static uint8_t get_button_by_contorller_and_index(int controller, int button) {
    return buttons[(controller*4) + button];
}

/*
 *
 * return a copy of the button state by controller index and button index
 *
 * @param controller: index of controller
 * @param button: index of button
 *
 * @return: copy of button state
 */
static uint8_t get_button_by_contorller_and_index_copy(int controller, int button) {
    uint8_t temp = buttons[(controller*4) + button];
    return temp;
}

/*
 * gets button state by button index
 *
 * @param button: index of button
 *
 * @return: button state
 */
static uint8_t get_button_by_index(int button) {
    return buttons[button];
}

/*
 * return a copy of the button state by button index
 *
 * @param button: index of button
 *
 * @return: copy of button state
 */
static uint8_t get_button_by_index_copy(int button) {
    uint8_t temp = buttons[button];
    return temp;
}

/*
 * gets array of button states by controller index
 *
 * @param controller: index of controller
 *
 * @return: array button states
 */
static uint8_t * get_buttons_by_controller(int controller) {
    uint8_t subset[8] = {0, 0, 0, 0, 0, 0, 0, 0 };
    for(int i=0; i<8; i++)
        subset[i] = buttons[(controller*4) + i];
    return subset;
}

/*
 * gets copy of array of button states by controller index
 *
 * @param controller: index of controller
 *
 * @return: copy of array button states
 */
static uint8_t * get_buttons_by_controller_copy(int controller) {
    uint8_t subset[8] = {0, 0, 0, 0, 0, 0, 0, 0 };
    for(int i=0; i<8; i++)
        subset[i] = buttons[(controller*4) + i];
    return subset;
}

/*
 * gets controller status
 *
 * @param controller: index of controller
 *
 * @return: status of controller
 */
static uint8_t get_controller_status(int controller) {
    return active_controller[controller];
}

/*
 * gets copy of controller status
 *
 * @param controller: index of controller
 *
 * @return: copy of status of controller
 */
static uint8_t get_controller_status_copy(int controller) {
    uint8_t temp = active_controller[controller];
    return temp;
}

/*
 * gets array of controller statuses
 *
 * @return: array of controller status
 */
static uint8_t * get_controller_statuses() {
    return active_controller;
}

/*
 * gets copy of array of controller statuses
 *
 * @return: copy of array of controller status
 */
static uint8_t * get_controller_statuses_copy() {
    uint8_t subset[4];
    memcpy(subset, active_controller, sizeof(uint8_t)*4);
    return subset;
}

#endif //VMES_CONTROLLER_H
