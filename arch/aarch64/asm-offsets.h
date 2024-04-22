#ifndef _ASM_OFFSETS_H_
#define _ASM_OFFSETS_H_

#define SAVE_CONTEXT_SIZE 0x128 /* sizeof(struct excp_context) */
#define SAVE_X0           0x0   /* OFFSETOF(struct excp_context, user_regs.regs[0]) */
#define SAVE_X1           0x8   /* OFFSETOF(struct excp_context, user_regs.regs[1]) */
#define SAVE_X2           0x10  /* OFFSETOF(struct excp_context, user_regs.regs[2]) */
#define SAVE_X3           0x18  /* OFFSETOF(struct excp_context, user_regs.regs[3]) */
#define SAVE_X4           0x20  /* OFFSETOF(struct excp_context, user_regs.regs[4]) */
#define SAVE_X5           0x28  /* OFFSETOF(struct excp_context, user_regs.regs[5]) */
#define SAVE_X6           0x30  /* OFFSETOF(struct excp_context, user_regs.regs[6]) */
#define SAVE_X7           0x38  /* OFFSETOF(struct excp_context, user_regs.regs[7]) */
#define SAVE_X8           0x40  /* OFFSETOF(struct excp_context, user_regs.regs[8]) */
#define SAVE_X9           0x48  /* OFFSETOF(struct excp_context, user_regs.regs[9]) */
#define SAVE_X10          0x50  /* OFFSETOF(struct excp_context, user_regs.regs[10]) */
#define SAVE_X11          0x58  /* OFFSETOF(struct excp_context, user_regs.regs[11]) */
#define SAVE_X12          0x60  /* OFFSETOF(struct excp_context, user_regs.regs[12]) */
#define SAVE_X13          0x68  /* OFFSETOF(struct excp_context, user_regs.regs[13]) */
#define SAVE_X14          0x70  /* OFFSETOF(struct excp_context, user_regs.regs[14]) */
#define SAVE_X15          0x78  /* OFFSETOF(struct excp_context, user_regs.regs[15]) */
#define SAVE_X16          0x80  /* OFFSETOF(struct excp_context, user_regs.regs[16]) */
#define SAVE_X17          0x88  /* OFFSETOF(struct excp_context, user_regs.regs[17]) */
#define SAVE_X18          0x90  /* OFFSETOF(struct excp_context, user_regs.regs[18]) */
#define SAVE_X19          0x98  /* OFFSETOF(struct excp_context, user_regs.regs[19]) */
#define SAVE_X20          0xa0  /* OFFSETOF(struct excp_context, user_regs.regs[20]) */
#define SAVE_X21          0xa8  /* OFFSETOF(struct excp_context, user_regs.regs[21]) */
#define SAVE_X22          0xb0  /* OFFSETOF(struct excp_context, user_regs.regs[22]) */
#define SAVE_X23          0xb8  /* OFFSETOF(struct excp_context, user_regs.regs[23]) */
#define SAVE_X24          0xc0  /* OFFSETOF(struct excp_context, user_regs.regs[24]) */
#define SAVE_X25          0xc8  /* OFFSETOF(struct excp_context, user_regs.regs[25]) */
#define SAVE_X26          0xd0  /* OFFSETOF(struct excp_context, user_regs.regs[26]) */
#define SAVE_X27          0xd8  /* OFFSETOF(struct excp_context, user_regs.regs[27]) */
#define SAVE_X28          0xe0  /* OFFSETOF(struct excp_context, user_regs.regs[28]) */
#define SAVE_FRAME        0xe8  /* OFFSETOF(struct excp_context, user_regs.regs[29]) */
#define SAVE_LR           0xf0  /* OFFSETOF(struct excp_context, user_regs.regs[30]) */
#define SAVE_ELR          0xf8  /* OFFSETOF(struct excp_context, user_regs.elr) */
#define SAVE_ESR          0x100 /* OFFSETOF(struct excp_context, user_regs.esr) */
#define SAVE_PSTATE       0x108 /* OFFSETOF(struct excp_context, user_regs.pstate) */
#define SAVE_CALLNO       0x110 /* OFFSETOF(struct excp_context, callno) */
#define SAVE_TRAP_EL2     0x118 /* OFFSETOF(struct excp_context, trap_el2) */
#define SAVE_TRAP_MODE32  0x120 /* OFFSETOF(struct excp_context, trap_mode32) */

#endif