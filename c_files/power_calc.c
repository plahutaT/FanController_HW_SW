#include "power_calc.h"

uint16_t Triac_Calc(float delay){

    uint16_t timer_1_fill = 0;
    
    timer_1_fill = (uint16_t)(TMR1_MAX_VALUE - (delay * 0.001 * FOSC ) / (PRESCALAR * 4));
    
    return timer_1_fill;
}

float Delay_Calc(float pogresek){

    float propotional = pogresek;
    float kp = 1;    // stem spreminjas hitrost odziva
    float output;
    float x;
    float y;
    
    
           // nesmemo it pod min delay in nesmemo it nad max delay
         // kp more bit med 0 in 1
         // fora je da vecji kot je pogresek manjsi more bit delay za vecjo moc

    output = (float)(kp * propotional);
    if(output > 10){
        output = 10;
    }
    else if(output <= 0 ){
        output = 0;
    }
         
         // linearna transformacija iz outputa PID v delay
         
    x = 10.0 * output;
    y = (-0.06 * x) + 6.00;          // sem menjal da gremo z delayem do 7ms
         
    //if (y <= 0.3){
    //  y = 0.3;            // to je se ce je delay 0 neki jebe sistem
    //}

    return y;
         

}

