#include "config.h"
#include "onewire.h"
#include "builtins.h"
#include <xc.h>


/**
 * Drive bus low, delay 480 us.
 * Release bus, delay 70 us.
 * Sample bus: 0 = device(s) present, 1 = no device present
 * Delay 410 us.
 */


uint8_t ow_reset(void) {
    
    OWDIR = 0;   // setting the pin to output
    
    OWOUT;
    __delay_us(480); // wait for 480us+

    OWIN;
    __delay_us(70);
    
    //OWDIR = 1;   // setting the pin to input??

    uint8_t response = (OWPORT == 0);
    __delay_us(410);

    return response;
}

uint8_t ow_reset2(void) {
    
    OWDIR2 = 0;   // setting the pin to output
    
    OWOUT2;
    __delay_us(480); // wait for 480us+

    OWIN2;
    __delay_us(70);
    
    //OWDIR = 1;   // setting the pin to input??

    uint8_t response = (OWPORT2 == 0);
    __delay_us(410);

    return response;
}


/*
uint8_t ow_reset(uint8_t PIN) {
    
    TRISC &= ~(1<<PIN);   // setting the pin to output
    
    LATC &= ~(1<<PIN);
    __delay_us(480); // wait for 480us+

    LATC |= 1<<PIN;
    __delay_us(70);

    uint8_t response = ~PORTC & (1<<PIN);
    __delay_us(410);

    return response;
}
*/


/*
 * Drive bus low.
 * Write 1: delay 6 us. Release bus, delay 64 us.
 * Write 0: delay 60 us. Release bus, delay 10 us.
 */

void ow_write_bit(uint8_t b) {
    
    OWDIR = 0;   // setting the pin to output
    
    OWOUT;

    if (b) {
        __delay_us(6);
        OWIN;
        __delay_us(64);
    } else {
        __delay_us(60);
        OWIN;
        __delay_us(10);
    }
}

void ow_write_bit2(uint8_t b) {
    
    OWDIR2 = 0;   // setting the pin to output
    
    OWOUT2;

    if (b) {
        __delay_us(6);
        OWIN2;
        __delay_us(64);
    } else {
        __delay_us(60);
        OWIN2;
        __delay_us(10);
    }
}

/*
void ow_write_bit(uint8_t PIN, uint8_t b) {
    
    TRISC &= ~(1<<PIN);   // setting the pin to output
    
    LATC &= ~(1<<PIN);

    if (b) {
        __delay_us(6);
        LATC |= 1<<PIN;
        __delay_us(64);
    } else {
        __delay_us(60);
        LATC |= 1<<PIN;
        __delay_us(10);
    }
}
*/


/*
 * Drive bus low, delay 6 us.
 * Release bus, delay 9 us.
 * Sample bus to read bit from slave.
 * Delay 55 us.
*/ 


uint8_t ow_read_bit(void) {
    
    OWDIR = 0;   // setting the pin to output
    
    OWOUT;
    __delay_us(6);

    OWIN;
    OWDIR = 1;   // setting the pin to input
    
    __delay_us(9);

    uint8_t response = OWPORT;

    __delay_us(55);

    return response;
}

uint8_t ow_read_bit2(void) {
    
    OWDIR2 = 0;   // setting the pin to output
    
    OWOUT2;
    __delay_us(6);

    OWIN2;
    OWDIR2 = 1;   // setting the pin to input
    
    __delay_us(9);

    uint8_t response = OWPORT2;

    __delay_us(55);

    return response;
}


/*
uint8_t ow_read_bit(uint8_t PIN) {
    
    uint8_t response = 0;
    
    TRISC &= ~(1<<PIN);   // setting the pin to output
    
    LATC &= ~(1<<PIN);
    __delay_us(6);

    LATC |= 1<<PIN;
    TRISC |= 1<<PIN;   // setting the pin to input
    __delay_us(9);
    
   
    if(PORTC & (1 << PIN)){
        response = 1;
    }

    __delay_us(55);

    return response;
}
*/



uint8_t ow_read_byte() {
    
    uint8_t c, r = 0;

    for (c = 0; c < 8; c++) {
        if (ow_read_bit()) {
            r |= 1 << c;
        }
    }

    return r;
}


uint8_t ow_read_byte2() {
    
    uint8_t c, r = 0;

    for (c = 0; c < 8; c++) {
        if (ow_read_bit2()) {
            r |= 1 << c;
        }
    }

    return r;
}



