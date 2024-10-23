#include "power_calc.h"

uint16_t Triac_Calc(float delay){

    uint16_t timer_1_fill = 0;
    
    timer_1_fill = (uint16_t)(TMR1_MAX_VALUE - (delay * 0.001 * FOSC ) / (PRESCALAR * 4));
    
    return timer_1_fill;
}

float Delay_Calc(float pogresek){

    float propotional = pogresek;
    uint8_t kp = 1;    // stem spreminjas hitrost odziva
    float output;
    float delay;
    
    
    // nesmemo it pod min delay in nesmemo it nad max delay
    // kp more bit med 0 in 1

    output = (float)(kp * propotional);
    if(output > 10){
        output = 10;
    }
    else if(output <= 0 ){
        output = 0;
    }
         
    // linearna transformacija iz outputa v delay
    delay = 6 - ((output * 6.0) / 10.0); // Scaling using division
    
    // ce je delay 0 bi lahko dau flag, ce je postavljen bi izklopu timer in prizgal triak
    if (delay < 0.2){  
      delay = 0.2;            // to je se ce je delay 0 neki jebe sistem
    }
    
    return delay;
        
}

