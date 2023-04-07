/*
 * asm.h
 */

#ifndef __ASM_H__
#define __ASM_H__

#ifndef  ALIGN
#define  ALIGN		.align 4,0x90
#define  ALIGN_STR	".align 4,0x90"
#endif

#define ENTRY(name) \
    .globl name; \
    ALIGN; \
    name:

#define END(name) \
    .size name, .-name

#define ENDPROC(name) \
    .type name, @function; \
    END(name)

#endif /* __ASM_H__ */
