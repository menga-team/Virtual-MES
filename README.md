# Virtual-MES
An Emulator of the Menga Entertainment System.

MES drivers (such as controller.h or gpu.h) and the CPU code are written in C, which means it
is up to the game developer to decide whether they code their game in C or C++. Since VMES
under the hood uses SDL2 for graphics and chrono for timing, a C++ compiler is still required.
Nonetheless, software in C can be tested using VMES just fine.

## Drivers:

### Controller:
* `get_button_by_contorller_and_index`
* `get_button_by_contorller_and_index_copy`
* `get_button_by_index`
* `get_button_by_index_copy`
* `get_buttons_by_controller`
* `get_buttons_by_controller_copy`
* `get_controller_status`
* `get_controller_status_copy`
* `get_controller_statuses`
* `get_controller_statuses_copy`

### GPU:

* [TODO] `send_buffer`
* [TODO] `send_rectangle`
* [TODO] `swap_buffers`

### Timer:

* `time_ms`
* `sleep_ms`
