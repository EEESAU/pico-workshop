//
// Created by valen on 13/02/25.
//

#include "pico/stdlib.h"
#include "hardware/gpio.h"

int main() {
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(PICO_DEFAULT_LED_PIN, true);

        sleep_ms(500);

        gpio_put(PICO_DEFAULT_LED_PIN, false);

        sleep_ms(500);
    }
}