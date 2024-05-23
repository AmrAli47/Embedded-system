/* 
 * File:   mcal_eusart.c
 * Author: Amr Ali
 *
 * Created on March 25, 2024, 7:40 PM
 */


#include "mcal_eusart.h"
static void (* Transmit_Handler)(void);
static void (* Reception_Handler)(void);
static STD_Return_t Select_Baud_Rate_Config(EUSART_t *EUSART);
static STD_Return_t Set_Baud_Rate_value(EUSART_t *EUSART);
static STD_Return_t Sending_or_Receiving(EUSART_t *EUSART);
static STD_Return_t EUSART_Disable(EUSART_t *EUSART);
static STD_Return_t EUSART_Enable(EUSART_t *EUSART);
static STD_Return_t Set_Handlers(EUSART_t *EUSART);
static STD_Return_t EUSART_Pin_Config(EUSART_t *EUSART);
static STD_Return_t EUSART_Interrupt_Init(EUSART_t *EUSART);
void return_ (void);

/**
 * @brief initialize EUSART Module
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EUSART_Init(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
    
}
else
{
ret = EUSART_Disable(EUSART);
ret = Select_Baud_Rate_Config(EUSART);
ret = Set_Baud_Rate_value(EUSART);
ret = Sending_or_Receiving(EUSART);
ret = EUSART_Pin_Config(EUSART);
ret = Set_Handlers(EUSART);
ret = EUSART_Interrupt_Init(EUSART);
ret = EUSART_Enable(EUSART);
ret = R_OK;    
}
return ret;
}

/**
 * @brief de-initialize EUSART Module
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EUSART_DeInit(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
    
}
else
{
ret = EUSART_Disable(EUSART);
EUSART_Transmit_Interrupt_Disable();
EUSART_Transmit_Clear_Flag();
EUSART_Receive_Interrupt_Disable();
EUSART_Receive_Clear_Flag();
ret = R_OK;    
}
return ret;    
}






/**
 * @brief set Baud Rate Configuration
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Select_Baud_Rate_Config(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
ret = R_NOK;    
}
else
{
switch(EUSART->BaudRate_config)
{
case config_8_bit_Asyncrhonous_Low_Speed:
UART_Asynchronous_Mode(); 
Baud_Rate_8_Bit();
Low_Baud_Rate();   
break;
case config_8_bit_Asyncrhonous_High_Speed:
UART_Asynchronous_Mode(); 
Baud_Rate_8_Bit();
High_Baud_Rate();
break;
case config_16_bit_Asyncrhonous_Low_Speed:
UART_Asynchronous_Mode();
Baud_Rate_16_Bit();
Low_Baud_Rate();   
break;
case config_16_bit_Asyncrhonous_High_Speed:
UART_Asynchronous_Mode();     
Baud_Rate_16_Bit();
High_Baud_Rate();
break;
case config_8_bit_syncrhonous:
UART_Synchronous_Mode();   
Baud_Rate_8_Bit();    
break;
case config_16_bit_syncrhonous:        
UART_Synchronous_Mode(); 
Baud_Rate_16_Bit();;  
break;
default : ret = R_NOK;
}
ret = R_OK;    
}
return ret;    
}


/**
 * @brief set Baud Rate value
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Set_Baud_Rate_value(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
uint8 l_8_bit_value = 0;
uint16 l_16_bit_value = 0;
if(NULL == EUSART)
{
ret = R_NOK;    
}
else
{
switch(EUSART->BaudRate_config)
{
case config_8_bit_Asyncrhonous_Low_Speed:
l_8_bit_value = (uint8)((4000000/(EUSART->BaudRate_value)/64));
SPBRG = l_8_bit_value;
break;
case config_8_bit_Asyncrhonous_High_Speed:
l_8_bit_value = (uint8)((4000000/(EUSART->BaudRate_value)/16) -1);
SPBRG = l_8_bit_value;
break;
case config_16_bit_Asyncrhonous_Low_Speed:
l_16_bit_value = (uint16)((4000000/(EUSART->BaudRate_value)/16) -1); 
SPBRG  = (uint8)(l_16_bit_value);
SPBRGH = (uint8)(l_16_bit_value >> 8);
break;
/*-------------------------------------------------------------------*/

