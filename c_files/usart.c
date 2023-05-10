#include "usart.h"
#include "ring_buffer.h"

#define UART_BUFFER_SIZE 16
static uint8_t buffer[UART_BUFFER_SIZE];
ring_buffer tx_buffer = {.buffer = buffer, .size = sizeof(buffer), .head = 0, .tail = 0};


void USART_init(void)
{
    TXSTA1bits.SYNC = 0;
    TXSTA1bits.TXEN = 1;
    RCSTA1bits.SPEN = 1;
    RCSTA1bits.CREN = 1;
    PIE1bits.RC1IE = 1;
    IPR1bits.RC1IP = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

inline void USART_clear_tx_flag(void){
    PIR1bits.TX1IF = 0;
}

inline void USART_tx_enable_interrupt(void){
    PIE1bits.TX1IE = 1;
}

inline void USART_tx_disable_interrupt(void){
    PIE1bits.TX1IE = 0;
}

void USART_tx_start(void){
    
    if (!ring_buffer_empty(&tx_buffer)) {
        TXREG1 = ring_buffer_peek(&tx_buffer);
    }

}

void USART_sendC_interrupt(const uint8_t data)
{
  
    // obesi if full
    while (ring_buffer_full(&tx_buffer)) { }

    USART_tx_disable_interrupt();
    
    // ce ring buffer ni prazen se izvaja posiljanje
    const uint8_t tx_ongoing = !ring_buffer_empty(&tx_buffer);
    
    // nalozi na ring buffer
    ring_buffer_push(&tx_buffer, data);
    
    // ce se ne posilja lahko zastratas ... ko je zastartano ga runna interrupt dokler se ne sprazne ring_buffer
    if (!tx_ongoing) {
        USART_tx_start();
    }
    
    USART_tx_enable_interrupt();
}

void USART_print_interrupt(const char *string)
{
    
    for(uint8_t i = 0; string[i] != '\0'; i++)
    {
        USART_sendC_interrupt(string[i]);
    }
}

void USART_calculate_baud(const unsigned long int baudrate)
{
    uint8_t value = 0;
    value = (_XTAL_FREQ - baudrate * 16) / (baudrate * 16);  // to je enacba za high speed
    TXSTA1bits.BRGH = 1;              // high speed
    
    if(value < 256)
    {
       SPBRG1 = value;
    }
}

void USART_115200_baud(void)
{
    
    TXSTA1bits.BRGH = 1;              // high baud
    BAUDCON1bits.BRG16 = 1;
    
    
    SPBRGH1 = 0;
    SPBRG1 = 34;
   
}

void USART_9600_baud(void)
{
    
    TXSTA1bits.BRGH = 0;              // high baud
    BAUDCON1bits.BRG16 = 0;
    
    
    //SPBRGH1 = 0;
    SPBRG1 = 25;
   
}

void USART_send(const char data)
{
    while(!TXSTA1bits.TRMT);
    TXREG1 = data;
}

unsigned char USART_TSR_control(void)
{
    return TXSTA1bits.TRMT;
}

void USART_print(const char *string)
{
    
    for(uint8_t i = 0; string[i] != '\0'; i++)
    {
        USART_send(string[i]);
    }
}

unsigned char USART_read_available(void)
{
    return PIR1bits.RC1IF;
}

void USART_read(char* response_add, uint8_t size)
{
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
