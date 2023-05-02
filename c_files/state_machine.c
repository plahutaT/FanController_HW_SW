#include "state_machine.h"



uint8_t entry_state_driver(void){
    
    return ok;
}

/****************************************************************************

Function:           uint8_t temp_measure_inside_state_driver(void);
Input:              Void

Output:             Void

PreCondition:
Related Parameters:
Overview:           Funkcija hendla main menu kjer lahko uporabnik nastavi
                    referencno temperaturo 
                    Po 5 sek brez pritiskov gumbov pride do izhoda iz menija 
                    gremo nazaj v normalno delovanje                   


******************************************************************************/

uint8_t temp_measure_inside_state_driver(void){
    
    uint16_t temp = read_temp_inside();
    
    if(temp != 0){
        Temp = temp>>1;     // mores delit z 2 ker je 0.5 step
        return ok;
    }
    
    return repeat;
}


/****************************************************************************

Function:           uint8_t temp_measure_outside_state_driver(void);
Input:              Void

Output:             Void

PreCondition:
Related Parameters:
Overview:           Funkcija hendla main menu kjer lahko uporabnik nastavi
                    referencno temperaturo 
                    Po 5 sek brez pritiskov gumbov pride do izhoda iz menija 
                    gremo nazaj v normalno delovanje                   


******************************************************************************/


uint8_t temp_measure_outside_state_driver(void){
    
    uint16_t temp = read_temp_outside();
    
    if(temp != 0){
        Temp2 = temp>>1;    // mores delit z 2 ker je 0.5 step
        return ok;
    }
    
    return repeat;
}



uint8_t LCD_update_state_driver(void){
    
    char buffer[10];
    char buffer2[10];
    /*
    LCD_cursor_set(1, 1);
    
    if(Temp != 0){
        sprintf(buffer, "T1=%d", Temp);
    }
    
    LCD_write_string(buffer);
        
    
    LCD_cursor_set(2, 1);
    
    if(Temp2 != 0){
        sprintf(buffer2, "T2=%d", Temp2);
    }
    LCD_write_string(buffer2);
    */
    
    return ok;
}


uint8_t triac_calc_state_driver(void){

    float delay;
    uint16_t Tcalc;
    float pogresek = (float)(Temp - Ref_temp);
    
    char buffer[10];
    char buffer2[10];
    
    if(pogresek > 30.0 | pogresek < 0.0){            // to zna mogoce hecat ki sm spremenu treba preverit
        pogresek = 0;
    }
    
    delay = Delay_Calc(pogresek);
    Tcalc = Triac_Calc(delay);
    timer_1_fill_H = Tcalc>>8;
    timer_1_fill_L = Tcalc;
    
    
    sprintf(buffer, "%d,%d", timer_1_fill_H,timer_1_fill_L);
    sprintf(buffer2, "D=%f", delay);
    LCD_cursor_set(1, 1);
    LCD_write_string(buffer);
    LCD_cursor_set(2, 1);
    LCD_write_string(buffer2);
     
     
     
    return ok;
}



uint8_t main_menu_state_driver(void){

    if(Main_menu_F){
        main_menu_func();
        return repeat;                     //treba preverit ce je boljse z ifom ali z whilom
    }
    else if(!Main_menu_F){
        LCD_clear();
        return ok;
    }
    
    return fail;
}


uint8_t exit_state_driver(void){
    
    sprintf(buffer_g, "Err");
    
    return 1;

}


uint8_t lookup_transitions(uint8_t cur_state,uint8_t rc){
    uint8_t next_state;
    
    for(uint8_t i = 0; i < sizeof(state_transitions)/sizeof(state_transitions[0]); i++){
        if(state_transitions[i].src_state == cur_state){
            if (state_transitions[i].ret_code == rc){
                next_state = state_transitions[i].dst_state;
            }
            
        }
    }
    return next_state;
}
