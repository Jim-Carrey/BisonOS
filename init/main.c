#include "type.h"
#include "io.h"
#include "printk.h"
#include "uart.h"
#include "timer.h"
#include "irq.h"
#include "mm.h"
#include "memory.h"
#include "sched.h"

extern char _bss[], _ebss[];

void kernel_thread(unsigned long arg)
{
	while (1) {
        delay(100000000);
        struct proc *p = (struct proc*)arg;
	      printk("%s : pid is %d\n", __func__, p->pid);
	}
}

void kernel_main(void)
{
    uart_init();

    uart_send_string("hello, this is BisonOS!\r\n");

    printk("hello, this is BisonOS!\n");

    printk("copyright @jimcarrey\n");

    mem_init((u64)_ebss, TOTAL_MEMORY);

    //timer_init();
    //armv8_local_irq_enable();

    int pid;

    pid = do_fork(PF_KTHREAD, (unsigned long)&kernel_thread, 0);
    if (pid < 0)
      printk("create thread fail\n");

    struct proc *next = g_proc[pid];

    switch_to(next);

    while (1);
		//uart_send(uart_recv());
}