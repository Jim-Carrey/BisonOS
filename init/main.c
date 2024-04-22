#include "printk.h"
#include "uart.h"
#include "timer.h"
#include "irq.h"

void kernel_main(void)
{
    uart_init();

    uart_send_string("hello, this is BisonOS!\r\n");

    printk("hello, this is BisonOS!\n");

    printk("copyright @jimcarrey\n");

    timer_init();
    armv8_local_irq_enable();

    while (1);
		//uart_send(uart_recv());
}