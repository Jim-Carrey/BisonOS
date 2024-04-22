#include "io.h"
#include "timer.h"
#include "printk.h"

static unsigned int val = NSEC_PER_SEC / DEFAULT_HZ;

void armv8_local_irq_enable(void)
{
	asm volatile(
		"msr	daifclr, #2"
		:
		:
		: "memory");
}

void armv8_local_irq_disable(void)
{
	asm volatile(
		"msr	daifset, #2"
		:
		:
		: "memory");
}

void handle_timer_irq(void)
{
	generic_timer_reset(val);
	printk("Core0 Timer interrupt received\r\n");
}

void irq_handle(void)
{
	unsigned int irq = readl(CORE0_IRQ_SOURCE);

	switch (irq) {
	case (CNT_PNS_IRQ):
		handle_timer_irq();
		break;
	default:
		printk("Unknown pending irq: %x\r\n", irq);
	}
}