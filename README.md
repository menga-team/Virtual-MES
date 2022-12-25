# Virtual-MES
An Emulator of the Menga Entertainment System.

MES drivers (such as controller.h or gpu.h) and the CPU code are written in C, which means it
is up to the game developer to decide whether they code their game in C or C++. Since VMES
under the hood uses SDL2 for graphics and chrono for timing, a C++ compiler is still required.
Nonetheless, software in C can be tested using VMES just fine.

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
