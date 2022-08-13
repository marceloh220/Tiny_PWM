/*
 * pwm.cpp
 *
 * Created: 31/07/2022 18:30:20
 *  Author: marce
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
uint8_t pwm_state = PWM_MODE_OUT0;

void pwm_init() {
	pwm_out0(0);
	pwm_out1(0);
	TCCR0A = _bv(WGM01)|_bv(WGM00);
	TCCR0B = PWM_PRESCALE;
}

void pwm_out0(uint8_t value) {
	if(!value || !pwm_stateRead(0)) {
		pwm_out0_disable();
		_off(_OUT0);
	} else {
		pwm_out0_enable();
		_OUT1_PWM = value;
	}
}

void pwm_out1(uint8_t value) {
	if(!value || !pwm_stateRead(1)) {
		pwm_out1_disable();
		_off(_OUT1);
	} else {
		pwm_out1_enable();
		_OUT2_PWM = value;
	}
}
