#include "LCD.h"


/**
 * Decrements the current cursor position by 1
 */
void LCD_cursor_decrement(){
   
    /* Send the cursor decrement command */
    LCD_write_command(LCD_CMD_CURSOR_DECREMENT);
}