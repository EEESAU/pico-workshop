#include "boards/pico.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

// Our button is connected to GP15 (Pin 20)
constexpr uint button_pin = 15;

[[noreturn]] int main() {
    stdio_init_all();

    cyw43_arch_init();

    // Initialise the pin and make it an input.
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);

    // Enable the internal pull-up resistor on the button pin.
    gpio_pull_up(button_pin);

    while (true) {
        // Since the button is on a pin that is pulled up, we have the following mapping:
        //     - 3.3V (true)    -> button is not pressed
        //     - 0V (false)     -> button is pressed
        auto button_value = gpio_get(button_pin);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, !button_value);
    }
}