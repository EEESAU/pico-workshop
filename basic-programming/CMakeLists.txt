add_executable(serial-monitor serial-monitor.cpp)
target_link_libraries(serial-monitor pico_stdlib)
pico_enable_stdio_usb(serial-monitor 1)
pico_add_extra_outputs(serial-monitor)