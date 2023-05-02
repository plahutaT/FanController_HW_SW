#include "LCD.h"


/**
 * Writes an ASCII character to the current cursor location
 * @param character: Character to be written
 */
void LCD_write_char(char character){
   
    /* Write the character */
    LCD_write_data(character);
}