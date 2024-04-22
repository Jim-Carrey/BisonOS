#ifndef _TRAPS_H_
#define _TRAPS_H_

#include "type.h"

struct excp_regs {
    /* save register 0 ~ register 30 */
    u64 regs[31];
    /* save the traps return address. */
    u64 elr;
    /* save exception syndrome, used to check exception information */
    u64 esr;
    /* save SPSR_ELx */
    u64 pstate;
};

struct excp_context {
    struct excp_regs user_regs;
    u64 callno;
    u64 trap_el2;
    u64 trap_mode32;
};

#endif /* _TRAPS_H_ */