cmake_minimum_required(VERSION 3.22)

include(pico_sdk_import.cmake)

project(pico-workshop C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD pico2_w CACHE STRING "Board type")

pico_sdk_init()


# Setup basic blink program
add_executable(blink
        onboard_led.c
)

pico_add_extra_outputs(blink)

target_link_libraries(blink pico_stdlib)
target_link_libraries(blink pico_cyw43_arch_none)