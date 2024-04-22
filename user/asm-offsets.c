#include "type.h"
#include "traps.h"

#define DEFINE(sym, val)         __asm__ volatile ("\n" #sym " %0 " #val::"i"(val))
#define OFFSET(sym, str, mem)    DEFINE(sym, offsetof(struct str, mem))

void create_asm_offset(void)
{
    DEFINE(SAVE_CONTEXT_SIZE, sizeof(struct excp_context));
    OFFSET(SAVE_X0, excp_context, user_regs.regs[0]);
    OFFSET(SAVE_X1, excp_context, user_regs.regs[1]);
    OFFSET(SAVE_X2, excp_context, user_regs.regs[2]);
    OFFSET(SAVE_X3, excp_context, user_regs.regs[3]);
    OFFSET(SAVE_X4, excp_context, user_regs.regs[4]);
    OFFSET(SAVE_X5, excp_context, user_regs.regs[5]);
    OFFSET(SAVE_X6, excp_context, user_regs.regs[6]);
    OFFSET(SAVE_X7, excp_context, user_regs.regs[7]);
    OFFSET(SAVE_X8, excp_context, user_regs.regs[8]);
    OFFSET(SAVE_X9, excp_context, user_regs.regs[9]);
    OFFSET(SAVE_X10, excp_context, user_regs.regs[10]);
    OFFSET(SAVE_X11, excp_context, user_regs.regs[11]);
    OFFSET(SAVE_X12, excp_context, user_regs.regs[12]);
    OFFSET(SAVE_X13, excp_context, user_regs.regs[13]);
    OFFSET(SAVE_X14, excp_context, user_regs.regs[14]);
    OFFSET(SAVE_X15, excp_context, user_regs.regs[15]);
    OFFSET(SAVE_X16, excp_context, user_regs.regs[16]);
    OFFSET(SAVE_X17, excp_context, user_regs.regs[17]);
    OFFSET(SAVE_X18, excp_context, user_regs.regs[18]);
    OFFSET(SAVE_X19, excp_context, user_regs.regs[19]);
    OFFSET(SAVE_X20, excp_context, user_regs.regs[20]);
    OFFSET(SAVE_X21, excp_context, user_regs.regs[21]);
    OFFSET(SAVE_X22, excp_context, user_regs.regs[22]);
    OFFSET(SAVE_X23, excp_context, user_regs.regs[23]);
    OFFSET(SAVE_X24, excp_context, user_regs.regs[24]);
    OFFSET(SAVE_X25, excp_context, user_regs.regs[25]);
    OFFSET(SAVE_X26, excp_context, user_regs.regs[26]);
    OFFSET(SAVE_X27, excp_context, user_regs.regs[27]);
    OFFSET(SAVE_X28, excp_context, user_regs.regs[28]);
    OFFSET(SAVE_FRAME, excp_context, user_regs.regs[29]);
    OFFSET(SAVE_LR, excp_context, user_regs.regs[30]);
    OFFSET(SAVE_ELR, excp_context, user_regs.elr);
    OFFSET(SAVE_ESR, excp_context, user_regs.esr);
    OFFSET(SAVE_PSTATE, excp_context, user_regs.pstate);
    OFFSET(SAVE_CALLNO, excp_context, callno);
    OFFSET(SAVE_TRAP_EL2, excp_context, trap_el2);
    OFFSET(SAVE_TRAP_MODE32, excp_context, trap_mode32);
}