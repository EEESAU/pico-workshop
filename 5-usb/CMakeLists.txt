add_executable(usb-hid usb-hid.cpp tusb_config.h usb_descriptors.c usb_descriptors.h)
target_include_directories(usb-hid PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(usb-hid pico_stdlib pico_cyw43_arch_none pico_unique_id tinyusb_device tinyusb_board)
pico_add_extra_outputs(usb-hid)