/* 
 * File:   button.h
 * Author: tilen
 *
 * Created on April 8, 2023, 7:37 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include <stdint.h>
#include <stdio.h>
#include <xc.h>

#define BUTTON1 PORTAbits.RA2
#define BUTTON2 PORTAbits.RA3

extern volatile uint8_t debounce_count;
extern volatile uint16_t multitaskTimer;

uint8_t Get_Button_State(void);
uint8_t Get_Button_Press(void);
uint8_t Both_Button_Pressed(void);


#endif	/* BUTTON_H */

