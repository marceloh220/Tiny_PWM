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
	
	/*configure gpios pins*/
	_pullup(_BT);
	_out(_OUT0);
	_out(_OUT1);
	
	/*test outputs in first power on*/
	for(uint8_t i = 0; i < 3; i++) {
		blink_out();
	}
	
	/*initialize peripherals*/
	power_init();
	pwm_init();
	adc_init();
	timer_init();
	wdt_enable(WDTO_1S);
	system_init();
	
    while (1) {
		
		/*process new sample*/
		adc_sample();
		
		/*pass setpoint to PWM output, shift left by 2 is the same as divide by 4
		  ADC has 10 bits but PWM has only 8, divide by 4 convert this resolution*/
		pwm_out0(adc_read(0)>>2);
		pwm_out1(adc_read(1)>>2);
		
		/*at final of sample processing cpu go to idle mode*/
		power_idle();
		power_wkup();
		
		/*WDT must be reset from time to time*/
		wdt_reset();
    
	}
}

