#include "pico/stdlib.h"
#include "hardware/adc.h"

// Potentiometer is on GP26
constexpr uint input_pin = 26;

[[noreturn]] int main() {
    stdio_init_all();

    // Wait for the serial connection to setup.
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    // Initialise the ADC.
    adc_init();

    // Make the potentiometer pin as an ACD input.
    adc_gpio_init(input_pin);

    // Select ADC input 0 (GP26)
    adc_select_input(0);

    while (true) {
        auto adc_value = adc_read();

        // Convert from 0->4095 to 0->3.3V
        constexpr float conversion = 3.3f / (1<<12);

        auto voltage = static_cast<float>(adc_value) * conversion;

        // Print the value
        stdio_printf("Current value: %f V, raw: %i\n", voltage, adc_value);

        sleep_ms(100);
    }
}