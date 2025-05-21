#include "pico/stdlib.h"
#include "pico/multicore.h"
#include <cstdint>
#include <cstdio>

#include "pico/cyw43_arch.h"
#include "pico/util/queue.h"

struct queue_entry {
    int32_t (*func)(int32_t) = nullptr;
    int32_t data = 0;
};

queue_t call_queue;
queue_t results_queue;

[[noreturn]] void core1_entry() {
    queue_entry entry;
    while (true) {
        // Wait for a message from core 0.
        queue_remove_blocking(&call_queue, &entry);

        int32_t result = 0;

        // Run the code to calculate the result.
        if (entry.func != nullptr)
            result = entry.func(entry.data);

        // If the result is odd, turn on the LED.
        if (result % 2 == 1)
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
        else
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);

        // Send the result back to core 0.
        queue_add_blocking(&results_queue, &result);
    }
}

// Calculate square of a number.
int32_t square(int32_t in) {
    return in * in;
}

int main() {
    stdio_init_all();

    cyw43_arch_init();

    while (!stdio_usb_connected())
        sleep_ms(100);

    stdio_printf("Welcome to multicore!\n");
    stdio_printf("I'm core 0, but I'm too lazy to do maths, so I'll make core 1 do it all for me!\n");

    // Initialise the queues to send messages between the cores.
    queue_init(&call_queue, sizeof(queue_entry), 2);
    queue_init(&results_queue, sizeof(int32_t), 2);

    multicore_launch_core1(core1_entry);

    for (int i = 0; i < 100; i++) {
        stdio_printf("Square of %i is... ", i);

        // Send data to core 1
        // Tell it to find the square of i.
        queue_entry entry = {square, i};
        queue_add_blocking(&call_queue, &entry);

        // Wait for response from core 1
        int32_t result = 0;
        queue_remove_blocking(&results_queue, &result);

        stdio_printf("%i\n", result);

        sleep_ms(1000);
    }

    stdio_printf("Finished!\n");
}