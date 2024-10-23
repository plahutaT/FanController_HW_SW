/* 
 * File:   onewire.h
 * Author: tilen
 *
 * Created on March 8, 2023, 1:34 PM
 */

#ifndef ONEWIRE_H
#define	ONEWIRE_H

#include <stdint.h>

#define OWPORT PORTCbits.RC4
#define OWLAT LATCbits.LATC4
#define OWDIR TRISCbits.TRISC4
#define OWIN OWLAT = 1
#define OWOUT OWLAT = 0

#define OWPORT2 PORTCbits.RC5
#define OWLAT2 LATCbits.LATC5
#define OWDIR2 TRISCbits.TRISC5
#define OWIN2 OWLAT2 = 1
#define OWOUT2 OWLAT2 = 0

#define _XTAL_FREQ 16000000

extern volatile uint16_t count;



uint8_t Ow_reset(void);
void Ow_write_bit(uint8_t Bit);
void Ow_write_byte(uint8_t B);
uint8_t Ow_read_bit(void);
uint8_t Ow_read_byte(void);
uint16_t Read_temp_inside(void);
uint8_t Ow_reset2(void);
void Ow_write_bit2(uint8_t Bit);
void Ow_write_byte2(uint8_t B);
uint8_t Ow_read_bit2(void);
uint8_t Ow_read_byte2(void);
uint16_t Read_temp_outside(void);





/*
uint8_t ow_reset(uint8_t PIN);
uint16_t read_temp(uint8_t PIN);
void ow_write_bit(uint8_t PIN, uint8_t b);
uint8_t ow_read_bit(uint8_t PIN);
uint8_t ow_read_byte(uint8_t PIN);
void ow_write_byte(uint8_t PIN, uint8_t B);
*/

#endif	/* ONEWIRE_H */

