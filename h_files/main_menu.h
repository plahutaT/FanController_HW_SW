/* 
 * File:   main_menu.h
 * Author: tilen
 *
 * Created on April 9, 2023, 8:07 PM
 */

#ifndef MAIN_MENU_H
#define	MAIN_MENU_H

#include <stdint.h>
#include <stdio.h>
#include "LCD.h"
#include "button.h"

extern uint8_t Ref_temp;
extern volatile uint16_t multitaskTimer;
extern uint8_t Main_menu_F;
uint16_t TicksM = 0;

void main_menu_func(void);

#endif	/* MAIN_MENU_H */

