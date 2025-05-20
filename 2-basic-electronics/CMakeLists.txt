add_executable(blink-led blink-led.cpp)
target_link_libraries(blink-led pico_stdlib)
pico_add_extra_outputs(blink-led)
pico_enable_stdio_usb(blink-led 1)

add_executable(onboard-led onboard-led.cpp)
target_link_libraries(onboard-led pico_stdlib pico_cyw43_arch_none)
pico_add_extra_outputs(onboard-led)
pico_enable_stdio_usb(onboard-led 1)