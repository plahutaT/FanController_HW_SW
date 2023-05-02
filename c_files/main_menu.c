#include "main_menu.h"
#include "eeprom.h"


/****************************************************************************

Function:           void main_menu_func(void);
Input:              Void

Output:             Void

PreCondition:
Related Parameters:
Overview:           Funkcija hendla main menu kjer lahko uporabnik nastavi
                    referencno temperaturo 
                    Po 5 sek brez pritiskov gumbov pride do izhoda iz menija 
                    gremo nazaj v normalno delovanje                   


******************************************************************************/


void main_menu_func(void){
    
    uint8_t button_state = Get_Button_Press();
    static char buffer[10];
    
    LCD_cursor_set(1, 1);
    LCD_write_string("Menu:");
    LCD_cursor_set(2, 1);
    LCD_write_string("Ref:");
    sprintf(buffer,"%d", Ref_temp);
    LCD_write_string(buffer);
    
    if(button_state & 1){
        Ref_temp++;
    }
    else if(button_state & (1<<1)){
        Ref_temp--;
    }
    
    if(button_state & 0x03){
        TicksM = multitaskTimer;
        
    }
    else if(multitaskTimer - TicksM >= 500 && TicksM){        // ce mini 5s brez pritiska grem ven, problem je bil da ni zaznalo button_stata ker deluje na padajoco fronto
        Main_menu_F = 0;
        TicksM = 0;
        
        /* Zapisemo vrednost v eeprom  */
        
    }


}