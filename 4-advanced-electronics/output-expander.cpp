#include "MCP23008.h"
#include "pico/stdio.h"
#include "pico/stdio_usb.h"
#include "pico/time.h"

[[noreturn]] int main() {
    stdio_init_all();

    // Setup pins for I2C
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    // Setup the MCP23008 output expander.
    // Since we connected the address pins to GND, the address is 0x20 + 0
    MCP23008 output_expander(0x20, i2c_default);
    output_expander.begin();

    // Configure pin 0 as an output.
    output_expander.pinMode1(0, OUTPUT);

    // Loop to use the MCP23008 to flash an LED
    while (true) {
        output_expander.write1(0, true);

        sleep_ms(500);

        output_expander.write1(0, false);

        sleep_ms(500);
    }
}
