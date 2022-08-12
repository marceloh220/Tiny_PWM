/*
 * timer.cpp
 *
 * Created: 02/08/2022 19:24:45
 *  Author: marce
 */ 

#include "timer.h"
#include "adc.h"
#include "button.h"

/*Overflow each 16ms*/
ISR(TIMER1_OVF_vect) {
	static uint8_t timer_overflow = 0;
	timer_overflow++;
	if(timer_overflow == 7) {
		/*each 16 x 7 = 113ms*/
		timer_overflow = 0;
		if (_read(_BT)) { 
			/*if button release, enable interrupt INT0 to read again*/
			int_enable();
		}
	}
	/*start the adc to read a new channel*/
	adc_enable();
}

void timer_init() {
	TIMSK = _bv(TOIE1); /*enable timer overflow interrupt*/
	timer_enable(); /*start the timer*/
}
