#include "boards/pico.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {
    cyw43_arch_init();

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
}