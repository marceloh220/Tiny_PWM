/*
 * e2prom.h
 *
 * Created: 02/08/2022 19:48:20
 *  Author: marce
 */ 


#ifndef E2PROM_H_
#define E2PROM_H_

#include "defines.h"

void e2prom_write(uint16_t addr, uint8_t value);
uint8_t e2prom_read(uint16_t addr);

void mode_save(uint8_t mode);
uint8_t mode_restore();

#endif /* E2PROM_H_ */