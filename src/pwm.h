/*
 * pwm.h
 *
 * Created: 31/07/2022 18:28:47
 *  Author: marce
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
