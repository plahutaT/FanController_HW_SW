/* 
 * File:   DC_fan_ctrl.h
 * Author: tilen
 *
 * Created on September 26, 2024, 12:43 PM
 */

#ifndef DC_FAN_CTRL_H
#define	DC_FAN_CTRL_H



#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include "onewire.h"
#include "LCD.h"
#include "main_menu.h"
#include "power_calc.h"
#include "uart.h"

void PWM_Init(void);
void PWM_SetDutyCycle(uint16_t duty_cycle);
void EnTimer5(void);
void DisTimer5(void);

#endif	/* DC_FAN_CTRL_H */

