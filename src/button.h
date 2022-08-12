/*
 * button.h
 *
 * Created: 01/08/2022 10:52:26
 *  Author: marce
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "defines.h"

#define int_enable() {MCUCR |= _bv(ISC01); GIMSK |= _bv(INT0);}
#define int_disable() {MCUCR &= ~(_bv(ISC01)|_bv(ISC00)); GIMSK &= ~_bv(INT0);}

#endif /* BUTTON_H_ */