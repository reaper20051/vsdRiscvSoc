#define UART0 0x10000000

void uart_putc(char c) {
	*(volatile char *)UART0 = c;
}

void uart_puts(const char *s) {
	while (*s) uart_putc(*s++);
}

int main() {
	uart_puts("Printing from UART\n");
	uart_puts("Value of x: 43\n");
	while (1);
}

