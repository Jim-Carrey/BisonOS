// entry.S jumps here in machine mode on stack0.
void start()
{
    uart_puts("risc-v architecture mechine!");
    uart_puts("hello, this is BisonOS by jim carrey!");
    while(1);
}