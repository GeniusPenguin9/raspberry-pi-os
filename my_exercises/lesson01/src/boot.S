#include "mm.h"

.section ".text.boot"

.globl _start
_start:
	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF		// x0 = processor_id, value range 0x0 ~ 0x3
	cbz	x0, master			// x0 == 0, jump to master; else execute next step

	//sp = (processor_id + 1) * #LOW_MEMORY
	mov x1, #LOW_MEMORY
	add x0, x0, #1
	mul x1, x1, x0
	mov sp, x1
	//x0 = processor_id
	sub x0, x0, #1
	bl  function
	b	proc_hang

proc_hang: 
	b 	proc_hang

master:
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

	mov	sp, #LOW_MEMORY 
	bl	kernel_main
	b 	proc_hang		// should never come here
