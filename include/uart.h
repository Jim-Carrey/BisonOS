#ifndef	_UART_H_
#define	_UART_H_

void uart_init(void);
char uart_recv(void);
void uart_send(char c);
void uart_send_string(char *str);

#define putchar uart_send

#endif  /*_UART_H_ */
