#include <stdint.h>

#define GPIO_ADDR 0x10012000

int main() {
    volatile uint32_t *gpio = (volatile uint32_t *)GPIO_ADDR;

    *gpio = 0x1;   // Set GPIO pin (e.g., turn on LED)
    *gpio = 0x0;   // Clear GPIO pin (e.g., turn off LED)

    while (1);     // Loop forever
}
