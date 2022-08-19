/*
	e2prom.cpp

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

#include "e2prom.h"

#define MODE_ADDR	0x01

void e2prom_write(uint16_t addr, uint8_t value) {
	uint8_t byteRead = eeprom_read_byte((uint8_t*) addr);
	if (value != byteRead) eeprom_write_byte ((uint8_t*) addr, value); 
}

uint8_t e2prom_read(uint16_t addr) {
	return eeprom_read_byte((uint8_t*)addr);
}

void mode_save(uint8_t mode) {
	e2prom_write(MODE_ADDR, mode);
}

uint8_t mode_restore() {
	return e2prom_read(MODE_ADDR);
}
