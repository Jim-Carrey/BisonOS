#ifndef _IRQ_H_
#define _IRQ_H_

void armv8_local_irq_enable(void);
void armv8_local_irq_disable(void);
void handle_timer_irq(void);

#endif /* _IRQ_H_ */
