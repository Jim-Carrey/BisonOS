.section ".text.boot"

.global _start
_start:
    mrs x0 , DAIF
    orr x0, x0, 0x3c0
    msr DAIF, x0

    ldr x1, =__end
    mov sp, x1

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
