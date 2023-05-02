/* 
 * File:   eeprom.h
 * Author: tilen
 *
 * Created on April 14, 2023, 8:55 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include <stdint.h>
#include <xc.h>

void write_internal_eeprom(uint8_t address, uint8_t data); 
uint8_t read_internal_eeprom(uint8_t address);

#endif	/* EEPROM_H */

