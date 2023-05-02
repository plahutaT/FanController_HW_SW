#include "LCD.h"


/**
 * Writes an integer variable to the current cursor location(max. 32-bit)\n
 * (Negative numbers will be treated as positive!)
 * @param variable: Variable to be written
 * @param back_offset: If the offset is bigger than the
 * total digit count, the difference amount of empty spaces
 * will be put before writing the variable\n
 * (Allows for right to left writing while keeping the first
 * digit stationary)\n
 * (Cursor will still point to the right side of the variable)\n
 * (Leave as 0 if you want the variable to be written as is)
 */
void LCD_write_variable(int32_t variable, uint8_t left_offset){
    
    int32_t temp_variable;  //Temporary variable to work on
    uint8_t digits = 0;     //Variable to hold the number of total digits
    
    /*----- Turn negative numbers into positive -----*/
    if(variable < 0) variable *= -1;
    
    /*---------- Calculate the total digits ----------*/
    temp_variable = variable;          //Copy the variable
    while(1){                          //...
        digits++;                      //Increment the digit(do first since even 0 will have 1 digit)
        if(temp_variable < 10) break;  //If the number has 1 digit left, break
        temp_variable /= 10;           //Shift the number to the right
    }
    
    /*---------- Give the offset before writing the variable ----------*/
    while(1){
        if(left_offset <= digits) break;  //If the offset is equal to digits *or less*, break
        LCD_write_data(' ');              //Put an empty space
        left_offset--;                    //Decrement the offset
    }
    
    /*---------- Write the variable on screen ----------*/
    while(1){
        temp_variable = variable;                    //Copy/re-copy the variable
        for(uint8_t i = 1 ; i < digits ; i++){       //Shift the temporary variable *digits* times
            temp_variable /= 10;                     //...
        }                                            //...
        LCD_write_data( (temp_variable%10) + '0' );  //Write the digit(with character 0 as offset)
        digits --;                                   //Decrement the *digits*(to move onto next)
        if(digits == 0) break;                       //If *digits* reaches 0, break
    }
}