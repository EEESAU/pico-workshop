#include "pico/stdlib.h"
#include "hardware/adc.h"

[[noreturn]] int main() {
    stdio_init_all();

    // Wait for the serial connection to setup.
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    // Initialise the ADC.
    adc_init();

    // Enable the temperature sensor
    adc_set_temp_sensor_enabled(true);

    // Select ADC input 4 (Builtin temperature sensor)
    adc_select_input(4);

    while (true) {
        auto adc_value = adc_read();

        // Convert from 0->4095 to 0->3.3V
        constexpr float conversion = 3.3f / (1<<12);

        auto voltage = static_cast<float>(adc_value) * conversion;

        // Convert to celsius
        auto celsius = 27.0 - (voltage - 0.706) / 0.001721;

        // Print the value
        stdio_printf("Current temperature is %f C\n", celsius);

        sleep_ms(100);
    }
}