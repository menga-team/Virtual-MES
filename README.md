# Virtual-MES
An Emulator of the Menga Entertainment System.

## Drivers:

All publicly accessible variables intended for internal use are prefixed with
`_vmes_<filename>`

### Controller:
* `controller_get_button`
* `controller_get_statuses`

### GPU:

* `set_palette`
* [TODO] `send_buffer`
* [TODO] `send_rectangle`
* [TODO] `swap_buffers`

### Timer:

* `time_ms`
* `sleep_ms`
