#include "LCD.h"


/**
 * Writes a string to the current cursor location\n
 * <STRONG>!!!The string has to be null terminated otherwise this function will fail or loop forever!!!</STRONG> 
 * @param *string: Character array that contains the string(max. 255 characters)
 */
void LCD_write_string(char *string){
   
    /* Write all characters one by one until you reach "NULL" */
    for(uint8_t i=0 ; string[i] != '\0' ; i++){
        LCD_write_data(string[i]);
    }
}