add_executable(serial-monitor serial-monitor.cpp)
target_link_libraries(serial-monitor pico_stdlib)
# enable usb output, disable uart output
pico_enable_stdio_usb(serial-monitor 1)
pico_enable_stdio_uart(serial-monitor 0)
pico_add_extra_outputs(serial-monitor)

add_executable(serial-monitor-input serial-monitor-input.cpp)
target_link_libraries(serial-monitor-input pico_stdlib)
# enable usb output, disable uart output
pico_enable_stdio_usb(serial-monitor-input 1)
pico_enable_stdio_uart(serial-monitor-input 0)
pico_add_extra_outputs(serial-monitor-input)