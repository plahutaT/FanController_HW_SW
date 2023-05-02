#include "LCD.h"


/**
 * Resets the shifting and resets cursor to 1,1
 */
void LCD_shift_reset(){
    
    /* Send the return home command(automatically sets cursor to 1,1) */
    LCD_write_command(LCD_CMD_RETURN_HOME);
    
    /* Give the extended delay needed by the longer command */
    __delay_us(LCD_BUSY_DELAY_EXTENDED);
}