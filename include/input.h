#ifndef MES_CONTROLLER_H
#define MES_CONTROLLER_H

#include <input_internal.h>
#include <font.h>

#define CONTROLLER_1 0
#define CONTROLLER_2 1
#define CONTROLLER_3 2
#define CONTROLLER_4 3

#define BUTTON_RIGHT 0
#define BUTTON_LEFT 1
#define BUTTON_DOWN 2
#define BUTTON_UP 3
#define BUTTON_SELECT 4
#define BUTTON_START 5
#define BUTTON_B 6
#define BUTTON_A 7

static const char *BUTTON_CHARACTERS[8] = {
    FONT_BUTTONRIGHT,
    FONT_BUTTONLEFT,
    FONT_BUTTONDOWN,
    FONT_BUTTONUP,
    FONT_SELECT0 FONT_SELECT1 FONT_SELECT2,
    FONT_START0 FONT_START1 FONT_START2,
    FONT_BUTTONB,
    FONT_BUTTONA,
};

/**
 * Gets button state by controller index and button index.
 * @param controller: index of controller
 * @param button: index of button
 *
 * @return: button state
 */
bool input_get_button(uint8_t controller, uint8_t button);

/**
 * Gets array of button states by controller index
 *
 * @param controller: index of controller
 *
 * @return: array button states
 */
bool* input_get_buttons(uint8_t controller);

/**
 * Gets controller status
 *
 * @param controller: index of controller
 *
 * @return: status of controller
 */
bool input_is_available(uint8_t controller);

/**
 * Gets array of controller statuses
 *
 * @return: array of controller status
 */
bool* input_get_avalability(void);


/**
 * Will change the clock frequency to the specified frequency.
 */
void input_change_freq(uint16_t freq);

#endif //MES_CONTROLLER_H
