#include <SDL.h>

#include <input.h>
#include <input_internal.h>
#include <stdint.h>

// order:
// 0      1     2     3   4       5      6  7
// right  left  down  up  select  start  b  a

bool _vmes_controller_buttons[32] = { 0 };
bool _vmes_controller_active[4] = { 0 };

const uint8_t _vmes_controller_button_key_map[32] = {
        // controller 0
        SDL_SCANCODE_D,
        SDL_SCANCODE_A,
        SDL_SCANCODE_S,
        SDL_SCANCODE_W,
        SDL_SCANCODE_X,
        SDL_SCANCODE_Z,
        SDL_SCANCODE_E,
        SDL_SCANCODE_Q,

        // controller 1
        SDL_SCANCODE_H,
        SDL_SCANCODE_F,
        SDL_SCANCODE_G,
        SDL_SCANCODE_T,
        SDL_SCANCODE_B,
        SDL_SCANCODE_V,
        SDL_SCANCODE_Y,
        SDL_SCANCODE_R,

        // controller 2
        SDL_SCANCODE_L,
        SDL_SCANCODE_J,
        SDL_SCANCODE_K,
        SDL_SCANCODE_I,
        SDL_SCANCODE_COMMA,
        SDL_SCANCODE_M,
        SDL_SCANCODE_O,
        SDL_SCANCODE_U,

        // controller 3
        SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_UP,
        SDL_SCANCODE_RIGHTBRACKET,
        SDL_SCANCODE_LEFTBRACKET,
        SDL_SCANCODE_EQUALS,
        SDL_SCANCODE_MINUS
};

void _vmes_controller_update() {
    const uint8_t *_vmes_controller_keyboard_state = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < 32; i++) {
        if (!_vmes_controller_active[i/8])  _vmes_controller_buttons[i] = 0;
        else _vmes_controller_buttons[i] = _vmes_controller_keyboard_state[_vmes_controller_button_key_map[i]];
    }
}

bool input_get_button(uint8_t controller, uint8_t button) {
    return _vmes_controller_buttons[(controller * 8) + button];
}

bool* input_get_buttons(uint8_t controller) {
    return _vmes_controller_buttons + controller*8;
}

bool input_is_available(uint8_t controller) {
    return _vmes_controller_active[controller];
}

bool* input_get_availability(void) {
    return _vmes_controller_active;
}

void input_change_freq(uint16_t freq) {
    // TODO
}
