/*
 * power.h
 *
 * Created: 01/08/2022 10:06:48
 *  Author: marce
 */ 


#ifndef POWER_H_
#define POWER_H_

#include "defines.h"

void power_init();
void power_down();
void power_idle();
void power_wkup();

#endif /* POWER_H_ */