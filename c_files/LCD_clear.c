#include "LCD.h"


/**
 * Clears the whole screen and resets cursor to 1,1
 */
void LCD_clear(){
    
    /* Send the clear command(automatically sets cursor to 1,1) */
    LCD_write_command(LCD_CMD_CLEAR);
    
    /* Give the extended delay needed by the longer command */
    __delay_us(LCD_BUSY_DELAY_EXTENDED);
    
    /* Re-send the entry mode, otherwise clear command resets the id to increment */
    LCD_write_command(LCD_entry_mode);
}