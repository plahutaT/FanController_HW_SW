#include "LCD.h"


/**
 * Sends an 8-bit data (in 4-bit mode)\n
 * <STRONG>(!!!Meant for internal use only!!!)</STRONG>s
 * @param data: 8-bit data to be sent
 */
void LCD_write_data(char data){

    LCD_RS_LAT = 1; //Enter data mode
    
    /*---------- Load higher order 4-bits ----------*/
    LCD_D7_LAT = (data & 0b10000000) >> 7;
    LCD_D6_LAT = (data & 0b01000000) >> 6;
    LCD_D5_LAT = (data & 0b00100000) >> 5;
    LCD_D4_LAT = (data & 0b00010000) >> 4;
    
    /*---------- Send a clock pulse ----------*/
    LCD_pulse_clock();
    
    /*---------- Load lower order 4-bits ----------*/
    LCD_D7_LAT = (data & 0b00001000) >> 3;
    LCD_D6_LAT = (data & 0b00000100) >> 2;
    LCD_D5_LAT = (data & 0b00000010) >> 1;
    LCD_D4_LAT = (data & 0b00000001)     ;
    
    /*---------- Send a clock pulse ----------*/
    LCD_pulse_clock();
}