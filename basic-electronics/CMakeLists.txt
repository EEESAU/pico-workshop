add_executable(blink-led blink-led.cpp)
target_link_libraries(blink-led pico_stdlib)
pico_add_extra_outputs(blink-led)