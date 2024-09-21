/* 
 * File:   mcal_spi.c
 * Author: Amr Ali
 *
 * Created on March 27, 2024, 11:34 AM
 */
#include "mcal_spi.h"
static STD_Return_t SPI_Enable(SPI_t *spi);
static STD_Return_t SPI_Disable(SPI_t *spi);
static STD_Return_t SPI_Set_Configuration(SPI_t *spi); 
static STD_Return_t SPI_Pin_Configuration(SPI_t *spi);
static STD_Return_t SPI_Select_Clock_status(SPI_t *spi);
static STD_Return_t SPI_Select_Sampling_Mode(SPI_t *spi);
static STD_Return_t SPI_Select_Transmitting_Mode(SPI_t *spi);
static STD_Return_t SPI_Set_Handlers(SPI_t *spi);
static void (* Read_Handler)(void) = NULL;

/**
 * @brief initialize SPI Module
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t SPI_Init(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
ret = SPI_Disable(spi);
ret = SPI_Set_Configuration(spi);        
ret = SPI_Pin_Configuration(spi);        
ret = SPI_Select_Clock_status(spi);
ret = SPI_Select_Sampling_Mode(spi); 
ret = SPI_Select_Transmitting_Mode(spi); 
ret = SPI_Set_Handlers(spi); 
ret = SPI_Enable(spi);    
ret = R_OK;
}
return ret;
}


/**
 * @brief de-initialize SPI Module
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t SPI_DeInit(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
ret = SPI_Disable(spi);   
ret = R_OK;
}
return ret;    
}


/**
 * @brief send Byte (Blocking Mode)
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t SPI_write_Byte_Blocking(uint8 data)
{
STD_Return_t ret = R_NOK;
while(SSPCON1bits.WCOL);
SSPBUF = data;
ret = R_OK;
return ret;
}

/**
 * @brief send string (Blocking Mode)
 * @param data
 * @param length of data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t SPI_write_string_Blocking(uint8 *data,uint8 len)
{
STD_Return_t ret = R_NOK;
uint8 counter = 0;
for(counter = 0;counter<len;counter++)
{
while(SSPCON1bits.WCOL);
SSPBUF = data[counter];  
}
ret = R_OK;
return ret;    
}

/**
 * @brief Enable SPI Module
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t SPI_Enable(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
Enable_MSSP_Module();  
ret = R_OK;
}
return ret;   
}



/**
 * @brief Disable SPI Module
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t SPI_Disable(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
Disable_MSSP_Module();
MSSP_Interrupt_Disable();
MSSP_Clear_Flag();
Bus_Collision_Interrupt_Disable();
Bus_Collision_Clear_Flag();
ret = R_OK;
}
return ret;    
}

/**
 * @brief Set SPI interrupt handler 
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t SPI_Set_Handlers(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
Read_Handler = spi->SPI_Read_Handler;
ret = R_OK;
}
return ret;       
}

/**
 * @brief Set SPI Module Configurations
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t SPI_Set_Configuration(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
MSSP_Module_Config(spi->Module_Configuration);    
ret = R_OK;
}
return ret;    
}


/**
 * @brief Set SPI Pin Configurations
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t SPI_Pin_Configuration(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
CLEAR_BIT(TRISC,_TRISC_RC5_POSN); 
switch(spi->Mode)
{
case Master_Mode:
CLEAR_BIT(TRISC,_TRISC_RC3_POSN);   
SET_BIT(TRISC,_TRISC_RC4_POSN);  
CLEAR_BIT(TRISA,_TRISA_RA5_POSN); 
break;
case Slave_Mode:
SET_BIT(TRISC,_TRISC_RC3_POSN);  
SET_BIT(TRISC,_TRISC_RC4_POSN); 
SET_BIT(TRISA,_TRISA_RA5_POSN); 
break;
default : ret = R_NOK;
}
ret = R_OK;
}
return ret;       
}
/* collision detector Interrupt Service Routine*/
void Collision_ISR(void)
{
Bus_Collision_Clear_Flag();
__delay_ms(500);
}
/**
 * @brief select clock status
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t SPI_Select_Clock_status(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
switch(spi->clock_status)
{
case idle_high:
Clock_idle_state_is_high();      
break;
case idle_low:
Clock_idle_state_is_low();        
break;
default : ret = R_NOK;
}
ret = R_OK;
}
return ret;       
}


/**
 * @brief select sampling mode
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t SPI_Select_Sampling_Mode(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
switch(spi->Sampling_Mode)
{
case at_the_end:
data_sampled_at_end_of_output_time();      
break;
case at_the_middle:
data_sampled_at_Middle_of_output_time();        
break;
default : ret = R_NOK;
}
ret = R_OK;
}
return ret;     
}


/**
 * @brief set Transmitting Mode Configuration
 * @param reference SPI configurations @ref SPI_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t SPI_Select_Transmitting_Mode(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;    
}
else
{
switch(spi->Transmitting_Mode)
{
case active_to_idle:
Transmit_occurs_from_active_to_idle();      
break;
case idle_to_active:
Transmit_occurs_from_idle_to_active();        
break;
default : ret = R_NOK;
}
ret = R_OK;
}
return ret;    
}


/**
 * @brief send Byte (Non_Blocking)
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t SPI_write_Byte_unblocking(uint8 data)
{
STD_Return_t ret = R_NOK;
SSPBUF = data;
ret = R_OK;
return ret;    
}


/**
 * @brief initialize SPI Module interrupt
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t SPI_Interrupt_Init(SPI_t *spi)
{
STD_Return_t ret = R_NOK;
if(NULL == spi)
{
ret = R_NOK;
}
else
{
Peripheral_Interrupt_Enable(); 
Bus_Collision_Clear_Flag(); 
MSSP_Clear_Flag(); 
MSSP_Interrupt_Enable();
Bus_Collision_Interrupt_Enable();
#if (Interrupt_Priority_Enable == 1)
if(spi->Priority == High_Piority)
{
ADC_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(spi->Priority == Low_Priority)
{
ADC_Interrupt_Low_Priority();
Global_Low_Priority_Interrupt_Enable();
}
else{/*Nothing*/}
#else
Global_Interrupt_Enable();
#endif
ret = R_OK;    
}
return ret;     
}
/**
 * @brief Read Byte Non_Blocking
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t SPI_Read_Byte_unblocking(uint8 *data)
{
STD_Return_t ret = R_NOK;
*data = SSPBUF;
MSSP_Interrupt_Disable();
ret = R_OK;
return ret;     
}


/* read data interrupt service routine */
void Read_ISR(void)
{
MSSP_Clear_Flag();
if(Read_Handler)
{
Read_Handler();
}
}
