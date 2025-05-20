#include <cstdio>
#include <cstring>

#include "pico/stdlib.h"

/// Helper function to read a string from standard input.
/// @param string Buffer to hold the string that will be read in
/// @param string_size The size of the buffer (Will read n-1 chars)
/// @return Number of characters read
size_t gets_s(char* string, size_t string_size) {
    if (string == nullptr) return 0;

    putchar('>');

    // Only want to read a maximum of string_size-1 characters to avoid buffer overflow.
    size_t i = 0;
    for (i = 0; i < string_size-1; i++) {
        // Read the character and print it back so the user sees what they're typing
        auto result = stdio_getchar();
        putchar(result);

        // Detect enter key
        if (result == '\n' || result == '\r' || result == EOF) break;

        string[i] = result;
    }

    // Add a null terminator
    string[i] = '\0';

    putchar('\n');

    // Return the length of the string
    return i;
}

int main() {
    // Initialise the Standard I/O interface. This will enable the USB serial communication.
    stdio_init_all();

    // Create a string to hold the input
    char input[21] = {'\0'};

    // Wait for the serial connection to setup.
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    while (true) {
        stdio_printf("What is the password?\n");

        // Get the input from the user
        gets_s(input, 21);

        // Use strcmp to compare strings
        if (std::strcmp(input, "password1234") == 0)
            printf("Correct password!\n");
        else
            printf("Wrong password!\n");

    }
}