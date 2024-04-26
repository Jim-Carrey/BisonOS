#ifndef _TRAPS_H_
#define _TRAPS_H_

#include "type.h"

/*
 * PSR bits
 */
#define PSR_MODE_EL0t	0x00000000
#define PSR_MODE_EL1t	0x00000004
#define PSR_MODE_EL1h	0x00000005
#define PSR_MODE_EL2t	0x00000008
#define PSR_MODE_EL2h	0x00000009
#define PSR_MODE_EL3t	0x0000000c
#define PSR_MODE_EL3h	0x0000000d
#define PSR_MODE_MASK	0x0000000f

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