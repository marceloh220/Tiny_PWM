/*
 * defines.h
 *
 * Created: 31/07/2022 18:16:38
 *  Author: marce
 *
 *
 *	Description:
 *		Are two channels of PWM control output, each one controlled by a potentiometer
 *		Are three modes:
 *			mode 0: The MCU is in power down and outputs is turn off
 *			mode 1: Only OUT0 is driven, the OUT1 is turn off
 *			mode 2: Only OUT1 is driven, the OUT0 is turn off
 *			mode 3(default): Both outputs is driven
 *	
 *	Identity of system:
 *		OUT1: PWM out 0 at PB0 pin
 *		OUT2: PWM out 1 at PB1 pin
 *		POT1: ADC channel 2 control PWM out at PB4 pin
 *		POT2: ADC channel 3 control PWM out at PB3 pin
 *		BTN0: INT0 interrupt to wakeup MCU and change modes
 *		
 *	Peripheral:
 *		The clock MCU is running at 1MHz
 *		The Brown-down detect programed at 4.5V
 *		The PWM is generated by Timer 0 at frequency of 488Hz and calculate by move average with number max of samples defined in SAMPLES
 *		Timer 1 generate the times to read the analog inputs with ADC each 16ms and debounce the button at 114ms
 *		The ADC read two analog inputs, the ADC complete ISR change between the two channels, each channel have frequency 30 samples/s 
 *		The button is read at falling edge by external interrupt INT0, a debounce time of 114ms verify if button is liberated.
 *      This button wakeup CPU from power down
 *      Sleep Power Down is active in mode 0
 *		Sleep IDLE is active in the end of each ADC read, sample process and control read, until the next ADC read time
 *
*/
#ifndef DEFINES_H_
#define DEFINES_H_

#include "avr/io.h"
#include "avr/eeprom.h"
#include "avr/interrupt.h"
#include "avr/sleep.h"
#include "avr/wdt.h"
#include "util/delay.h"
#include "inttypes.h"

#define _bv(_bit)	(1<<_bit)

#define _OUT0 PB0
#define _OUT1 PB1

#define _OUT1_PWM OCR0A
#define _OUT2_PWM OCR0B

#define _BT	PB2

#define _ADC_CH0	2
#define _ADC_CH1	3

/*number of samples in moving average, more samples means steady and smooth captures, but slower the changes*/
#define NUMBER_OF_SAMPLES		10

/*
	Fclk = 16MHz
	Fpwm = Fclk / 256 / prescaler
	default frequency pwm:
		1E6 / 256 / 8 = 488Hz
	
	Above 300Hz is good for the eyes, but to camera captures needs above 1KHz
	Controlled led must match frequency, using more speed may result in loss of control resolution
	Select one prescaler below
*/
//#define PWM_PRESCALE (_bv(CS00))				/*Fclk/1, 3.9KHz to 1MHz mcu clock, good for video recording but controller lost resolution*/
#define PWM_PRESCALE (_bv(CS01))				/*Fclk/8, 488Hz at 1MHz mcu clock, good for eyes but not good for video recording*/
//#define PWM_PRESCALE (_bv(CS01)|_bv(CS00))	/*Fclk/64, 61Hz at 1MHz mcu clock, in limit to be good*/
//#define PWM_PRESCALE (_bv(CS02))				/*Fclk/256, 15Hz at 1MHz mcu clock, not good at all*/
//#define PWM_PRESCALE (_bv(CS02)|_bv(CS00))	/*Fclk/1024, 3Hz at 1MHz mcu clock, definitely bad*/

#define _out(_pin)		{PORTB&=~_bv(_pin); DDRB|=_bv(_pin);}
#define _pullup(_pin)	{DDRB&=~_bv(_pin); PORTB|=_bv(_pin);}

#define _off(_pin)	(PORTB&=~_bv(_pin))
#define _on(_pin)	(PORTB|=_bv(_pin))

#define _read(_pin)	(PINB&_bv(_pin))

#define system_init() {sei();}

#endif /* DEFINES_H_ */