/*
 * power.cpp
 *
 * Created: 01/08/2022 10:07:59
 *  Author: marce
 */ 

#include "power.h"
#include "timer.h"
#include "pwm.h"

void power_init() {
	/*disable use clock to reduce energy consumption*/
	PRR = _bv(PRUSI);
}

void power_down() {
	/*in this mode CPU clock is disabled,
	  only external interrupt INT0 and WDT will wakeup CPU*/
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
}

void power_idle() {
	/*in this mode CPU clock is disabled too,
	  but the timer overflow, ADC complete read and INT0 can wakeup CPU*/
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();
}

void power_wkup() {
	/*point to CPU wakeup*/
	sleep_mode();
	sleep_disable();
}
