add_executable(blink-led blink-led.cpp)
target_link_libraries(blink-led pico_stdlib)
pico_add_extra_outputs(blink-led)
pico_enable_stdio_usb(blink-led 1)

add_executable(onboard-led onboard-led.cpp)
target_link_libraries(onboard-led pico_stdlib pico_cyw43_arch_none)
pico_add_extra_outputs(onboard-led)
pico_enable_stdio_usb(onboard-led 1)

add_executable(button-input button-input.cpp)
target_link_libraries(button-input pico_stdlib pico_cyw43_arch_none)
pico_add_extra_outputs(button-input)
pico_enable_stdio_usb(button-input 1)

add_executable(adc-rgb-led pwm-rgb-led.cpp)
target_link_libraries(adc-rgb-led pico_stdlib hardware_pwm)
pico_add_extra_outputs(adc-rgb-led)
pico_enable_stdio_usb(adc-rgb-led 1)