case config_16_bit_Asyncrhonous_High_Speed:
l_16_bit_value = (uint16)((4000000/(EUSART->BaudRate_value)/4) -1); 
SPBRG  = (uint8)(l_16_bit_value);
SPBRGH = (uint8)(l_16_bit_value >> 8);
break;
case config_8_bit_syncrhonous:
l_8_bit_value = (uint8)((4000000/(EUSART->BaudRate_value)/4)-1);
SPBRG = l_8_bit_value;
break;
case config_16_bit_syncrhonous:        
l_16_bit_value = (uint16)((4000000/(EUSART->BaudRate_value)/4)-1); 
SPBRG  = (uint8)(l_16_bit_value);
SPBRGH = (uint8)(l_16_bit_value >> 8);
break;
default : ret = R_NOK;
}
ret = R_OK;    
}
return ret;       
}


/**
 * @brief select EUSART Module will be sender or receiver
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Sending_or_Receiving(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
    
}
else
{
switch(EUSART->direction)
{
case Transmission_Mode: 
Enable_Transmission_Mode();
Enable_Continuous_Receiver();  
if(EUSART->data_field == data_8_bits)
{
Select_8_Bit_Transmission();
}
else if(EUSART->data_field == data_9_bits)
{
Select_9_Bit_Transmission();   
}
else
{
Select_8_Bit_Transmission();    
}

if(EUSART->Synchronization_type == Asynchronous_Mode)
{
idle_state_for_clock_or_Transmit_reversing();
}
else if(EUSART->Synchronization_type == Synchronous_Mode)
{
Select_9_Bit_Transmission();   
}
else
{
Select_8_Bit_Transmission();    
}
break;

case Reception_Mode:    
Enable_Continuous_Receiver(); 
Enable_Transmission_Mode();
if(EUSART->data_field == data_8_bits)
{
Select_8_Bit_Reception();
}
else if(EUSART->data_field == data_9_bits)
{
Select_9_Bit_Reception();   
}
else
{
Select_8_Bit_Reception();    
}
break;
default : ret = R_NOK;
}       
ret = R_OK;    
}
return ret;     
}


/**
 * @brief Disable EUSART Module will be sender or receiver
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t EUSART_Disable(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
    
}
else
{
Disable_UART_Module();     
ret = R_OK;    
}
return ret;       
}

/**
 * @brief Enable EUSART Module will be sender or receiver
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t EUSART_Enable(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
    
}
else
{
Enable_UART_Module();     
ret = R_OK;    
}
return ret;       
}


/**
 * @brief initialize EUSART Module interrupt
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t EUSART_Interrupt_Init(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
    
}
else
{
switch(EUSART->direction)
{
case Transmission_Mode:
Peripheral_Interrupt_Enable(); 
EUSART_Transmit_Clear_Flag();  
EUSART_Transmit_Interrupt_Enable(); 
#if (Interrupt_Priority_Enable == 1)
if(EUSART->Priority == High_Piority)
{
EUSART_Transmit_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(EUSART->Priority == Low_Priority)
{
EUSART_Transmit_Interrupt_Low_Priority();
Global_Low_Priority_Interrupt_Enable();
}
else{/*Nothing*/}
#else
Global_Interrupt_Enable();
#endif
break;

case Reception_Mode:
Peripheral_Interrupt_Enable(); 
EUSART_Receive_Clear_Flag();   
EUSART_Receive_Interrupt_Enable();
#if (Interrupt_Priority_Enable == 1)
if(EUSART->Priority == High_Piority)
{
EUSART_Receive_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(EUSART->Priority == Low_Priority)
{
EUSART_Receive_Interrupt_Low_Priority();
Global_Low_Priority_Interrupt_Enable();
}
else{/*Nothing*/}
#else
Global_Interrupt_Enable();
#endif
break;
default : ret = R_NOK;
}       
ret = R_OK;    
}
return ret;      
}



