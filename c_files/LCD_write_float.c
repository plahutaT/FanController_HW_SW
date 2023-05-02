#include "LCD.h"


/**
 * Writes a float variable to the current cursor location\n
 * (Negative numbers will be treated as positive!)
 * @param variable: Variable to be written
 * @param back_offset: If the offset is bigger than the total
 * digit count(including integer digits, float digits and 1 
 * more for the '.' character), the difference amount of 
 * empty spaces will be put before writing the variable\n
 * (Allows for right to left writing while keeping the first
 * digit stationary)\n
 * @param f_digit: How many digits of the fractional part to
 * be written\n
 * (Too high value will cause the variable to overflow!)
 */
void LCD_write_float(float variable, uint8_t left_offset, uint8_t f_digit){
    
    /*----- Calculate the left offset for the integer part.(-1 is for the '.' character) -----*/
    /*----- (Making sure that left offset doesn't wrap back to 255.) -----*/
    if( left_offset >= (f_digit+1) ){        
        left_offset = (left_offset-f_digit) - 1;
    }
    else{
        left_offset = 0;
    }
    
    /*----- Turn negative numbers into positive -----*/
    if(variable < 0) variable *= -1;

    /*----- Seperate the integer and fractional parts using "modff" from "math.h" -----*/
    float integer;                           //Define a variable for the integer part
    float fractional;                        //Define a variable for the fractional part
    fractional = modff(variable, &integer);  //Seperate the integer and fractional parts

    /*----- Write the integer part -----*/
    LCD_write_variable( (int32_t)integer, left_offset );  //Write the integer part with given offset    
    LCD_write_char('.');                                  //Place a dot before the fractional part
    
    /*----- Write the fractional part -----*/
    for(uint8_t i=0 ; i < f_digit ; i++){                           //Limit the fractional digits
        fractional *= 10;                                           //Shift fraction to left
        LCD_write_data( (uint8_t)((int32_t)fractional%10 + '0') );  //Write the digit(with character 0 as offset)
    }
}