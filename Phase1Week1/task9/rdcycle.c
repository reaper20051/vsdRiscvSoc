#include <stdint.h>

static inline uint32_t rdcycle(void) {
	uint32_t cycles;
	__asm__ volatile ("rdcycle %0" : "=r"(cycles));
	return cycles;
}

void main() {
	volatile uint32_t start = rdcycle();

	// Simple delay loop
	for (volatile int i = 0; i < 100000; i++);

	volatile uint32_t end = rdcycle();

	// Calculate cycles taken during delay
	volatile uint32_t cycles_taken = end - start;

	// Infinite loop to keep program alive
	while (1) {}
}
