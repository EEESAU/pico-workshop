#include "boards/pico.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

[[noreturn]] int main() {
    stdio_init_all();

    // On the Pico W series, the onboard LED needs to be accessed through the CYW43 wireless module.
    // Initialise the wireless module.
    cyw43_arch_init();

    while (true) {
        // Tell the wireless module to turn on the LED.
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);

        sleep_ms(500);

        // Tell the wireless module to turn on the LED.
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);

        sleep_ms(500);
    }
}