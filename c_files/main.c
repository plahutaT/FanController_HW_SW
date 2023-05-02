/*
 * File:   main.c
 * Author: tilen
 *
 * Created on March 8, 2023, 1:22 PM
 */

#include "config.h"
#include <xc.h>
#include "onewire.h"
#include "LCD.h"
#include <stdio.h>
#include <pic18f45k22.h>
#include "state_machine.h"
#include "button.h"


#define _XTAL_FREQ 16000000
#define TRIGGER LATBbits.LATB3;

volatile uint16_t count = 0;
volatile uint8_t debounce_count = 0;
volatile uint16_t multitaskTimer = 0;


char buffer_g[10];
char buffer2_g[10];
uint16_t Temp = 0;
uint16_t Temp2 = 0;
uint8_t Ref_temp = 20;
uint8_t Main_menu_F = 0;
//float pogresek = 0;
uint8_t timer_1_fill_H = 0xC1;
uint8_t timer_1_fill_L = 0x80;



void __interrupt(low_priority) LowIsr(void){
    
     if (PIR1bits.TMR1IF && PIE1bits.TMR1IE){
        PIR1bits.TMR1IF = 0;
        //count++;
        //debounce_count++;
        //multitaskTimer++;
        
        LATBbits.LATB3 = 1;    // prizgemo triac
     }
}

void __interrupt(high_priority) HighIsr(void){
     
    /* Interrupt funkcija preverja kateri Interrupt e je zgodil
        RB0 Interrupt prozi na 10ms v ISR je treba ugasnit triac in napolnit timer ki bo nato prozil triac
    */

    if(INTCONbits.INT0IF && INTCONbits.INT0IE){
           
        INTCONbits.GIEH = 0;     // Prekini vse prekinitve
        LATBbits.LATB3 = 0;    // ugasnemo triac
        count++;
        debounce_count++;
        multitaskTimer++;
           
        // nastavimo na 7ms
        TMR1H = timer_1_fill_H;
        TMR1L = timer_1_fill_L;
           
        PIR1bits.TMR1IF = 0;
        INTCONbits.INT0IF = 0;           // clearas interrupt flag bit
        INTCONbits.GIEH = 1;              // Vklop prekinitev
           
    }



}


void InitTimer1(){
    T1CON         = 0x01;
    IPR1bits.TMR1IP = 0;      // low priority
    PIR1bits.TMR1IF = 0;
    TMR1H         = 0x00;
    TMR1L         = 0x00;
    PIE1bits.TMR1IE = 1;
    //INTCON         = 0xC0;          // to je jebalo sistem
}


void Initialize(void){
    
    OSCCON = 0B01110010;
    ANSELB = 0x00;
    ANSELD = 0x00;
    ANSELC = 0x00;
    ANSELE = 0x00;
    ANSELA = 0x00;
    TRISD = 0b00000000;
    TRISC = 0b00000000;
    TRISA = 0b00001111;
    TRISE = 0b00001111;
    TRISB = 0b00000001;           // nastavimo B0 na input
   


    CM1CONbits.C1ON = 0;            // Disable comparators
    CM2CONbits.C2ON = 0;
     
    ADCON0 = 0x00;              // ugasnemo ADC
    //ADCON0bits.ADON = 0;
    RCONbits.IPEN = 1;          // enable priority

    
    
    INTCONbits.INT0IE = 0;      // na zacetku disejblamo interupt na RB0 ki je INT0
    INTCON2bits.INTEDG0 = 1;    // interupt INT0 prozi na rising edge
    //INTCON3bits.INT1IP = 1;     // int1 interupt je high priority
    RCONbits.IPEN = 1;          // enable priority
    
    INTCONbits.INT0IE = 1;    // enejblamo interupt na RB0
    INTCONbits.GIE_GIEH = 1;         // enejblamo global interupts
    INTCONbits.PEIE_GIEL = 1;           // enejbelamo peripheral high priority intrrupts
    
}

void main(void) {
    
    /*  Initializations    */
    
    
    
    Initialize();
    InitTimer1();
    
    LCD_init();
    LCD_clear();
    
    __delay_ms(300);      // delay da se stabilizira ekran
    
    
    LATBbits.LATB3 = 0;    // ugasnemo triac
    
    /*  State machine init*/
    state_codes cur_state = entry;                // ustvarimo trenutni state         
    ret_codes rc;                                 // ustvarimo variable ki hrani return vrednosti fnkcij statov
    uint8_t (* state_func)(void);                 // ustvarimo pointer na funkcije statov
    
    
    
    /*   Variables    */
    
    
    uint8_t both_pressed = 0;
    
    
  
    
    while(1){
        
        /*   Logiga za laufanje state machina   */
        
        state_func = state_funcs[cur_state];
        rc = state_func(); 
        if (end == cur_state){
            while(1){
                LCD_write_string("Err");  // obesimo program ce je end nas state
            }    
        }    
        cur_state = lookup_transitions(cur_state, rc);
        
        
        /*   Button check  
         *   checkiramo ali so pritisnjena oba gumba 
         *   ce so gremo v main menu
         */
       
        both_pressed = Both_Button_Pressed();
        
        if(both_pressed){
            LCD_clear();
            Main_menu_F = 1;
            
            cur_state = main_menu;    //nastavimo state na main menu
        }
         
       //LCD_cursor_set(1,1); 
       //LCD_write_variable(multitaskTimer, 4);
    
        
    }
    
    
    /* Fail safe while loop  */
    
    
    while(1){
     
       
    }
    return;
}
