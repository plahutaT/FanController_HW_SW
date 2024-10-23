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
#include "eeprom.h"
#include "DC_fan_ctrl.h"


//#define DEBUG


#define _XTAL_FREQ 16000000
#define TRIGGER LATBbits.LATB3;
#define LED_OK LATDbits.LATD5;
#define LED_NOK LATDbits.LATD6;
#define OSVETLITEV LATCbits.LATC3;

volatile uint16_t count = 0;
volatile uint8_t debounce_count = 0;
volatile uint32_t multitaskTimer = 0;


//char buffer_g[10];
//char buffer2_g[10];
uint16_t Temp = 0;
uint16_t Temp2 = 0;
uint8_t Ref_temp = 20;
uint8_t Main_menu_F = 0;
uint8_t Main_menu2_F = 0;
uint8_t Filter_F = 0;
uint8_t DC_fan_F = 1;
uint8_t DC_fan_running_F = 0;


//float pogresek = 0;
uint8_t timer_3_fill_H = 0xC1;
uint8_t timer_3_fill_L = 0x80;

void InitTimer3();
void InitTimer5();
void Initialize(void);
void DisINT0(void);
void EnINT0(void);


#ifdef DEBUG

    /* Koda ki zelimo da se izvaja v debug verziji
     * Timer dela interrut na 10ms, tako simuliramo AC interrupt
     * 
     *   */

    void __interrupt(low_priority) LowIsr(void){

         if (PIR1bits.TMR1IF && PIE1bits.TMR1IE){
            PIR1bits.TMR1IF = 0;
            count++;
            debounce_count++;
            multitaskTimer++;

            //LATBbits.LATB3 = 1;    // prizgemo triac
         }
    }
    

#endif


#ifndef DEBUG

    void __interrupt(low_priority) LowIsr(void){

       
            
        if (PIR2bits.TMR3IF && PIE2bits.TMR3IE) {
            PIR2bits.TMR3IF = 0;   // clear Timer3 flag
            LATBbits.LATB3 = 1;    // trigger TRIAC
        }
      
        
        if (PIR5bits.TMR5IF && PIE5bits.TMR5IE) {
            PIR5bits.TMR5IF = 0;   // clear Timer3 flag
            count++;
            debounce_count++;
            multitaskTimer++;   
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

            // loadamo timer z pravilnimi vrednostmi za zeleno zakasnitev
            TMR3H = timer_3_fill_H;
            TMR3L = timer_3_fill_L;

            //PIE1bits.TMR1IE = 1;           // enejblas interrupt ce ni Fullspeed_F setan
            PIR2bits.TMR3IF = 0;
            INTCONbits.INT0IF = 0;           // clearas interrupt flag bit
            INTCONbits.GIEH = 1;              // Vklop prekinitev

        }
       
        

        /*
        if(Fullspeed_F){
            PIE1bits.TMR1IE = 0;
            LATBbits.LATB3 = 1; //prizgi triak
        }
        */
        
    }

#endif




void main(void) {
    
    /*  Initializations    */
 
    Initialize();
    InitTimer3();
    InitTimer5();
    PWM_Init();
    
    /* Preberi vrednost reference iz EEPROM  */
	//Ref_temp = read_internal_eeprom(0x60);
    
    
    LATCbits.LATC3 = 0;
    __delay_ms(300);
    LCD_init();
    __delay_ms(100);
    LCD_clear();
    
    __delay_ms(300);      // delay da se stabilizira ekran
    
    //UART_init();
    //UART_115200_baud();
    LATBbits.LATB3 = 0;    // ugasnemo triac
    
    __delay_ms(500);
    
    /*  State machine init   */
    
    state_codes cur_state = temp_measure_inside; //testiraj ce deluje isto z temp_measure_inside // ustvarimo trenutni state         
    ret_codes rc;                                 // ustvarimo variable ki hrani return vrednosti fnkcij statov
    uint8_t (* state_func)(void);                 // ustvarimo pointer na funkcije statov
    
    
    
    /*   Variables    */
    uint8_t both_pressed = 0;
    uint32_t Wifi_ticks = 0;
    
    while(1){
        
        /*   Logika za laufanje state machina   */
        
        state_func = state_funcs[cur_state];
        rc = state_func();    
        cur_state = lookup_transitions(cur_state, rc);
        
        
        /*   Button check  
         *   checkiramo ali so pritisnjena oba gumba 
         *   ce so gremo v main menu
         */
        
        /*
        LCD_cursor_set(1, 1);
        LCD_write_string("TEST");
        LCD_cursor_set(2, 1);
        LCD_write_string("24DC");
        */
        
        
        
        both_pressed = Both_Button_Pressed();
        
        if(both_pressed){
            LCD_clear();
            Main_menu_F = 1;
            
            cur_state = main_menu;    //nastavimo state na main menu
        }
        
        /* Treba je naredit da gre v wifi state usakih par min   */
        
        // Trenutno nerabimo WIFI state
        /*
        if(multitaskTimer - Wifi_ticks >= 30000){        // 6000 je ena minuta
            //TODO nastavi state da je wifi
            cur_state = wifi_send_temp;
            Wifi_ticks = multitaskTimer;
        }
        */
        
        
        
        
        
        
        __delay_ms(200);
        
    }
    
    
    /* Fail safe loop  */
    while(1){}
    
    return;
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
    
    
    INTCONbits.INT0IE = 0;      // na zacetku disejblamo interupt na RB0 ki je INT0
    INTCON2bits.INTEDG0 = 1;    // interupt INT0 prozi na rising edge
    INTCONbits.INT0IE = 1;    // enejblamo interupt na RB0
    
    RCONbits.IPEN = 1;          // enable priority
    INTCONbits.PEIE_GIEL = 1;           // enejbelamo peripheral high priority intrrupts
    INTCONbits.GIE_GIEH = 1;         // enejblamo global interupts
    
}

void InitTimer3(){
    T3CON         = 0x01;
    IPR2bits.TMR3IP = 0;      // low priority
    PIR2bits.TMR3IF = 0;
    TMR3H         = 0x63;     // 0x63, 0xC0 je za 10ms
    TMR3L         = 0xC0;
    PIE2bits.TMR3IE = 1;
    //INTCON         = 0xC0;          // to je jebalo sistem
}

void InitTimer5(){
  T5CON	 = 0x01;
  IPR5bits.TMR5IP = 0;  
  PIR5bits.TMR5IF = 0;
  TMR5H	 = 0x63;
  TMR5L	 = 0xC0;
  PIE5bits.TMR5IE = 1;
  //INTCON	 = 0xC0;
}



