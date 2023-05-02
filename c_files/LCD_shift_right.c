#include "LCD.h"


/**
 * Shifts the whole screen right by 1\n
 * (Shifting the screen also shifts the cursor locations!)\n
 * <STRONG>Note: Characters off-screen will be displayed on a different line!</STRONG>
 */
void LCD_shift_right(){
    
    /* Send the shift right command */
    LCD_write_command(LCD_CMD_SHIFT_RIGHT);
}
