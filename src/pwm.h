/*
	pwm.h

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


#ifndef PWM_H_
#define PWM_H_

#include "defines.h"

#define pwm_out0_enable()   {TCCR0A |= _bv(COM0A1);}
#define pwm_out1_enable()   {TCCR0A |= _bv(COM0B1);}
#define pwm_out0_disable()  {TCCR0A &= ~_bv(COM0A1);}
#define pwm_out1_disable()  {TCCR0A &= ~_bv(COM0B1);}
#define pwm_mode() {pwm_state = (pwm_state+1)&3;}

typedef enum {
	PWM_MODE_OFF,
	PWM_MODE_OUT0,
	PWM_MODE_OUT1,
	PWM_MODE_BOTH
} pwm_mode_t;

extern uint8_t pwm_state;

void pwm_init();
void pwm_out0(uint8_t value);
void pwm_out1(uint8_t value);

#endif /* PWM_H_ */
