#include "eeprom.h"

void write_internal_eeprom(uint8_t address, uint8_t data) 
{
	//Write the address
	EEADR = address;
    //EEADRH = 0x00;

	//Write the data
	EEDATA = data;

	//Point to data memory not program memoty
	EECON1bits.EEPGD = 0;

	//Access data EEPROM memory
	EECON1bits.CFGS = 0;

	//Data write enable bit
	EECON1bits.WREN = 1;

	//Global interrupt disable 
	GIE = 0;

	//Write protection sequence
	EECON2 = 0x55;
	EECON2 = 0xAA;

	//Initiate write
	EECON1bits.WR = 1;

    //Wait till write is complete
	while (!PIR2bits.EEIF);

	//Disable the flag
	PIR2bits.EEIF = 0;
    
    //Global interrupt enable
	GIE = 1;
}

uint8_t read_internal_eeprom(uint8_t address)
{
	//Write the address, from where data has to be read
	EEADR = address;
    //EEADRH = 0x00;

	//Disable write cycles to data EEPROM
	EECON1bits.WREN = 0;

	//Point to data memory
	EECON1bits.EEPGD = 0;

	//Access data EEPROM memory
	EECON1bits.CFGS = 0;
	
	//Initiate read
	EECON1bits.RD = 1;

	//Data available in EEDATA register
	return EEDATA;
}
