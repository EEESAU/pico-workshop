#include <cstdio>
#include "pico/stdlib.h"

int main() {
    // Initialise the Standard I/O interface. This will enable the USB serial communication.
    stdio_init_all();

    stdio_printf("Join EEESAU!\n");

    char string[21] = {'\0'};

    fgets(string, 20, stdin);

    printf("Received string: %s\n", string);
}