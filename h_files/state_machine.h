/* 
 * File:   state_machine.h
 * Author: tilen
 *
 * Created on April 8, 2023, 5:31 PM
 */

#ifndef STATE_MACHINE_H
#define	STATE_MACHINE_H

#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include "onewire.h"
#include "LCD.h"
#include "main_menu.h"
#include "power_calc.h"
#include "uart.h"
#include "DC_fan_ctrl.h"

#define EXIT_STATE end

//extern char buffer[10];
//extern char buffer2[10];
extern uint16_t Temp;
extern uint16_t Temp2;
extern uint8_t Ref_temp;
extern uint8_t Filter_F;
//extern float pogresek;                     pogresek nerabi bit global?
extern char buffer_g[10];
extern uint8_t timer_3_fill_H;
extern uint8_t timer_3_fill_L;
extern uint8_t DC_fan_F;
extern uint8_t DC_fan_running_F;



uint8_t decimal_f = 0;


uint8_t entry_state_driver(void);
uint8_t temp_measure_inside_state_driver(void);
uint8_t temp_measure_outside_state_driver(void);
uint8_t exit_state_driver(void);
uint8_t LCD_update_state_driver(void);
uint8_t main_menu_state_driver(void);
uint8_t triac_calc_state_driver(void);
uint8_t filter_state_driver(void);
uint8_t DC_Fan_driver(void);
uint8_t wifi_state_driver(void);
uint8_t lookup_transitions(uint8_t cur_state,uint8_t rc);


/* array and enum moreta biti v pravilnem zaporedju */
uint8_t (* state_funcs[])(void) = { temp_measure_inside_state_driver, temp_measure_outside_state_driver, LCD_update_state_driver, main_menu_state_driver, triac_calc_state_driver, filter_state_driver, DC_Fan_driver , wifi_state_driver, exit_state_driver};

/* imena stejtov */
typedef enum {
    temp_measure_inside,
    temp_measure_outside,
    LCD_update,
    main_menu,
    triac_calc,
    filter,
    DC_Fan,        
    wifi_send_temp,
    end
}state_codes ;

/* return codes */
typedef enum{
    ok,
    fail,
    repeat
}ret_codes;

typedef struct{
    state_codes src_state;
    ret_codes   ret_code;
    state_codes dst_state;
}transition;


/* 
 * 
 * array tranzicij
 *   
 */
transition state_transitions[] = {
    {temp_measure_inside, ok, temp_measure_outside},
    {temp_measure_inside, repeat, temp_measure_inside},
    {temp_measure_outside,   fail,   end},
    {temp_measure_outside,   repeat, temp_measure_outside},
    {temp_measure_outside,   ok,     LCD_update},
    {LCD_update,   ok,     triac_calc},
    {LCD_update,   fail,     end},
    {triac_calc,   ok,     filter},
    {filter, ok,     temp_measure_inside},
    {main_menu,   ok,     temp_measure_inside},
    {main_menu,   repeat,     main_menu},
    {wifi_send_temp,   ok,     temp_measure_inside},
    {wifi_send_temp,   repeat,    wifi_send_temp}
};

#endif	/* STATE_MACHINE_H */

