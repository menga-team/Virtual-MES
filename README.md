# Virtual-MES
An Emulator of the Menga Entertainment System.

## Provided functions:

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

### Time:

Get the current point in time:
* `mestime::Clock::now() -> mestime::Moment`

Calculate duration between points in time:
* `mestime::Duration::Duration()`
* `mestime::Duration::Duration(mestime::Moment, mestime::Moment)`
* `mestime::Duration::set(mestime::Moment, mestime::Moment)`


* `mestime::Duration::nanoseconds() -> uint64_t`
* `mestime::Duration::microseconds() -> uint64_t`
* `mestime::Duration::milliseconds() -> uint64_t`
* `mestime::Duration::seconds() -> uint64_t`
