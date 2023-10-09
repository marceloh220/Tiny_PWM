/*
	pwm.cpp

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

#include "pwm.h"
#include "power.h"
#include "adc.h"
#include "timer.h"

/*
	PWM state
	Bit 0 output 0
	Bit 1 output 1
*/
#define pwm_stateRead(_bit) (pwm_state&_bv(_bit))		
uint8_t pwm_state = PWM_MODE_BOTH;

void pwm_init() {
	pwm_out0(0);
	pwm_out1(0);
	TCCR0A = PWM_MODE;;
	TCCR0B = PWM_PRESCALE;
}

void pwm_out0(uint8_t value) {
	static uint8_t changeoff = 0;
	static uint8_t old = 0;
	int diff = value > old ? value - old : old - value;
	if(!value || !pwm_stateRead(0)) {
		pwm_out0_disable();
		_off(_OUT0);
		changeoff = 1;
	} else {
		if(changeoff) {
			pwm_out0_enable();
			changeoff = 0;
		}
		if(diff < PWM_OUT_THRESHOLD) return;
		_OUT0_PWM = value;
	}
	old = value;
}

void pwm_out1(uint8_t value) {
	static uint8_t changeoff = 0;
	static uint8_t old = 0;
	int diff = value > old ? value - old : old - value;
	old = value;
	if(!value || !pwm_stateRead(1)) {
		pwm_out1_disable();
		_off(_OUT1);
		changeoff = 1;
	} else {
		if(changeoff) {
			pwm_out1_enable();
			changeoff = 0;
		}
		if(diff < PWM_OUT_THRESHOLD) return;
		_OUT1_PWM = value;
	}
	old = value;
}
