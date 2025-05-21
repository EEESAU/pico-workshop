#include "pico/stdlib.h"
#include "pico/multicore.h"
#include <cstdint>
#include <cstdio>

constexpr uint32_t FLAG_VALUE = 123;

[[noreturn]] void core1_entry() {
    // Send a value to core 0 to let it know we are ready.
    multicore_fifo_push_blocking(FLAG_VALUE);

    uint32_t g = multicore_fifo_pop_blocking();

    if (g != FLAG_VALUE)
        printf("Hmm, that's not right on core 1!\n");
    else
        printf("Its all gone well on core 1!");

    while (true)
        tight_loop_contents();
}

void main() {
    stdio_init_all();

    while (!stdio_usb_connected())
        sleep_ms(100);

    printf("Hello, multicore!\n");

    multicore_launch_core1(core1_entry);

    // Wait for it to start up

    uint32_t g = multicore_fifo_pop_blocking();

    if (g != FLAG_VALUE)
        printf("Hmm, that's not right on core 0!\n");
    else {
        multicore_fifo_push_blocking(FLAG_VALUE);
        printf("It's all gone well on core 0!");
    }

}