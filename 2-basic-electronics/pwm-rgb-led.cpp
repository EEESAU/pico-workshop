#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Our LED is connected to GP13, GP12, GP11
constexpr uint red_pin = 13;
constexpr uint blue_pin = 12;
constexpr uint green_pin = 11;

[[noreturn]] int main() {
    stdio_init_all();

    // Set the red pin as PWM.
    gpio_set_function(red_pin, GPIO_FUNC_PWM);

    // Get the PWM slice number for the red pin.
    auto red_slice = pwm_gpio_to_slice_num(red_pin);

    // Enable the PWM slice that controls the red pin.
    pwm_set_wrap(red_slice, 1<<16 - 1);
    pwm_set_enabled(red_slice, true);

    uint8_t red_value = 0;
    bool red_going_up = true;

    while (true) {
        // Square the value so that the brightness increase looks linear.
        pwm_set_gpio_level(red_pin, red_value * red_value);

        // Some logic for the pulsing brightness.
        if (red_going_up)
            red_value += 1;
        else
            red_value -= 1;

        if (red_value == 0)
            red_going_up = true;
        if (red_value == 255)
            red_going_up = false;

        sleep_ms(10);
    }
}