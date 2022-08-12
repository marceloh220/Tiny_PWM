/*
 * adc.h
 *
 * Created: 31/07/2022 18:45:27
 *  Author: marce
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "defines.h"

#define adc_enable()	{ADCSRA = _bv(ADEN)|_bv(ADSC)|_bv(ADIE)|3;}
#define adc_disable()	{ADCSRA = 0;}

void adc_init();
void adc_sample();
uint16_t adc_read(uint8_t channel);

uint8_t timer();

#endif /* ADC_H_ */