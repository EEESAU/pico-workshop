cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico-workshop C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

pico_sdk_init()

add_executable(hello
        main.c
)

pico_add_extra_outputs(hello)

target_link_libraries(hello pico_stdlib)