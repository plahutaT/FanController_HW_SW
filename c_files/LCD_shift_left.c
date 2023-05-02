#include "LCD.h"


/**
 * Shifts the whole screen left by 1\n
 * (Shifting the screen also shifts the cursor locations!)\n
 * <STRONG>Note: Characters off-screen will be displayed on a different line!</STRONG>
 */
void LCD_shift_left(){
    
    /* Send the shift left command */
    LCD_write_command(LCD_CMD_SHIFT_LEFT);
}