/**
 * @brief send Byte (Blocking Mode)
 * @param reference EUSART configurations @ref EUSART_t
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EUSART_Write_Byte_Blocking(EUSART_t *EUSART,uint8 data)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
ret = R_NOK;    
}
else
{ 
while(!(TXSTAbits.TRMT));
TXREG = data;    
ret = R_OK;    
}
return ret;     
}
/**
 * @brief set pin configuration
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t EUSART_Pin_Config(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
ret = R_NOK;   
}
else
{
SET_BIT(TRISC,_TRISC_RC6_POSN);
SET_BIT(TRISC,_TRISC_RC7_POSN);
ret = R_OK;    
}
return ret;     
}

/**
 * @brief send string (Blocking Mode)
 * @param reference EUSART configurations @ref EUSART_t
 * @param string
 * @param length of string
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EUSART_Write_string_Blocking(EUSART_t *EUSART,uint8 *data,uint8 length)
{
STD_Return_t ret = R_NOK;
uint8 counter = 0;
if(NULL == EUSART)
{
ret = R_NOK;    
}
else
{ 
while(counter  < length)
{
while(!(TXSTAbits.TRMT));
TXREG = data[counter];  
counter++;
}
ret = R_OK;    
}
return ret;      
}


/**
 * @brief send data Byte (Non_Blocking Mode)
 * @param reference EUSART configurations @ref EUSART_t
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EUSART_Write_Byte_unblocking(EUSART_t *EUSART,uint8 data)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
ret = R_NOK;    
}
else
{
TXREG = data; 
ret = EUSART_Interrupt_Init(EUSART);
ret = R_OK;       
}
return ret;      
}

/**
 * @brief set EUSART interrupt Handler
 * @param reference EUSART configurations @ref EUSART_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Set_Handlers(EUSART_t *EUSART)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
ret = R_NOK;    
}
else
{ 
if(Transmission_Mode == EUSART->direction)
{
Transmit_Handler = EUSART->EUSART_Transmit_Interrupt_Handler;        
}
else if(Reception_Mode == EUSART->direction)
{
Reception_Handler = EUSART->EUSART_Transmit_Interrupt_Handler;    
}
ret = R_OK;    
}
return ret;     
}

/* EUSART Transmission interrupt service routine*/
void EUSART_Tx_ISR(void)
{
EUSART_Transmit_Interrupt_Disable();
if(Transmit_Handler)
{
Transmit_Handler();   
}
}
/* EUSART reception interrupt service routine*/
void EUSART_Rx_ISR(void)
{
EUSART_Transmit_Interrupt_Disable();
if(Reception_Handler)
{
Reception_Handler();
}
}


/**
 * @brief Read data Byte (Blocking Mode)
 * @param reference EUSART configurations @ref EUSART_t
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EUSART_Read_Byte_Blocking(EUSART_t *EUSART,uint8 *data)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
ret = R_NOK;    
}
else
{ 
while(!(PIR1bits.RCIF));
*data = RCREG;
ret = R_OK;    
}
return ret;     
}
/**
 * @brief Read data Byte (Non_Blocking Mode)
 * @param reference EUSART configurations @ref EUSART_t
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EUSART_Read_Byte_unblocking(EUSART_t *EUSART,uint8 *data)
{
STD_Return_t ret = R_NOK;
if(NULL == EUSART)
{
ret = R_NOK;    
}
else
{ 
*data = RCREG;
ret = R_OK;    
}
return ret;      
}

/**
 * @brief Read string (Non_Blocking Mode)
 * @param reference EUSART configurations @ref EUSART_t
 * @param data (This Parameter will be array)
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EUSART_Read_String_unblocking(EUSART_t *EUSART,uint8 *data)
{
STD_Return_t ret = R_NOK;
static uint8 i = 0;
if(NULL == EUSART)
{
ret = R_NOK;    
}
else
{ 
data[i] = RCREG;
i++;
ret = R_OK;    
}
return ret;      
}
