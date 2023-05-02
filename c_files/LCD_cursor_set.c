#include "LCD.h"


/**
 * Sets the cursor location
 * @param row: Row position(1-4)
 * @param column: Column position(1-20)
 */
void LCD_cursor_set(uint8_t row, uint8_t column){

   /* Offset the column address with the corresponding row */
    if(row == 1) column += LCD_CMD_DDRAM_LINE_1;
    if(row == 2) column += LCD_CMD_DDRAM_LINE_2;
    if(row == 3) column += LCD_CMD_DDRAM_LINE_3;
    if(row == 4) column += LCD_CMD_DDRAM_LINE_4;
   
   /* Set the cursor location with the new address */
   LCD_write_command(column);
}