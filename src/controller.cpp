#include "controller.h"

#include <SDL.h>

// order: up left down right start select a b
uint8_t _vmes_controller_buttons[32] = { 0 };
uint8_t _vmes_controller_active[4] = { 0 };

const uint8_t *_vmes_controller_keyboard_state = SDL_GetKeyboardState(NULL);

const uint8_t _vmes_controller_button_key_map[32] = {
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

void _vmes_controller_update() {
    for (int i = 0; i < 32; i++) {
        _vmes_controller_buttons[i] = _vmes_controller_keyboard_state[_vmes_controller_button_key_map[i]];
    }
}

uint8_t controller_get_button(int controller, int button) {
    return _vmes_controller_buttons[(controller * 4) + button];
}

uint8_t * controller_get_statuses() {
    return _vmes_controller_active;
}
