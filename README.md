# Virtual-MES
An Emulator of the Menga Entertainment System.

## Drivers:

Headers are copied from [menga-team/MES](https://github.com/menga-team/MES)
to ensure feature parity.

Following functions are available:

### Controller:
* `controller_get_button_by_controller_and_index`
* `controller_get_buttons`
* `controller_get_status`
* `controller_get_statuses`

### GPU:
* [TODO] `gpu_print_text`
* [TODO] `gpu_reset`
* `gpu_blank`
* `gpu_swap_buf`
* `gpu_send_buf`
* [TODO] `gpu_display_buf`

### Timer:
* `timer_get_ms`
* `timer_block_ms`
