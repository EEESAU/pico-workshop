//
// Created by valen on 13/02/25.
//

#include "boards/pico.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {
    cyw43_arch_init();

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);

        sleep_ms(500);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);

        sleep_ms(500);
    }
}