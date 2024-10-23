/* 
 * File:   uart.h
 * Author: tilen
 *
 * Created on May 29, 2023, 5:29 PM
 */

#ifndef UART_H
#define	UART_H

/* Includes */
#include <xc.h>
#include <stdint.h>

/* Definitions */
#define _XTAL_FREQ 16000000

/* UART funkcije */
void UART_init(void);
void UART_115200_baud(void);
void UART_send(const char data);
uint8_t  UART_TSR_control(void);
void UART_print(const char *string);
uint8_t UART_read_available(void);
void UART_read(char* response_add, uint8_t size);
/* ESP funkcije */
void send_data_to_thingspeak(uint8_t value);
void connect_to_wifi(void);



#endif	/* UART_H */

