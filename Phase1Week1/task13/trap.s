.section .text
.globl trap_entry

trap_entry:
	csrr t0, mcause
	li t1, 0x80000007    	# Machine timer interrupt (bit 31 set, cause = 7)
	bne t0, t1, other_trap

	call mtimer_handler  	# Call C timer interrupt handler

	mret                	# Return from trap

other_trap:
	j .
