/*
 * e2prom.cpp
 *
 * Created: 02/08/2022 19:48:33
 *  Author: marce
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
