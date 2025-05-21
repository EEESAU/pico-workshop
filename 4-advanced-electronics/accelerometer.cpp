#include <stdio.h>
#include "ADXL345.h"

ADXL345 accelerometer;
int interrupt_pin = 0;

void accelerometer_interrupt_handler(uint gpio, uint32_t events) {
    printf("interrupt! reasons: 0x%x\n",
           accelerometer.getInterruptSources()); // get interrupt reasons and clear latched motion interrupts
}

[[noreturn]] int main() {
    stdio_init_all();

    accelerometer = ADXL345();
    accelerometer.begin(ADXL345_DEFAULT_ADDRESS, // I2C address
                        i2c_default, // Pico I2C bus (0 is default)
                        PICO_DEFAULT_I2C_SDA_PIN, // SDA pin (4 is default)
                        PICO_DEFAULT_I2C_SCL_PIN); // SCL pin (5 is default)

    accelerometer.setRange(ADXL345_RANGE_16_G); // set 16 g range
    accelerometer.setFreefallInterruptTime(350); // 350 ms minimum
    accelerometer.setFreefallInterruptTreshold(600); // below 600 mg
    accelerometer.setInterrupt(ADXL345_INT_FREE_FALL, true); // enable free fall interrupt

    gpio_set_irq_enabled_with_callback(interrupt_pin, GPIO_IRQ_EDGE_RISE, true, &accelerometer_interrupt_handler);

    while (true) {
        printf("X: %4d Y: %4d Z: %4d\n",
               // note: these are raw values, to get real gravitational force, you can use accelerometer.getEvent()
               accelerometer.getX(),
               accelerometer.getY(),
               accelerometer.getZ()
        );

        sleep_ms(100);
    }
}
