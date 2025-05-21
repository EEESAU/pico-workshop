#include <cstdio>
#include <cstdlib>

#include "pico/stdlib.h"
#include "pico/flash.h"
#include "hardware/flash.h"

constexpr uint button_pin = 15;

// We're going to erase and reprogram a region 256k from the start of flash.
// Once done, we can access this at XIP_BASE + 256k.
constexpr uint FLASH_TARGET_OFFSET = (256 * 1024);

const uint8_t *flash_target_contents = reinterpret_cast<const uint8_t*>((XIP_BASE + FLASH_TARGET_OFFSET));

// This function will be called when it's safe to call flash_range_erase
static void call_flash_range_erase(void *param) {
    uint32_t offset = reinterpret_cast<uint32_t>(param);
    flash_range_erase(offset, FLASH_SECTOR_SIZE);
}

// This function will be called when it's safe to call flash_range_program
static void call_flash_range_program(void *param) {
    uint32_t offset = static_cast<uintptr_t*>(param)[0];
    const auto *data = reinterpret_cast<const uint8_t*>(static_cast<uintptr_t*>(param)[1]);
    flash_range_program(offset, data, FLASH_PAGE_SIZE);
}

void wait_for_press() {
wait_press:
    while (gpio_get(button_pin))
        tight_loop_contents();

    for (uint i = 0; i < 10; i++) {
        if (gpio_get(button_pin))
            goto wait_press;

        sleep_ms(1);
    }
}

int main() {
    stdio_init_all();

    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);
    gpio_pull_up(button_pin);

    while (!stdio_usb_connected())
        sleep_ms(100);

    uint32_t num_press[64] = {*flash_target_contents, 0};

    while (true) {
        stdio_printf("Button has been pressed %i times.\n", num_press[0]);

        wait_for_press();

        num_press[0]++;

        while (!gpio_get(button_pin))
            tight_loop_contents();

        sleep_ms(100);

        // Note that a whole number of sectors must be erased at a time.
        printf("\nErasing target region...\n");

        // Flash is "execute in place" and so will be in use when any code that is stored in flash runs, e.g. an interrupt handler
        // or code running on a different core.
        // Calling flash_range_erase or flash_range_program at the same time as flash is running code would cause a crash.
        // flash_safe_execute disables interrupts and tries to cooperate with the other core to ensure flash is not in use
        // See the documentation for flash_safe_execute and its assumptions and limitations
        int rc = flash_safe_execute(call_flash_range_erase, reinterpret_cast<void*>(FLASH_TARGET_OFFSET), UINT32_MAX);
        hard_assert(rc == PICO_OK);

        printf("\nProgramming target region...\n");
        uintptr_t params[] = { FLASH_TARGET_OFFSET, reinterpret_cast<uintptr_t>(num_press)};
        rc = flash_safe_execute(call_flash_range_program, params, UINT32_MAX);
        hard_assert(rc == PICO_OK);
    }
}