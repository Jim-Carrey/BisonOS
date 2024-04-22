#include "asm-offsets.h"

#define BAD_SYNC        0
#define BAD_IRQ         1
#define BAD_FIQ         2
#define BAD_ERROR       3

/*
   vector table entry
   每个表项是128字节， align 7表示128字节对齐
 */
	.macro vtentry label
	.align 7
	b \label
	.endm

/*
   处理无效的异常向量
 */
	.macro inv_entry el, reason
	kernel_entry el
	mov x0, sp
	mov x1, #\reason
	mrs x2, esr_el1
	b bad_mode
	.endm

/*
   保存异常发生时候的上下文

   保存x0~x29, x30（lr）, elr, esr, spsr保存到栈中
 */
	.macro kernel_entry el
	/*
	   SP指向了栈底, SAVE_CONTEXT_SIZE 表示一个栈框的大小.
	   定义一个struct excp_regs 来保存处理器发生异常时的上下文.
	 */
	sub sp, sp, #SAVE_CONTEXT_SIZE

	/*
	   保存通用寄存器x0~x29到栈框里excp_regs->x0~x29
	 */
	sub     sp, sp, #SAVE_CONTEXT_SIZE
    stp     x0, x1, [sp, #SAVE_X0]
    stp     x2, x3, [sp, #SAVE_X2]
    stp     x4, x5, [sp, #SAVE_X4]
    stp     x6, x7, [sp, #SAVE_X6]
    stp     x8, x9, [sp, #SAVE_X8]
    stp     x10, x11, [sp, #SAVE_X10]
    stp     x12, x13, [sp, #SAVE_X12]
    stp     x14, x15, [sp, #SAVE_X14]
    stp     x16, x17, [sp, #SAVE_X16]
    stp     x18, x19, [sp, #SAVE_X18]
    stp     x20, x21, [sp, #SAVE_X20]
    stp     x22, x23, [sp, #SAVE_X22]
    stp     x24, x25, [sp, #SAVE_X24]
    stp     x26, x27, [sp, #SAVE_X26]
    stp     x28, x29, [sp, #SAVE_X28]

	mrs     x22, elr_el1
	mrs     x23, esr_el1
	mrs     x24, spsr_el1

	/* 把lr保存到excp_regs->lr, 把elr_el1保存到excp_regs->elr位置 */
	stp     lr, x22, [sp, #SAVE_LR]
	/* 把esr_el1保存到excp_regs->esr中, 把spsr_elr保存到excp_regs->pstate中 */
	stp     x23, x24, [sp, #SAVE_ESR]
	.endm

/*
   恢复异常发生时保存下来的上下文
 */
	.macro kernel_exit el
	/* 从excp_regs->elr中恢复elr_el1,
	   从excp_regs->pstate中恢复spsr_el1
	 */
	ldr		x21, [sp, #SAVE_ELR]			// load ELR
	ldr     x22, [sp, #SAVE_PSTATE]         // load SPSR
	msr     elr_el1, x21                    // set up the return data
	msr     spsr_el1, x22

	ldp     x0, x1, [sp, #SAVE_X0]
	ldp     x2, x3, [sp, #SAVE_X2]
    ldp     x4, x5, [sp, #SAVE_X4]
    ldp     x6, x7, [sp, #SAVE_X6]
    ldp     x8, x9, [sp, #SAVE_X8]
    ldp     x10, x11, [sp, #SAVE_X10]
    ldp     x12, x13, [sp, #SAVE_X12]
    ldp     x14, x15, [sp, #SAVE_X14]
    ldp     x16, x17, [sp, #SAVE_X16]
    ldp     x18, x19, [sp, #SAVE_X18]
    ldp     x20, x21, [sp, #SAVE_X20]
    ldp     x22, x23, [sp, #SAVE_X22]
    ldp     x24, x25, [sp, #SAVE_X24]
    ldp     x26, x27, [sp, #SAVE_X26]
    ldp     x28, x29, [sp, #SAVE_X28]

	/* 从excp_regs->lr中恢复lr*/
	ldr     lr, [sp, #SAVE_LR]
	add     sp, sp, #SAVE_CONTEXT_SIZE      // restore sp
	eret                                    // return to kernel
	.endm


/*
 * Vector Table
 *
 * ARM64的异常向量表一共占用2048个字节
 * 分成4组，每组4个表项，每个表项占128字节
 * 参见ARMv8 spec v8.6第D1.10节
 * align 11表示2048字节对齐
 */
.global vectors
.align 11
vectors:
	/* Current EL with SP0
	   当前系统运行在EL1时使用EL0的栈指针SP
	   这是一种异常错误的类型
	 */
	vtentry el1_sync_invalid
	vtentry el1_irq_invalid
	vtentry el1_fiq_invalid
	vtentry el1_error_invalid

	/* Current EL with SPx
	   当前系统运行在EL1时使用EL1的栈指针SP
	   这说明系统在内核态发生了异常

	   Note: 我们暂时只实现IRQ中断
	 */
	vtentry el1_sync_invalid
	vtentry el1_irq
	vtentry el1_fiq_invalid
	vtentry el1_error_invalid

	/* Lower EL using AArch64
	   在用户态的aarch64的程序发生了异常
	 */
	vtentry el0_sync_invalid
	vtentry el0_irq_invalid
	vtentry el0_fiq_invalid
	vtentry el0_error_invalid

	/* Lower EL using AArch32
	   在用户态的aarch32的程序发生了异常
	 */
	vtentry el0_sync_invalid
	vtentry el0_irq_invalid
	vtentry el0_fiq_invalid
	vtentry el0_error_invalid

el1_sync_invalid:
	inv_entry 1, BAD_SYNC
el1_irq_invalid:
	inv_entry 1, BAD_IRQ
el1_fiq_invalid:
	inv_entry 1, BAD_FIQ
el1_error_invalid:
	inv_entry 1, BAD_ERROR
el0_sync_invalid:
	inv_entry 0, BAD_SYNC
el0_irq_invalid:
	inv_entry 0, BAD_IRQ
el0_fiq_invalid:
	inv_entry 0, BAD_FIQ
el0_error_invalid:
	inv_entry 0, BAD_ERROR

el1_irq:
	kernel_entry 1
	bl irq_handle
	kernel_exit 1
