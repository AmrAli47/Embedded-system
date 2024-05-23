#include "eusart.h"

volatile eusart_status_t eusartRxLastError;

/**
  Section: EUSART APIs
*/

void (*EUSART_FramingErrorHandler)(void);
void (*EUSART_OverrunErrorHandler)(void);
void (*EUSART_ErrorHandler)(void);

void EUSART_DefaultFramingErrorHandler(void);
void EUSART_DefaultOverrunErrorHandler(void);
void EUSART_DefaultErrorHandler(void);

void EUSART_Initialize(void)
{
    // Set the EUSART module to the options selected in the user interface.

    // ABDOVF no_overflow; CKTXP async_noninverted_sync_fallingedge; BRG16 16bit_generator; WUE disabled; ABDEN disabled; DTRXP not_inverted; 
    BAUDCON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave_mode; 
    TXSTA = 0x24;

    // 
    SPBRG = 0x67;

    // 
    SPBRGH = 0x00;


    EUSART_SetFramingErrorHandler(EUSART_DefaultFramingErrorHandler);
    EUSART_SetOverrunErrorHandler(EUSART_DefaultOverrunErrorHandler);
    EUSART_SetErrorHandler(EUSART_DefaultErrorHandler);

    eusartRxLastError.status = 0;

}

bool EUSART_is_tx_ready(void)
{
    return (bool)(PIR1bits.TX1IF && TXSTAbits.TXEN);
}

bool EUSART_is_rx_ready(void)
{
    return (bool)(PIR1bits.RC1IF);
}

bool EUSART_is_tx_done(void)
{
    return TXSTAbits.TRMT;
}

eusart_status_t EUSART_get_last_status(void){
    return eusartRxLastError;
}

uint8_t EUSART_Read(void)
{
    while(!PIR1bits.RC1IF)
    {
    }

    eusartRxLastError.status = 0;
    
    if(1 == RCSTAbits.OERR)
    {
        // EUSART error - restart

        RCSTAbits.CREN = 0; 
        RCSTAbits.CREN = 1; 
    }

    return RCREG;
}

void EUSART_Write(uint8_t txData)
{
    while(0 == PIR1bits.TX1IF)
    {
    }

    TXREG = txData;    // Write the data byte to the USART.
}




void EUSART_DefaultFramingErrorHandler(void){}

void EUSART_DefaultOverrunErrorHandler(void){
    // EUSART error - restart

    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;

}

void EUSART_DefaultErrorHandler(void){
}

void EUSART_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART_FramingErrorHandler = interruptHandler;
}

void EUSART_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART_OverrunErrorHandler = interruptHandler;
}

void EUSART_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART_ErrorHandler = interruptHandler;
}

void EUSART_Write_String(uint8_t *txData,uint8_t len)
{
uint8_t counter = 0;
while(counter  < len)
{
while(!(TXSTAbits.TRMT));
TXREG = txData[counter];  
counter++;
}    
}
/**
  End of File
*/
