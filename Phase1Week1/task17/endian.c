#include <stdio.h>
#include <stdint.h>

int main() {
	union {
    	uint32_t value;
    	uint8_t bytes[4];
	} test;

	test.value = 0x01020304;

	printf("Byte order: %02x %02x %02x %02x\n",
       	test.bytes[0], test.bytes[1], test.bytes[2], test.bytes[3]);

	return 0;
}

