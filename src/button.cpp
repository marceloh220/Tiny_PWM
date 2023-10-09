/*
	button.cpp

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

#include "button.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
#include "power.h"

#ifdef BUTTON_ENABLE
/*external interrupt INT0, configured to detect falling edge in button*/
ISR(INT0_vect) {
	
	int_disable(); /*disable the int0 to debounce,
					 this will be enabled again at timer 1 overflow interrupt in timer.cpp file*/
	
	pwm_mode(); /*change the pwm mode*/
	
	if (pwm_state == PWM_MODE_OUT0) {
		/*if in pwm mode 1 its means that a power off return happens
		  enable timer and WDT again */
		timer_enable();
		wdt_enable(WDTO_1S);
	}
	
	else if(pwm_state == PWM_MODE_OFF) {
		/*if pwm mode change to power off mode, disable all peripheral and power down*/
		wdt_disable(); /*WDT must be disabled to enter in power down, otherwise the CPU will be reseted*/
		timer_disable();
		adc_disable();
		pwm_out0_disable();
		pwm_out1_disable();
		_off(_OUT0);
		_off(_OUT1);
		do {
			/*wait the button be released, in normal circumstances don't use delay into an interrupt,
			  here everything will be power down and all peripheral are disabled anyway*/
			_delay_ms(500);
		} while(!_read(_BT));
		int_enable(); /*enable interrupt do power up the system*/
		power_down();
	}
	
}
#endif
