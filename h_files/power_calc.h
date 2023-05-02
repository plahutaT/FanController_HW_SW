/* 
 * File:   power_calc.h
 * Author: tilen
 *
 * Created on April 9, 2023, 8:43 PM
 */

#ifndef POWER_CALC_H
#define	POWER_CALC_H

#include <stdint.h>
#include <stdio.h>

#define TMR1_MAX_VALUE 65536
#define FOSC 16000000
#define PRESCALAR 1

uint16_t Triac_Calc(float delay);
float Delay_Calc(float pogresek);

#endif	/* POWER_CALC_H */

