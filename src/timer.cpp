/*
	timer.cpp

	MIT License

	Copyright (c) 2022 Marcelo H Moraes

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

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
