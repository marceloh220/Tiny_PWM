/*
 * button.cpp
 *
 * Created: 01/08/2022 18:58:04
 *  Author: marce
 */

#include "button.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
#include "power.h"

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
