#include <string>
#include <iostream>

#include "pico/cyw43_arch.h"
#include "pico/stdio.h"
#include "pico/stdio_usb.h"
#include "pico/time.h"

int main() {
    stdio_init_all();
    cyw43_arch_init();

    // Wait for the serial connection to setup.
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    // We can use cout and cin in C++
    std::cout << "We're using C++, the future is here!" << std::endl;

    std::cout << "Enter a number: ";

    uint32_t num_times = 0;
    std::cin >> num_times;

    std::cout << "Flashing the LED " << num_times << " times..." << std::endl;

    for (uint32_t i = 0; i < num_times; i++) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
        sleep_ms(250);
    }

    std::cout << "Done!" << std::endl;
}