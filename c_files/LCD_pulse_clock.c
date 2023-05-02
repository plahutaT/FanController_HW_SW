#include "LCD.h"


/**
 * Pulses the clock line of LCD\n
 * <STRONG>(!!!Meant for internal use only!!!)</STRONG>
 */
void LCD_pulse_clock(){
  
  LCD_EN_LAT = 1;              //Set the "EN" pin
  __delay_us(LCD_BUSY_DELAY);  //Give the required delay
  LCD_EN_LAT = 0;              //Clear the "EN" pin
}