/* 
 * File:   usart.h
 * Author: tilen
 *
 * Created on April 22, 2023, 7:31 PM
 */

#ifndef USART_H
#define	USART_H

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 16000000


inline void USART_clear_tx_flag(void);
inline void USART_tx_enable_interrupt(void);
inline void USART_tx_disable_interrupt(void);
void USART_sendC_interrupt(const uint8_t data);
void USART_print_interrupt(const char *string);
void USART_tx_start(void);
void USART_calculate_baud(const unsigned long int baudrate);
void USART_send(const char data);
unsigned char USART_TSR_control(void);
void USART_print(const char *string);
unsigned char USART_read_available(void);
void USART_read(char* response_add, uint8_t size);
void USART_init(void);
void USART_115200_baud(void);
void USART_9600_baud(void);



#endif	/* USART_H */

