
void uart_puts(const char *str);

// entry.S jumps here in machine mode on stack0.
void start()
{
    uart_puts("hello, this is BisonOS by jim carrey!\n");
    uart_puts("risc-v architecture mechine!");
    while(1);
}