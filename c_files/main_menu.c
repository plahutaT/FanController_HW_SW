#include "main_menu.h"
#include "eeprom.h"



void EnTimer5(void){
   
  PIR5bits.TMR5IF = 0;
  PIE5bits.TMR5IE = 1;
  
}

void DisTimer5(void){
  
  PIR5bits.TMR5IF = 0;
  PIE5bits.TMR5IE = 0;
  
}

void EnINT0(void) {

    INTCONbits.INT0IE = 1;

}

void DisINT0(void) {

    INTCONbits.INT0IE = 0;

}


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

/*    
void first_main_menu_func(void){
    
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
        Main_menu_F = 1;
        Main_menu2_F = 0;
        TicksM = 0;
        LCD_clear();
        
        // Zapisemo vrednost v eeprom  //
        //write_internall_eeprom(0x45, Ref_temp);
    }


}

*/
/*
void main_menu_func(void){
    
    uint8_t button_state = Get_Button_Press();
    static uint8_t first_entry = 1;
    
    if (first_entry) {
        
        LCD_cursor_set(1, 1);
        LCD_write_string("Menu:");
        __delay_ms(2000);
        first_entry = 0;
    }
    
    
    
    
    LCD_cursor_set(1, 1);
    LCD_write_string("L->24V");
    
    
    LCD_cursor_set(2, 1);
    LCD_write_string("R->230V");
    
    
    
    if(button_state & 1){
        DC_fan_F = 1;
    }
    else if(button_state & (1<<1)){
        DC_fan_F = 0;
    }
    
    if(button_state & 0x03){
        TicksM = multitaskTimer;
        
    }
    else if(multitaskTimer - TicksM >= 500 && TicksM){        // ce mini 5s brez pritiska grem ven, problem je bil da ni zaznalo button_stata ker deluje na padajoco fronto
        Main_menu_F = 0;
        TicksM = 0;
        first_entry = 1;
        LCD_clear();
        
        if (DC_fan_F){
                EnTimer5();
                DisINT0();
        }
        else if (!DC_fan_F){
            
            //if (DC_fan_running_F == 1) {
                
                DisTimer5();
                EnINT0();
                
                //count = 0;
                //debounce_count = 0;
                //multitaskTimer = 0;
                
                
                LCD_clear();
                LCD_cursor_set(1, 1);
                LCD_write_string("AC");
            //}
           
        }
        
        
        
        // Zapisemo vrednost v eeprom  //
        //write_internall_eeprom(0x45, Ref_temp);
    }


}

*/



void main_menu_func(void){
    
    
    static uint8_t first_entry = 1;
    static uint8_t enter_f = 0;
    
    /* flags:
     
     *  B1 = output_or_ref_f, 0 -> output, 1 -> ref
     *  B0 = scroll_f, 0 -> no scroll, 1 -> scroll   
     */
    static uint8_t flags = 0;
    
    
    
    if (first_entry) {
        
        LCD_cursor_set(1, 1);
        LCD_write_string("Menu:");
        __delay_ms(2000);
        first_entry = 0;
    }
    
    uint8_t button_state = Get_Button_Press();
    
    
    /*          
       
     * Firstly 
     * 
     * Button one is enter 
     * Button two is used for scrolling between parameters
     * 
     * Once you chose enter, you can modify the parameter value
     * 
     * Button one is -1 or left
     * Button two is +1 or right
     * If both buttons are pressed for 2s your entry 
     * ( or if both buttons are released)
     
     
     */
    
    if (enter_f == 0) {
        
        if(button_state & 1){
            enter_f = 1;
        }
        else if(button_state & (1<<1)){
            flags |= 0x01;
        }

        if(button_state & 0x03){
            TicksM = multitaskTimer;

        }

        if(flags & 0x01){

            flags ^= 0x02;
        }
    
    }
    else if (enter_f == 1) {
    
        
        
        if(button_state & 1){
            if(flags & 0x02){
                Ref_temp--;
            }
            else {
                DC_fan_F ^= 0x01;
            }
            
        }
        else if(button_state & (1<<1)){
            
            if(flags & 0x02){
                Ref_temp++;
            }
            else {
                DC_fan_F ^= 0x01;
            }
        }

        if(button_state & 0x03){
            
            TicksM = multitaskTimer;

        }
        
        if(multitaskTimer - TicksM >= 500 && TicksM){        // ce mini 5s brez pritiska grem ven, problem je bil da ni zaznalo button_stata ker deluje na padajoco fronto
            
            Main_menu_F = 0;
            TicksM = 0;
            flags = 0;
            first_entry = 1;
            enter_f = 0;

            if (DC_fan_F){
                
                EnTimer5();
                DisINT0();
            }
            else if (!DC_fan_F){

                

                DisTimer5();
                EnINT0();
                   
                

            }

            /* Zapisemo vrednost v eeprom  */
            //write_internall_eeprom(0x45, Ref_temp);
        }
        
        
    
    } 
    
    flags &= ~0x01;
    display_menu (flags);
    

}


void display_menu (uint8_t flags) {
    static prev_flags = 0;

    /* flags:
     
     *  B1 = output_or_ref_f, 0 -> output, 1 -> ref
     *  B0 = scroll_f, 0 -> no scroll, 1 -> scroll   
     */
    char buffer[10];
    
    
    if (prev_flags != flags) {
        LCD_clear();
    }
    
    
    if (flags & 0x02) {
    
        LCD_cursor_set(1, 1);
        LCD_write_string("REF:");
        LCD_cursor_set(2, 1);
        sprintf(buffer,"%d", Ref_temp);
        LCD_write_string(buffer);
    
    }
    else {
    
        LCD_cursor_set(1, 1);
        LCD_write_string("OUTPUT:");
    
        if (DC_fan_F){
            LCD_cursor_set(2, 1);
            LCD_write_string("DC");
        }
        else{
        
            LCD_cursor_set(2, 1);
            LCD_write_string("AC");
        }
    } 
    
    
    prev_flags = flags;




}


