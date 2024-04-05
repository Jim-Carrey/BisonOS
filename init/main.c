#include "printk.h"
#include "uart.h"

void kernel_main(void)
{
    uart_init();

    uart_send_string("hello, this is BisonOS!\r\n");

    printk("hello, this is BisonOS!\n");

    printk("copyright @jimcarrey\n");

    while (1);
		//uart_send(uart_recv());
}