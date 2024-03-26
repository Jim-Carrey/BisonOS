#ifndef _SYSREGS_H
#define _SYSREGS_H

/*
 * SCR_EL3, Secure Configuration Register (EL3), Page 2648 of
 * AArch64-Reference-Manual.
 */

#define SCR_RESERVED (3 << 4)
#define SCR_RW (1 << 10)
#define SCR_NS (1 << 0)
#define SCR_VALUE (SCR_RESERVED | SCR_RW | SCR_NS)

/*
 * SPSR_EL3, Saved Program Status Register (EL3) Page 389 of
 * AArch64-Reference-Manual.
 */
#define SPSR_MASK_ALL (7 << 6)
#define SPSR_EL1h (5 << 0)
#define SPSR_EL2h (9 << 0)
#define SPSR_EL1 (SPSR_MASK_ALL | SPSR_EL1h)
#define SPSR_EL2 (SPSR_MASK_ALL | SPSR_EL2h)

/* Current Exception Level values, as contained in CurrentEL */
#define CurrentEL_EL1 (1 << 2)
#define CurrentEL_EL2 (2 << 2)
#define CurrentEL_EL3 (3 << 2)

#define SCTLR_EL2_VALUE_MMU_DISABLED 0
#define SCTLR_EL1_VALUE_MMU_DISABLED 0

/*
 * SCR_EL3, Secure Configuration Register (EL3), Page 2648 of
 * AArch64-Reference-Manual.
 */

#define SCR_RESERVED (3 << 4)
#define SCR_RW (1 << 10)
#define SCR_NS (1 << 0)
#define SCR_VALUE (SCR_RESERVED | SCR_RW | SCR_NS)

#endif
