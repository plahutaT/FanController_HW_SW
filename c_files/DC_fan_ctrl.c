#include <pic18f45k22.h>
#include "DC_fan_ctrl.h"





void PWM_Init(void) {
    // Set the RC2 pin as output
    TRISCbits.RC2 = 0;

    // Set up ECCP1 module in PWM mode
    CCP1CONbits.P1M = 0;        // Single output mode
    CCP1CONbits.CCP1M = 0b1100; // PWM mode

    // Set the PWM frequency (Period)
    // PR2 = [(_XTAL_FREQ / (PWM_freq * TMR2_prescale * 4)) - 1]
    // Example: PWM frequency = 5kHz, prescaler = 16
    PR2 = 249; // for 5kHz PWM with 16 prescaler

    // Set initial duty cycle (50% example)
    // Initial duty cycle to 50% (512/1023)
    PWM_SetDutyCycle(818);

    // Configure Timer2 for PWM
    T2CONbits.T2CKPS = 0b10;     // Timer2 prescaler 16
    T2CONbits.TMR2ON = 1;        // Turn on Timer2

    // Wait until Timer2 is ready
    while (!PIR1bits.TMR2IF);
    PIR1bits.TMR2IF = 0;
}

void PWM_SetDutyCycle(uint16_t duty_cycle) {
    // duty_cycle is a value between 0 and 1023 (10-bit)
    if (duty_cycle > 1023) {
        duty_cycle = 1023; // Cap duty cycle to 1023 (100%)
    }

    // Set the duty cycle (10-bit value)
    CCPR1L = duty_cycle >> 2;         // Upper 8 bits
    CCP1CONbits.DC1B = duty_cycle & 0x03;  // Lower 2 bits
}
















