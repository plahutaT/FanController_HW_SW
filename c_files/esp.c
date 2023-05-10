#include "esp.h"

// Wi-Fi module settings
#define WIFI_SSID "WIFIB32"
#define WIFI_PASSWORD "32brdnikova"
#define THINGSPEAK_API_KEY "HGCGZT2CUYJQLOR4"

// funkcija vrne pointer na polozaj kjer se prvic pojavi response v stringu 
uint8_t wait_till_recived(const char* response_adrr, const char* response, uint16_t timeout){
    
    uint16_t start_time = multitasktimer;
    
    while((multitasktimer - start_time) < timeout){
        if(strstr(response_adrr, response)){
            return OK;
        }
        if(strstr(response_adrr, "err")){
            return ERROR;
        }
    }
    
    return ERROR;

}

void connect_to_wifi(void){
        USART_print(CWMODE);    // ta vrne OK
        __delay_ms(400);
        
        USART_print(CWJAP);   // ta neki RECV 51 
        __delay_ms(400);

    // Check for success message
    
}

void send_data_to_thingspeak(uint8_t value){
    char field[15];
    sprintf(field, "&field1=%d\r\n", value);
    
        USART_print(CIPSEND);    // ta vrne OK
        __delay_ms(400);
        
        USART_print(GET);   // ta neki RECV 51
        USART_print(field);   // 
        __delay_ms(400);
        
        USART_print(GET);   //  ta neki RECV 51
        USART_print(field);   // SEND OK
        __delay_ms(5000);

    // Check for success message
    if (strstr(esp_response, "SEND") == NULL) {
        //printf("Failed to send data to ThingSpeak: %s", esp_response);
    }
}

uint8_t tcp_connect(uint16_t timeout){
    
    USART_print(CIPSTART);   // vrne CONNECT OK
    
    if(wait_till_recived(esp_response, "CONN", timeout)){
        return OK;
    }
    else{
        tcp_connect(timeout);
    }
    
}
