#include <cstdio>
#include <cstring>

#include "pico/stdlib.h"

int main() {
    // Initialise the Standard I/O interface. This will enable the USB serial communication.
    stdio_init_all();

    // Wait 1 second for the serial connection to setup.
    sleep_ms(1000);

    stdio_printf("Welcome to the EEESAU Microcontroller Workshop!\n");
}