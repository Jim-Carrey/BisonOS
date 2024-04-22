#ifndef _TIMER_H_
#define _TIMER_H_

#include "base.h"

// Timers interrupt control registers
#define CORE0_TIMER_IRQCNTL (ARM_LOCAL_PERIPHERALS + 0x40)
#define CORE1_TIMER_IRQCNTL (ARM_LOCAL_PERIPHERALS + 0x44)
#define CORE2_TIMER_IRQCNTL (ARM_LOCAL_PERIPHERALS + 0x48)
#define CORE3_TIMER_IRQCNTL (ARM_LOCAL_PERIPHERALS + 0x4C)

// Where to route timer interrupt to, IRQ/FIQ
// Setting both the IRQ and FIQ bit gives an FIQ
#define TIMER0_IRQ 0x01
#define TIMER1_IRQ 0x02
#define TIMER2_IRQ 0x04
#define TIMER3_IRQ 0x08
#define TIMER0_FIQ 0x10
#define TIMER1_FIQ 0x20
#define TIMER2_FIQ 0x40
#define TIMER3_FIQ 0x80

/* Secure Physical Timer Event for IRQ */
#define CNT_PS_IRQ (1 << 0)
/* Nonsecure Physical Timer Event for IRQ */
#define CNT_PNS_IRQ (1 << 1)
/* Hypervisor Physical Timer Event for IRQ */
#define CNT_HP_IRQ (1 << 2)
/* Virtual Timer Event for IRQ */
#define CNT_V_IRQ (1 << 3)
/* Secure Physical Timer Event for FIQ */
#define CNT_PS_IRQ_FIQ (1 << 4)
/* Nonsecure Physical Timer Event for FIQ */
#define CNT_PNS_IRQ_FIQ (1 << 5)
/* Hypervisor Physical Timer Event for FIQ */
#define CNT_HP_IRQ_FIQ (1 << 6)
/* Virtual Timer Event for FIQ */
#define CNT_V_IRQ_FIQ (1 << 7)

// IRQ & FIQ source registers
#define CORE0_IRQ_SOURCE (ARM_LOCAL_PERIPHERALS + 0x60)
#define CORE1_IRQ_SOURCE (ARM_LOCAL_PERIPHERALS + 0x64)
#define CORE2_IRQ_SOURCE (ARM_LOCAL_PERIPHERALS + 0x68)
#define CORE3_IRQ_SOURCE (ARM_LOCAL_PERIPHERALS + 0x6C)

#define CORE0_FIQ_SOURCE (ARM_LOCAL_PERIPHERALS + 0x70)
#define CORE1_FIQ_SOURCE (ARM_LOCAL_PERIPHERALS + 0x74)
#define CORE2_FIQ_SOURCE (ARM_LOCAL_PERIPHERALS + 0x78)
#define CORE3_FIQ_SOURCE (ARM_LOCAL_PERIPHERALS + 0x7C)

/* Parameters used to convert the timespec values: */
#define MSEC_PER_SEC	1000L
#define USEC_PER_MSEC	1000L
#define NSEC_PER_USEC	1000L
#define NSEC_PER_MSEC	1000000L
#define USEC_PER_SEC	1000000L
#define NSEC_PER_SEC	1000000000L

# define DEFAULT_HZ	250 /* Internal kernel timer frequency */

void timer_init(void);
int generic_timer_reset(unsigned int val);

#endif /* _TIMER_H_ */