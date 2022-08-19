/*
	power.cpp

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