/*
uint8_t ow_read_byte(uint8_t PIN) {
    
    uint8_t c, r = 0;

    for (c = 0; c < 8; c++) {
        if (ow_read_bit(PIN)) {
            r |= 1 << c;
        }
    }

    return r;
}
*/


void ow_write_byte(uint8_t B) {
    uint8_t c;

    for (c = 0; c < 8; c++) {
        ow_write_bit((B >> c) & 1);
    }
}

void ow_write_byte2(uint8_t B) {
    uint8_t c;

    for (c = 0; c < 8; c++) {
        ow_write_bit2((B >> c) & 1);
    }
}


/*
void ow_write_byte(uint8_t PIN, uint8_t B) {
    uint8_t c;

    for (c = 0; c < 8; c++) {
        ow_write_bit(PIN, (B >> c) & 1);
    }
}
*/


/****************************************************************************

Function:           uint8_t temp_measure_inside(void);
Input:              Void

Output:             uint16_t temperatura

PreCondition:
Related Parameters:
Overview:           funkcija uporabi funkcije one wire protokola
                    od senzorja dobi temperaturo 
                    vrne nazaj to temperaturo v uint16                     


******************************************************************************/


uint16_t read_temp_inside(){
    
        
    uint8_t TempH = 0;
    uint8_t TempL = 0;
    uint16_t temperatura = 0;
    static uint8_t iteracija_flag = 0;
         
        
    if(!iteracija_flag){     
        ow_reset(); // 'Reset command to initialize One-Wire
        ow_write_byte(0xCC); // 'Skip ROM Command
        ow_write_byte(0x44); // 'Convert_T command
        iteracija_flag = 1;
    }              
    //__delay_ms(800); // 'Provide delay for conversion
         
    if(count >= 80){              
        ow_reset(); // 'Reset command to initialize One-Wire
        ow_write_byte(0xCC); // 'Skip ROM Command
        ow_write_byte(0xBE); // 'Read Scratchpad Command
        TempL = ow_read_byte(); //Read Temperature low byte
        TempH = ow_read_byte(); //Read Temperature high byte
        temperatura |= TempH << 8;
        temperatura |= TempL;     // lahko ne  >> 1 pa gledam tudi ce je 0.5 stopinje
        iteracija_flag = 0;
        count = 0;
    }     

    
         
         
    return temperatura;
}

uint16_t read_temp_outside(){
    
        
    uint8_t TempH = 0;
    uint8_t TempL = 0;
    uint16_t temperatura = 0;
    static uint8_t iteracija_flag = 0;
         
        
    if(!iteracija_flag){     
        ow_reset2(); // 'Reset command to initialize One-Wire
        ow_write_byte2(0xCC); // 'Skip ROM Command
        ow_write_byte2(0x44); // 'Convert_T command
        iteracija_flag = 1;
        count = 0;
    }              
    //__delay_ms(800); // 'Provide delay for conversion
         
    if(count >= 80){              
        ow_reset2(); // 'Reset command to initialize One-Wire
        ow_write_byte2(0xCC); // 'Skip ROM Command
        ow_write_byte2(0xBE); // 'Read Scratchpad Command
        TempL = ow_read_byte2(); //Read Temperature low byte
        TempH = ow_read_byte2(); //Read Temperature high byte
        temperatura |= TempH << 8;
        temperatura |= TempL;     // lahko ne  >> 2 pa gledam tudi ce je 0.5 stopinje
        iteracija_flag = 0;
        count = 0;
    }     

   
         
         
    return temperatura;
}
/*
uint16_t read_temp(uint8_t PIN){
    
        
    uint8_t TempH = 0;
    uint8_t TempL = 0;
    uint16_t temperatura = 0;
   
         
        
         
    ow_reset(PIN); // 'Reset command to initialize One-Wire
    ow_write_byte(PIN,0xCC); // 'Skip ROM Command
    ow_write_byte(PIN,0x44); // 'Convert_T command
                  
    __delay_ms(800); // 'Provide delay for conversion
         
                  
    ow_reset(PIN); // 'Reset command to initialize One-Wire
    ow_write_byte(PIN,0xCC); // 'Skip ROM Command
    ow_write_byte(PIN,0xBE); // 'Read Scratchpad Command
    TempL = ow_read_byte(PIN); //Read Temperature low byte
    TempH = ow_read_byte(PIN); //Read Temperature high byte
         
    temperatura |= TempH << 8;
    temperatura |= TempL;     // lahko ne  >> 2 pa gledam tudi ce je 0.5 stopinje
         
         
    return temperatura;
}
*/

