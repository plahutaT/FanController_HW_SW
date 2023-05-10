/* 
 * File:   esp.h
 * Author: tilen
 *
 * Created on May 8, 2023, 5:13 PM
 */

#ifndef ESP_H
#define	ESP_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "usart.h"

extern volatile uint16_t multitasktimer;
extern const char* AT;
extern const char* CWMODE;
extern const char* CWJAP;
extern const char* CIPMUX;
extern const char* CIPSTART;
extern const char* CIPSEND;
extern const char* GET;
extern char esp_response[256];

typedef enum{
    ERROR = 0,
    OK,
} responses_t;

uint8_t wait_till_recived(const char* response_adrr, const char* response, uint16_t timeout);
void connect_to_wifi(void);
void send_data_to_thingspeak(uint8_t value);
uint8_t tcp_connect(uint16_t timeout);

#endif	/* ESP_H */

