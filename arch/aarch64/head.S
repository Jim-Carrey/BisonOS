/*
 * entry.S
 */
#include "mm.h"
#include "sysregs.h"

.section ".text.boot"
.globl _start
_start:
    //determning which core the code is running on
    //MPIDR_EL1:(Multi-Processor Affinity Register)
    mrs x0, mpidr_el1
    and x0, x0,#0xFF
    cbz x0, master //jump to label master if zero(primary core 0)
    b proc_hang    //hang for all non-primary CPU

proc_hang:
    b proc_hang

master:
    mrs x1, CurrentEL
    cmp x1, #12 	//CurrentEL_EL3 (3 << 2)
    b.eq el3_entry
    b el2_entry

el3_entry:
    ldr x0, =SCTLR_EL2_VALUE_MMU_DISABLED
    msr sctlr_el2, x0

    ldr x0, =HCR_HOST_NVHE_FLAGS
	msr hcr_el2, x0

    ldr x0, =SCR_VALUE
	msr scr_el3, x0

    ldr x0, =SPSR_EL2
	msr spsr_el3, x0

    adr x0, el2_entry
	msr elr_el3, x0

    eret

el2_entry:
	ldr x0, =SCTLR_EL2_VALUE_MMU_DISABLED
	msr sctlr_el2, x0

	/* The Execution state for EL1 is AArch64 */
	ldr x0, =HCR_HOST_NVHE_FLAGS
	msr hcr_el2, x0

	ldr x0, =SCTLR_EL1_VALUE_MMU_DISABLED
	msr sctlr_el1, x0

	ldr x0, =SPSR_EL1
	msr spsr_el2, x0

	adr x0, el1_entry
	msr elr_el2, x0

	eret

el1_entry:
    adr x0, bss_begin
	adr x1, bss_end
	sub x1, x1, x0
	bl memzero

    mov sp, #LOW_MEMORY	//set stack for C func running environment_4kb
	bl kernel_main      //start C program
	b proc_hang         //should never come here
