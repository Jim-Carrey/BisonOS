#include "io.h"
#include "timer.h"
#include "printk.h"

static unsigned int val = NSEC_PER_SEC / DEFAULT_HZ;

static int generic_timer_init(void)
{
	asm volatile(
		"mov x0, #1\n"
		"msr cntp_ctl_el0, x0"
		:
		:
		: "memory");

	return 0;
}

int generic_timer_reset(unsigned int val)
{
	asm volatile(
		"msr cntp_tval_el0, %x[timer_val]"
		:
		: [timer_val] "r" (val)
		: "memory");

	return 0;
}

static void enable_timer_interrupt(void)
{
	writel(CNT_PNS_IRQ, CORE0_TIMER_IRQCNTL);
}

void timer_init(void)
{
	generic_timer_init();
	generic_timer_reset(val);

	enable_timer_interrupt();
}