/*
 * timer.h
 *
 * Created: 02/08/2022 19:25:01
 *  Author: marce
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "defines.h"

//F_CPU = 1E6
//T = 1/F_CPU = 1us
//Overflow of timer in T/256/64 = ~16ms

#define timer_disable() {TCCR1 = 0;}
#define timer_enable()	{TCNT1 = 0; TCCR1 = 0x07;}

void timer_init();

#endif /* TIMER_H_ */