#include "pico/stdlib.h"

// Our LED is connected to GP15 (Pin 20)
constexpr uint led_pin = 15;

[[noreturn]] int main() {
    stdio_init_all();

    // Initialise the pin and make it an output.
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    while (true) {
        // Put 3.3V at the pin.
        gpio_put(led_pin, true);

        // Wait 500ms.
        sleep_ms(500);

        // Put 0V at the pin.
        gpio_put(led_pin, false);

        // Wait some more.
        sleep_ms(500);
    }
}