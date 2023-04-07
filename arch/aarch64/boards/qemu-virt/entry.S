/*
 * entry.S
 */

#include "asm.h"

.section ".text.boot"
ENTRY(_start)
    //disable Debug/Asynchronous/IRQ/FIQ interrupts
    mrs x0 , DAIF
    orr x0, x0, 0x3c0
    msr DAIF, x0

    ldr x21, = __end

    mrs x1, CurrentEL
    mov x1, x1, lsr #2
    cmp x1, #3			//in el3?
    bne not_in_el3
    bl clear_bss

not_in_el3:
    cmp x1, #2			//in el2?
    bne not_in_el2
    mrs x0, hcr_el2 		//Hypervisor Configuration Register
    //disable follow bits
    //[7:6] virtual irq/fiq physical
    //[5:3] serror/irq/fiq
    //[2]   stage2 translation 
    //[1]   set/way invalidation override
    //[0]   virtualization enable
    bic x0, x0, #0xff 
    msr hcr_el2, x0

    msr sp_el1, x21   		 //set el1 sp

    //enable CNTP for EL1
    mrs     x0, cnthctl_el2 	 //Counter-timer Hypervisor Control register
    orr     x0, x0, #3
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr

    //enable AArch64 in EL1
    mov     x0, #(1 << 31)  	 //AArch64
    orr     x0, x0, #(1 << 1)  	 //SWIO hardwired on Pi3
    msr     hcr_el2, x0
    mrs     x0, hcr_el2
    
    bl _disable_mmu

    //change execution level to EL1
    mov     x2, #0x3c4
    msr     spsr_el2, x2            // 1111000100
    eret

not_in_el2:
    cmp x1, #1	                  //in el1?
    bne in_el0
    mov sp, x21                   //set el1 sp
    
    bl _disable_mmu
    bl clear_bss

in_el0:
    wfe
    bl in_el0

clear_bss:
    ldr x0, =__bss_start
    ldr x1, =__bss_size
    mov x2, #0

bss_loop:
    cmp x0, x1
    str x2, [x0], #4
    blt bss_loop
    /*start c program*/
    bl kernel_main    
ENDPROC(_start)

ENTRY(_disable_mmu)
    //disable MMU I/D Cache
    //bit[0] : EL1/EL0 MMU
    //bit[2] : EL1/EL0 Data Cache
    //bit[12]: EL1/EL0 Instruct Cache
    dsb sy
    mrs x2, sctlr_el1
    mov x3, #0x1005
    bic x2, x2, x3
    msr sctlr_el1, x2
    isb
    ret
ENDPROC(_disable_mmu)
