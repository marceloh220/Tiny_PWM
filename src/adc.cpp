/*
	adc.cpp
		
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

#include "adc.h"
#include "timer.h"

/*struct help in data organization*/

typedef struct {
	uint16_t value_raw;
	uint16_t value_filtered;
} adc_t;

typedef struct {
	uint16_t value[NUMBER_OF_SAMPLES]; /*old reads vector, number of samples is defined in defines.h*/
	uint8_t index; /*each channel have your index*/
	uint32_t absolute; /*the sum of each sample*/
} sample_t;

/*data to analog capture*/
#ifdef DUAL_CHANNEL
static adc_t adc[2] = {0, 0}; /*each channel have your own capture data*/
#else
static adc_t adc = {0, 0}; /*capture data*/
#endif
static const uint8_t adc_mux[2] = {_ADC_CH0, _ADC_CH1}; /*poll to convert channel data to channel to mux*/
static uint8_t adc_channel = 0; /*channel is change at each complete analog capture*/
static uint8_t analog_read_complete = 0;

/*this interrupt will happen in each complete ADC capture*/
ISR(ADC_vect) {
	
	/*save the read in respective channel variable and change mux to next channel to be read*/
#ifdef DUAL_CHANNEL
	adc[adc_channel].value_raw = ADC;
#else
	adc.value_raw = ADC;
#endif
	
	adc_disable(); /*the new read will be triggered by timer 1 overflow in timer.cpp*/
	analog_read_complete = 1;
#ifdef DUAL_CHANNEL
	/*change channel and mux, have only two channel so xor operation can be used*/
	adc_channel ^= 1;
	ADMUX = adc_mux[adc_channel];
#endif
}

/*this will happen when a new analog capture came from the ADC*/
void adc_sample() {

#ifdef DUAL_CHANNEL
	static sample_t sample[2] = { {0}, 0, 0}; /*each channel have its own sample pool*/
	
	if(analog_read_complete) { /*if the channel in mux change means new data in data raw*/
	
		analog_read_complete = 0;
		uint8_t channel = (adc_channel+1) & 1; /*get the channel read, if channel in mux is 0 it means a new data captured in channel 1*/
	
		/*in the moving average, the oldest sample is subtracted from the absolute value and the new sample is added*/
		sample[channel].absolute -= sample[channel].value[sample[channel].index];
		sample[channel].value[sample[channel].index] = adc[channel].value_raw;
		sample[channel].absolute += adc[channel].value_raw;
	
		/*the index is incremented and reseted if this hits the max value of samples*/
		sample[channel].index++;
		if(sample[channel].index == NUMBER_OF_SAMPLES) sample[channel].index = 0;
		
		/*save the filtered signal*/
		adc[channel].value_filtered = sample[channel].absolute / NUMBER_OF_SAMPLES;
	
	}
#else
	static sample_t sample = { {0}, 0, 0}; /*each channel have its own sample pool*/

	if(analog_read_complete) { /*new data in data raw*/

		analog_read_complete = 0;

		/*in the moving average, the oldest sample is subtracted from the absolute value and the new sample is added*/
		sample.absolute -= sample.value[sample.index];
		sample.value[sample.index] = adc.value_raw;
		sample.absolute += adc.value_raw;

		/*the index is incremented and reseted if this hits the max value of samples*/
		sample.index++;
		if(sample.index == NUMBER_OF_SAMPLES) sample.index = 0;

		/*save the filtered signal*/
		adc.value_filtered = sample.absolute / NUMBER_OF_SAMPLES;

	}
#endif
	
}

void adc_init() {

	/*disables digital buffer on these channels to reduce analog capture noise*/
	DIDR0 |= _bv(ADC2D)|_bv(ADC3D);
	
	/*configure mux to read first channel, the ADC start conversion occur at timer 1 overflow in timer.cpp file*/
	ADMUX = adc_mux[adc_channel];

}

/*return the filtered ADC value*/
uint16_t adc_read(uint8_t channel) {
#ifdef DUAL_CHANNEL
	return adc[channel].value_filtered;
#else
	return adc.value_filtered;
#endif
}
