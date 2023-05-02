#include "LCD.h"


/**
 * Enables/disables character display on screen\n
 * (The LCD will still work and you can still do write operations,
 * only the characters will/won't be displayed)
 * @param state: 1 to enable, 0 to disable
 */
void LCD_configure_lcd_display(uint8_t state){
    
    /* Change the gobal display control variable accordingly */
    if(state){
        LCD_display_control |= 0b00000100;
    }
    else{
        LCD_display_control &= 0b11111011;
    }
    
    /* Send the new display control command */
    LCD_write_command(LCD_display_control);
}