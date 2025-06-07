#include <stdint.h>

// Memory-mapped CLINT addresses (platform-specific)
#define MTIMECMP   ((volatile uint64_t *)0x02004000)
#define MTIME  	((volatile uint64_t *)0x0200BFF8)
#define MSTATUS_MIE (1 << 3)
#define MIE_MTIE	(1 << 7)

// External trap handler in assembly
extern void trap_entry(void);

// Simple handler in C
void __attribute__((interrupt)) mtimer_handler(void) {
	volatile uint32_t *gpio = (uint32_t *)0x10012000;
	*gpio ^= 0x1;  // Toggle GPIO for visibility (e.g., LED)

	// Set next timer interrupt
	*MTIMECMP = *MTIME + 1000000;  // Simple periodic interval
}


void main() {
	// Set timer: next interrupt after 1 million ticks
	*MTIMECMP = *MTIME + 1000000;

	// Enable timer interrupt
	asm volatile("csrs mie, %0" :: "r"(MIE_MTIE));

	// Enable global machine interrupts
	asm volatile("csrs mstatus, %0" :: "r"(MSTATUS_MIE));

	// Set the machine trap-vector base address
	asm volatile("la t0, trap_entry\ncsrw mtvec, t0");

	while (1);  // Loop forever, wait for interrupts
}
