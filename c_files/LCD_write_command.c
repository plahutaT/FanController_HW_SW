#include "LCD.h"


/**
 * Sends an 8-bit command (in 4-bit mode)\n
 * <STRONG>(!!!Meant for internal use only!!!)</STRONG>
 * @param command: 8-bit command to be sent
 */
void LCD_write_command(char command){
    
    LCD_RS_LAT = 0; //Enter command mode
    
    /*---------- Load higher order 4-bits ----------*/
    LCD_D7_LAT = (command & 0b10000000) >> 7;
    LCD_D6_LAT = (command & 0b01000000) >> 6;
    LCD_D5_LAT = (command & 0b00100000) >> 5;
    LCD_D4_LAT = (command & 0b00010000) >> 4;
    
    /*---------- Send a clock pulse ----------*/
    LCD_pulse_clock();
    
    /*---------- Load lower order 4-bits ----------*/
    LCD_D7_LAT = (command & 0b00001000) >> 3;
    LCD_D6_LAT = (command & 0b00000100) >> 2;
    LCD_D5_LAT = (command & 0b00000010) >> 1;
    LCD_D4_LAT = (command & 0b00000001)     ;
    
    /*---------- Send a clock pulse ----------*/
    LCD_pulse_clock();
}