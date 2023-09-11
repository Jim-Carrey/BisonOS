#include "memlayout.h"

typedef unsigned long long uint64_t;
typedef unsigned long size_t;


static inline void mmio_write(uint64_t reg, uint64_t data)
{
    *(volatile uint64_t*)reg = data;
}

void uart_put_char(unsigned char c)
{
    mmio_write(UART0, c);
}

void uart_puts(const char *str)
{
    size_t i = 0;
    while(str[i] != '\0') {
        uart_put_char((unsigned char)str[i]);
	i++;
    }
}