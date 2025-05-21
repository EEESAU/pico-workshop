#include "pico/cyw43_arch.h"
#include "hardware/clocks.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Buzzer is on GP15.
constexpr uint buzzer_pin = 15;

[[noreturn]] int main() {
    stdio_init_all();
    cyw43_arch_init();

    // Set the red pin as PWM.
    gpio_set_function(buzzer_pin, GPIO_FUNC_PWM);

    // Get the PWM slice number for the red pin.
    auto slice = pwm_gpio_to_slice_num(buzzer_pin);

    // Set the system clock to 128 MHz.
    auto clock_success = set_sys_clock_hz(128 * MHZ, true);

    if (clock_success)
        // Turn on the LED if the clock was set correctly.
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);

    // Set the PWM clock divider to 64, so the PWM clock is 128 MHz / 64 = 2 MHz.
    // The lowest sound we can play is with wrap=65535 => f = 2 MHz / 65536 = 30 Hz.
    pwm_set_clkdiv(slice, 64);

    // Enable the PWM slice
    pwm_set_enabled(slice, true);

    while (true) {
        // 127 is 50% duty cycle
        pwm_set_gpio_level(buzzer_pin, 127);
        // wrap=7662 means that the sound frequency will be 2 MHz / 7662 = 261 Hz (note is C4, middle C).
        pwm_set_wrap(slice, 7662);

        sleep_ms(250);

        // wrap=6060 means that the sound frequency will be 2 MHz / 6060 = 330 Hz (note is E4).
        pwm_set_wrap(slice, 6060);

        sleep_ms(250);

        // wrap=5102 means that the sound frequency will be 2 MHz / 5102 = 392 Hz (note is G4).
        pwm_set_wrap(slice, 5102);

        sleep_ms(250);

        // Turn off the sound for one note
        pwm_set_gpio_level(slice, 0);

        sleep_ms(250);
    }
}