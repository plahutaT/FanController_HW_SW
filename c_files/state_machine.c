#include "state_machine.h"

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
    
    uint16_t temp = Read_temp_inside();
    
    if(temp != 0){
        
        if(temp & 0x01){
            decimal_f = 1;
        }
        
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
    
    uint16_t temp = Read_temp_outside();
    
    if(temp != 0){
        Temp2 = temp>>1;    // mores delit z 2 ker je 0.5 step
        return ok;
    }
    
    return repeat;
}

/****************************************************************************

Function:           uint8_t LCD_update_state_driver(void);
Input:              Void

Output:             Void

PreCondition:
Related Parameters:
Overview:           Funkcija hendla prikaz na displeju                


******************************************************************************/

uint8_t LCD_update_state_driver(void){
    
    char buffer[10];
    char buffer2[10];
    LCD_clear();
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
    
    
    return ok;
}

/****************************************************************************

Function:           uint8_t triac_calc_state_driver(void);
Input:              Void

Output:             Void

PreCondition:
Related Parameters:
Overview:           Funkcija preracuna potreben delay vklopa triaka
                    in vrednost zapise v timer registre                


******************************************************************************/

uint8_t triac_calc_state_driver(void){

    static uint32_t prejsnja_temp = 0;
	static uint32_t filter_ticks = 0;
    float delay;
    uint16_t Tcalc;
    float pogresek;
    if(decimal_f){
        pogresek = (float)(Temp + 0.5f - Ref_temp);
    }
    else{
        pogresek = (float)(Temp - Ref_temp);
    }
    
    
    if(pogresek > 30.0 | pogresek < 0.0){            // to zna mogoce hecat ki sm spremenu treba preverit
        pogresek = 0;
    }
    
    delay = Delay_Calc(pogresek);
    Tcalc = Triac_Calc(delay);
    timer_3_fill_H = Tcalc>>8;
    timer_3_fill_L = Tcalc;
    
    /* for debugging
    char buffer[10];
    char buffer2[10];
    sprintf(buffer, "%d,%d", timer_3_fill_H,timer_3_fill_L);
    sprintf(buffer2, "D=%f", delay);
    LCD_cursor_set(1, 1);
    LCD_write_string(buffer);
    LCD_cursor_set(2, 1);
    LCD_write_string(buffer2);
    */ 
    
    
    	/* Preglej temperaturno razliko med notranjostno in zunanjostjo
	   in hitrost ventilatorja
	*/
	
	/* To se ni doreceno ker bi bilo treba sprobat na pravi elektro omarici */
	
	if(multitaskTimer - filter_ticks >= 360000){    // na usako uro pregledamo
		if(Temp2 - Temp < 2){
			prejsnja_temp = Temp;
			if(prejsnja_temp - Temp < 1 && delay < 1.0){
				Filter_F = 1;
			}
			
		}
	}
     
     
    return ok;
}

/****************************************************************************

Function:           uint8_t main_menu_state_driver(void);
Input:              Void

Output:             Void

PreCondition:
Related Parameters:
Overview:           Funkcija hendla main menu kjer izpise vrednost reference na displej
                    in uporabnik lahko nastavi zeleno referenco
                                   
******************************************************************************/

uint8_t main_menu_state_driver(void){
/*
    if(Main_menu_F){
        main_menu_func();
        return repeat;                     //treba preverit ce je boljse z ifom ali z whilom
    }
    else if (Main_menu2_F) {
        first_main_menu_func();
        return repeat; 
    }
    else if(!Main_menu_F && !Main_menu2_F){
        LCD_clear();
        return ok;
    }
*/

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







/****************************************************************************

Function:           uint8_t DC_Fan_driver(void);
Input:              Void

Output:             Void

PreCondition:
Related Parameters:
Overview:           Funkcija hendla DC Fan controll z PWM
                                   
******************************************************************************/

uint8_t DC_Fan_driver(void){
    
    
    
    
    
    
    
    
    
    
    return ok;
}






/****************************************************************************

Function:           uint8_t wifi_state_driver(void);
Input:              Void

Output:             Void

PreCondition:
Related Parameters:
Overview:           Funkcija hendla posiljanje podatka o notranji temperaturi v ThingSpeak
                                   
******************************************************************************/

uint8_t wifi_state_driver(void){
    LCD_clear();
    LCD_cursor_set(1, 1);
    LCD_write_string("Sending");
    LCD_cursor_set(2, 1);
    LCD_write_string("data...");
    // posljemo trenutno temperaturo v ThingSpeak
    send_data_to_thingspeak(Temp);
    
    LCD_clear();
    return ok;
}

/****************************************************************************

Function:           uint8_t exit_state_driver(void);
Input:              Void

Output:             Void

PreCondition:
Related Parameters:
Overview:           Ko vstopimo v EXIT state se program obesi 
                    ne smemo pri v EXIT state
                                   
******************************************************************************/


uint8_t exit_state_driver(void){
    
    LCD_clear();
    while(1){
        LCD_cursor_set(1, 1);
        LCD_write_string("Err...");  // obesimo program ker smo prislo v end state tu nesmes bit
    }  
    
    return 1;

}


uint8_t filter_state_driver(void){

	if(Filter_F == 1){
		LATDbits.LATD4 = 1;
	}
    
    return ok;
}

/****************************************************************************

Function:           uint8_t lookup_transitions(uint8_t cur_state,uint8_t rc);
Input:              cur_state -> trenutni state 
                    rc -> return code (kaj je vrnila funkcija trenutnega stata)

Output:             Void

PreCondition:
Related Parameters:
Overview:           Pregleda tabelo v kateri so shranjene tranzicije med stejti glede na to kar vrnejo 
                    funkcije trenutno izvedenih stejtov. Posice naslednji state
                                   
******************************************************************************/

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

