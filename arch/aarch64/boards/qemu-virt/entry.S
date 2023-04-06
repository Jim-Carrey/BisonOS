.section ".text.boot"

.global _start
_start:
    //disable Debug/Asynchronous/IRQ/FIQ interrupts
    mrs x0 , DAIF
    orr x0, x0, 0x3c0
    msr DAIF, x0

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
    
    ldr x4, = __end
    mov sp, x4

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
