/*
	controlLED.cpp

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

#include "defines.h"
#include "power.h"
#include "pwm.h"
#include "adc.h"
#include "button.h"
#include "timer.h"

#ifdef AUTO_TEST
void blink_out() {
	_on(_OUT0);
	_on(_OUT1);
	_delay_ms(500);
	_off(_OUT0);
	_off(_OUT1);
	_delay_ms(500);
}
#endif

int main(void) {
	
	/*configure gpios pins*/
	_pullup(_BT);
	_out(_OUT0);
	_out(_OUT1);
#ifdef AUTO_TEST
	/*test outputs in first power on*/
	for(uint8_t i = 0; i < 3; i++) {
		blink_out();
	}
#endif
	/*initialize peripherals*/
	power_init();
	pwm_init();
	adc_init();
	timer_init();
	//wdt_enable(WDTO_1S);
	system_init();
	
    while (1) {
		
		/*process new sample*/
		adc_sample();
		
		/*pass setpoint to PWM output, shift left by 2 is the same as divide by 4
		  ADC has 10 bits but PWM has only 8, divide by 4 convert this resolution*/
		pwm_out0(adc_read(0)>>2);
#ifdef DUAL_CHANNEL
		pwm_out1(adc_read(1)>>2);
#endif
		
		/*at final of sample processing cpu go to idle mode*/
		power_idle();
		power_wkup();
		
		/*WDT must be reset from time to time*/
		wdt_reset();
    
	}
}

