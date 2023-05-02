#include "LCD.h"


/**
 * Turns on/off the line displayed below characters on cursor location  
 * @param state: 1 to turn on, 0 to turn off
 */
void LCD_configure_cursor_display(uint8_t state){
    
    /* Change the gobal display control variable accordingly */
    if(state){
        LCD_display_control |= 0b00000010;
    }
    else{
        LCD_display_control &= 0b11111101;
    }
    
    /* Send the new display control command */
    LCD_write_command(LCD_display_control);
}