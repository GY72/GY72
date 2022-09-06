
#ifndef __TIMER_H
#define	__TIMER_H

//Buzzer
#define  Enable_BUZ          SETBANK1;PWM1CON |= 0x80;SETBANK0
#define  Disable_BUZ         SETBANK1;PWM1CON &= 0x7F;SETBANK0

extern bit f_5ms;


void timerinit();

#endif