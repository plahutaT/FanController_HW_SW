#include "LCD.h"


/**
 * Increments the current cursor position by 1
 */
void LCD_cursor_increment(){
   
    /* Send the cursor increment command */
    LCD_write_command(LCD_CMD_CURSOR_INCREMENT);
}