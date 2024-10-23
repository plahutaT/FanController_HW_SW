#include "uart.h"

// Wi-Fi module commands
static const char* AT = "AT\r\n";
static const char* RST = "AT+RST\r\n";
static const char* CWMODE = "AT+CWMODE=1\r\n";
static const char* CWJAP = "AT+CWJAP=\"WIFIB32\",\"32brdnikova\"\r\n";
static const char* CIPMUX = "AT+CIPMUX=0\r\n";
static const char* CIPSTART = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n";
static const char* CIPSEND = "AT+CIPSEND=51\r\n";
static const char* CIPCLOSE = "AT+CIPCLOSE\r\n";
static const char* GET = "GET /update?api_key=HGCGZT2CUYJQLOR4";

/* UART inicializacija
 * 8 data bits, 1 stop, 1 start no parity
 * enable interrupt, nastavi priority
 *  */
void UART_init(void){
    TXSTA1bits.SYNC = 0;
    TXSTA1bits.TXEN = 1;
    RCSTA1bits.SPEN = 1;
    RCSTA1bits.CREN = 1;
    PIE1bits.RC1IE = 0;    // zaenkrat disejblamo interrupt davidimo kako bo
    IPR1bits.RC1IP = 0;    // low priority
}

/* UART 
 * nastavitev baud rate 
 *  */

void UART_115200_baud(void){
    
    TXSTA1bits.BRGH = 1;              // high baud
    BAUDCON1bits.BRG16 = 1;           // za manjsi error
    
    SPBRGH1 = 0;
    SPBRG1 = 34;                      // vrednost dobimo iz datasheeta
   
}

/* UART 
 * poslje 1 character
 *  */

void UART_send(const char data){
    while(!TXSTA1bits.TRMT);
    TXREG1 = data;
}

uint8_t UART_TSR_control(void){
    return TXSTA1bits.TRMT;
}

/* UART 
 * poslje NULL terminated string
 *  */

void UART_print(const char *string){
    
    for(uint8_t i = 0; string[i] != '\0'; i++)
    {
        UART_send(string[i]);
    }
}

uint8_t UART_read_available(void){
    return PIR1bits.RC1IF;
}

/* UART 
 * bere kar smo recivali prek UART
 *  */

void UART_read(char* response_add, uint8_t size){
    static uint8_t pos = 0;
    // pool if not set
    while(!PIR1bits.RC1IF){}
    
    if(pos < size){
        *(response_add + pos) =  RCREG1;
        pos++;
    }
    else if(pos >= size){
        pos = 0;
    }

}

/* 
 * Poslje potrebne ukaze WIFI modulu za povezavo na WIFI
 *  
 */


void connect_to_wifi(void){
        UART_print(CWMODE);    // ta vrne OK
        __delay_ms(400);
        
        UART_print(CWJAP);   // ta neki RECV 51 
        __delay_ms(400);

    
}

/* 
 * Poslje potrebne ukaze WIFI modulu da
 * poslje vrednost notranje temperature na
 * ThingSpeak
 *  
 */

void send_data_to_thingspeak(uint8_t value){
    char field[15];
    sprintf(field, "&field1=%d\r\n", value);
        UART_print(CIPSTART);
        __delay_ms(1000);
        UART_print(CIPSEND);    // ta vrne OK
        __delay_ms(200);
        
        UART_print(GET);   // ta neki RECV 51
        UART_print(field);   // 
        __delay_ms(200);
        
        UART_print(CIPCLOSE);   //  ta neki RECV 51
}
