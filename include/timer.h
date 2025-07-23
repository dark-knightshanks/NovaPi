#ifndef	_TIMER_H
#define	_TIMER_H

extern void timer_init ( void );
extern void handle_timer_irq ( void );
extern void delay_timer ( unsigned long );


#endif  /*_TIMER_H */