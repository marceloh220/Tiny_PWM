/*
 * controlLED.cpp
 *
 * Created: 31/07/2022 18:16:07
 * Author : marce
 */ 

#include "defines.h"
#include "power.h"
#include "pwm.h"
#include "adc.h"
#include "button.h"
#include "timer.h"

void blink_out() {
	_on(_OUT0);
	_on(_OUT1);
	_delay_ms(500);
	_off(_OUT0);
	_off(_OUT1);
	_delay_ms(500);
}

int main(void) {
	
	_pullup(_BT);
	_out(_OUT0);
	_out(_OUT1);
	
	for(uint8_t i = 0; i < 3; i++) {
		blink_out();
	}
	
	power_init();
	pwm_init();
	adc_init();
	timer_init();
	
	wdt_enable(WDTO_1S);
	system_init();
	
    while (1) {
		adc_sample();
		pwm_out0(adc_read(0)>>2);
		pwm_out1(adc_read(1)>>2);
		power_idle();
		power_wkup();
		wdt_reset();
    }
}

