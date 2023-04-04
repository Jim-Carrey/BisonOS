#define QEMU_VIRT_UART_BASE 0x09000000
#define QEMU_VIRT_UART_END (QEMU_VIRT_UART_BASE + 0x00001000)

typedef unsigned long long uint64_t;
typedef unsigned long size_t;


static inline void mmio_write(uint64_t reg, uint64_t data)
{
    *(volatile uint64_t*)reg = data;
}

void uart_put_char(unsigned char c)
{
    mmio_write(QEMU_VIRT_UART_BASE, c);
}

void uart_puts(const char *str)
{
    size_t i = 0;
    while(str[i] != '\0') {
    	uart_put_char((unsigned char)str[i]);
	i++;
    }
}

int kernel_main(int argc, char *argv[])
{
    uart_puts("hello, this is BisonOS by jim carrey!");
    while(1);
}
