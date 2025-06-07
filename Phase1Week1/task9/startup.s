.section .text
	.globl _start

_start:
	la sp, stack_top	# Set up stack pointer
	call main       	# Call main function
1:  j 1b            	# Infinite loop to halt

	.section .bss
	.space 4096      	# 4 KB stack space
stack_top:
