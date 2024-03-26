#include "printk.h"
#include "uart.h"

void kernel_main(void)
{
    uart_init();

    printk("hello, this is BisonOS!\n");
    while(1);
}