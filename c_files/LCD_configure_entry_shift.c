#include "LCD.h"


/**
 * Enables/disables screen shift on a write command\n
 * (Screen will be shifted left when cursor is incrementing, shifted right otherwise)
 * @param state: 1 to enable, 0 to disable
 */
void LCD_configure_entry_shift(uint8_t state){
    
    /* Change the gobal entry mode variable accordingly */
    if(state){
        LCD_entry_mode |= 0b00000001;
    }
    else{
        LCD_entry_mode &= 0b11111110;
    }
    
    /* Send the new entry mode command */
    LCD_write_command(LCD_entry_mode);
}