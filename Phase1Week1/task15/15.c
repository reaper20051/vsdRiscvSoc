#include <stdint.h>
// Shared lock variable (0 = unlocked, 1 = locked)
volatile int lock = 0;
// Shared resource
volatile int shared_counter = 0;
// Spin-lock acquire using lr.w / sc.w
void lock_mutex(volatile int *lock_addr) {
	int tmp;
	do {
    	asm volatile (
        	"lr.w %[val], (%[addr])\n"  	// Load-reserved from lock
        	"bnez %[val], 1f\n"         	// If already locked, skip
        	"li %[val], 1\n"            	// Load '1' to try acquiring lock
        	"sc.w %[val], %[val], (%[addr])\n" // Store-cond if still reserved
        	"1:"
        	: [val] "=&r" (tmp)
        	: [addr] "r" (lock_addr)
        	: "memory"
    	);
	} while (tmp != 0);  // Retry if store failed (lock taken)
}
void unlock_mutex(volatile int *lock_addr) {
	*lock_addr = 0;
}
void thread_A() {
	lock_mutex(&lock);
	shared_counter += 1;  // Critical section
	unlock_mutex(&lock);
}
void thread_B() {
	lock_mutex(&lock);
	shared_counter += 2;  // Critical section
	unlock_mutex(&lock);
}
int main() {
	thread_A();  // Simulate first thread
	thread_B();  // Simulate second thread
	while (1);
}
