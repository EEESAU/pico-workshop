#include "hardware/gpio.h"
#include "pico/stdio.h"
#include "pico/stdio_usb.h"
#include "pico/time.h"

constexpr uint trig_pin = 15;
constexpr uint echo_pin = 14;

float measure_distance() {
    // Send a pulse on the TRIG pin.
    gpio_put(trig_pin, true);
    sleep_us(10);
    gpio_put(trig_pin, false);

    // Wait until we get an echo.
    while (!gpio_get(echo_pin))
        tight_loop_contents();

    const auto start_time = time_us_32();

    while (gpio_get(echo_pin))
        tight_loop_contents();

    const auto time = time_us_32() - start_time;

    // Sound travels at ~340 m/s
    // Distance = time * speed
    // Divide by two so we don't count the echo.
    return (static_cast<float>(time) / 1000000.0f) * 340.0f / 2.0f;
}

[[noreturn]] int main() {
    stdio_init_all();

    // Setup pin directions.
    gpio_init(trig_pin);
    gpio_set_dir(trig_pin, GPIO_OUT);
    gpio_init(echo_pin);
    gpio_set_dir(echo_pin, GPIO_IN);
    gpio_pull_down(echo_pin);

    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    stdio_printf("Ultrasonic sensor started\n");

    while (true) {
        const auto distance = measure_distance();

        stdio_printf("Distance: %.3f m\n", distance);

        sleep_ms(500);
    }
}
