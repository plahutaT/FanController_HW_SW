#include "LCD.h"


/**
 * Configures if the cursor increments or decrements on a write command
 * @param state: 1 to increment, 0 to decrement
 */
void LCD_configure_entry_id(uint8_t state){
    
    /* Change the gobal entry mode variable accordingly */
    if(state){
        LCD_entry_mode |= 0b00000010;
    }
    else{
        LCD_entry_mode &= 0b11111101;
    }
    
    /* Send the new entry mode command */
    LCD_write_command(LCD_entry_mode);
}