#include <cstdio>
#include <cstring>

#include "pico/stdlib.h"

int main() {
    // Initialise the Standard I/O interface. This will enable the USB serial communication.
    stdio_init_all();

    // Wait for the serial connection to setup.
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    stdio_printf("Welcome to the EEESAU Microcontroller Workshop!\n");
}