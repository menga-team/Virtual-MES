#ifndef MES_CONTROLLER_H
#define MES_CONTROLLER_H

#include <input_internal.h>

/**
 * Gets button state by controller index and button index.
 * @param controller: index of controller
 * @param button: index of button
 *
 * @return: button state
 */
uint8_t input_get_button(uint8_t controller, uint8_t button);

/**
 * Gets array of button states by controller index
 *
 * @param controller: index of controller
 *
 * @return: array button states
 */
uint8_t* input_get_buttons(uint8_t controller);

/**
 * Gets controller status
 *
 * @param controller: index of controller
 *
 * @return: status of controller
 */
uint8_t input_get_controller(uint8_t controller);

/**
 * Gets array of controller statuses
 *
 * @return: array of controller status
 */
uint8_t* input_get_controllers(void);

#endif //MES_CONTROLLER_H
