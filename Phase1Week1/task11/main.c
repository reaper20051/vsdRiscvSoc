#include <stdint.h>

// Global variable in .data section
volatile uint32_t counter = 0;

// Simulated GPIO register
#define GPIO_ADDR 0x10012000
volatile uint32_t *gpio = (volatile uint32_t *)GPIO_ADDR;

// Entry point (linked to _start by linker script)
void _start(void) {
    // Simple loop writing to GPIO
    for (counter = 0; counter < 5; counter++) {
        *gpio = counter;

        // crude delay loop
        for (volatile int i = 0; i < 100000; ++i);
    }

    while (1);  // Infinite loop
}
