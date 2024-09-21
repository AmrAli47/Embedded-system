/* 
 * File:   mcal_i2c.c
 * Author: Amr Ali
 *
 * Created on March 28, 2024, 12:40 AM
 */ 

#include "mcal_i2c.h"
static void(* I2C_Interrupt_Handler)(void)= NULL;

static STD_Return_t I2C_Enable(I2C_t *I2C);
static STD_Return_t I2C_Disable(I2C_t *I2C);
static STD_Return_t I2C_Set_Slew_Rate(I2C_t *I2C);
static STD_Return_t I2C_Set_Configuration(I2C_t *I2C);
static STD_Return_t I2C_General_Call_Configuration(I2C_t *I2C);
static STD_Return_t I2C_Pin_Configuration(I2C_t *I2C);
static STD_Return_t I2C_Set_SPADD_value(I2C_t *I2C);
static STD_Return_t I2C_Interrupt_Init(I2C_t *I2C);
static STD_Return_t I2C_Set_Handlers(I2C_t *I2C);

/**
 * @brief initialize I2C Module
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_Init(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
ret = I2C_Disable(I2C);  
ret = I2C_Set_Slew_Rate(I2C);
ret = I2C_Set_Configuration(I2C);
ret = I2C_General_Call_Configuration(I2C);
ret = I2C_Pin_Configuration(I2C);
ret = I2C_Set_SPADD_value(I2C);
ret = I2C_Interrupt_Init(I2C);
ret = I2C_Set_Handlers(I2C);
ret = I2C_Enable(I2C);
ret = R_OK;
}
return ret;
}

/**
 * @brief set interrupt Handler
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t I2C_Set_Handlers(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
I2C_Interrupt_Handler = I2C->Interrupt_Handler;
ret = R_OK;
}
return ret;        
}

/**
 * @brief de-initialize I2C Module
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_DeInit(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
MSSP_Clear_Flag();
Bus_Collision_Interrupt_Disable();
Bus_Collision_Clear_Flag();
MSSP_Interrupt_Disable();
ret = I2C_Disable(I2C);    
ret = R_OK;
}
return ret;    
}


/**
 * @brief initialize I2C interrupt
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_Interrupt_Init(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
Peripheral_Interrupt_Enable(); 
MSSP_Clear_Flag();   
MSSP_Interrupt_Enable();
Bus_Collision_Interrupt_Enable();
Bus_Collision_Clear_Flag();
#if (Interrupt_Priority_Enable == 1)
if(I2C->Priority == High_Piority)
{
MSSP_Interrupt_High_Priority();
Bus_Collision_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(I2C->Priority == Low_Priority)
{
MSSP_Interrupt_Low_Priority();
Bus_Collision_Interrupt_Low_Priority();
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
 * @brief Send Start Condition
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_Master_Send_Start_Condition(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
MSSP_Interrupt_Disable();Bus_Collision_Interrupt_Disable();
Enable_Start_Condition();    
while(SSPCON2bits.SEN);
MSSP_Clear_Flag();
MSSP_Interrupt_Enable();
}
return ret;    
}


/**
 * @brief Send Repeated Start Condition
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_Master_Send_Repeated_Start_Condition(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
MSSP_Interrupt_Disable();
MSSP_Clear_Flag();
Set_Repeated_Start_Condition_on_Bus();    
while(SSPCON2bits.RSEN);  
MSSP_Clear_Flag();
MSSP_Interrupt_Enable();
if(SSPSTATbits.S == 1)
{
ret = R_OK;   
}
else
{
ret = R_NOK;    
}
}
return ret;    
}


/**
 * @brief Send Stop Condition
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_Master_Send_Stop_Condition(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
MSSP_Interrupt_Disable();
Set_Stop_Condition_on_Bus();    
while(SSPCON2bits.PEN); 
MSSP_Clear_Flag();
MSSP_Interrupt_Enable();
if(SSPSTATbits.P == 1)
{
ret = R_OK;   
}
else
{
ret = R_NOK;    
}
}
return ret;    
}

/**
 * @brief Slave Read Byte
 * @param reference I2C configurations @ref I2C_t
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_Slave_Read_Byte(I2C_t *I2C,uint8 *data)
{
STD_Return_t ret = R_NOK;
if((NULL == I2C) || (NULL == data))
{
ret = R_NOK;    
}
else
{
*data = SSPBUF; 
ret = R_OK;
}
return ret;    
}

/**
 * @brief Slave Read Byte
 * @param reference I2C configurations @ref I2C_t
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_Slave_Send_Byte(I2C_t *I2C,uint8 data)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
MSSP_Interrupt_Disable();
data = SSPBUF;
while(SSPSTATbits.BF); 
SSPBUF = data;
MSSP_Clear_Flag();
MSSP_Interrupt_Enable();
ret = R_OK;
}
return ret;   
}




/**
 * @brief Master Read Byte
 * @param reference I2C configurations @ref I2C_t
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_Master_Read_Byte(I2C_t *I2C,uint8 *data)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{ 
Enable_Receive_Mode();
while(!(SSPSTATbits.BF)) // wait till complete byte will be received
*data = SSPBUF;   
SSPCON2bits.ACKDT = 0;
SSPCON2bits.ACKEN = 1;
while(SSPCON2bits.ACKEN);
ret = R_OK;
}
return ret;     
}



/**
 * @brief Master Send Byte
 * @param reference I2C configurations @ref I2C_t
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t I2C_Master_Send_Byte(I2C_t *I2C,uint8 data)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
MSSP_Interrupt_Disable();
SSPBUF = data;
while(!(SSPSTATbits.BF));  
MSSP_Interrupt_Enable();
//while(SSPCON2bits.ACKSTAT); 
ret = R_OK;
}
return ret;      
}


/**
 * @brief Enable I2C Module
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t I2C_Enable(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
Enable_I2C_Module();   
ret = R_OK;
}
return ret;   
}


/**
 * @brief Disable I2C Module
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t I2C_Disable(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
Disable_I2C_Module();    
ret = R_OK;
}
return ret;   
}


/**
 * @brief Set Slew Rate
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t I2C_Set_Slew_Rate(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
switch(I2C->Slew_Rate)
{
case Standard_Mode:   Enable_Slew_Rate_Standard_Mode(); break ;
case High_Speed_Mode: Enable_Slew_Rate_High_Speed_Mode(); break ;
default : ret = R_NOK;
}  
ret = R_OK;
}
return ret;   
}


/**
 * @brief Set I2C Configuration
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t I2C_Set_Configuration(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
Set_I2C_Module_Configuration(I2C->I2C_Config);   
ret = R_OK;
}
return ret;   
}


/**
 * @brief make General Call
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t I2C_General_Call_Configuration(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
switch(I2C->General_Call)
{
case General_Call_Enable:   General_Call_Address_Interrupt_Enable(); break ;
case General_Call_Disable:  General_Call_Address_Interrupt_Disable(); break ;
default : ret = R_NOK;
}   
ret = R_OK;
}
return ret;   
}


/**
 * @brief set I2C Pins Configuration
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t I2C_Pin_Configuration(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
SET_BIT(TRISC,_TRISC_RC3_POSN);
SET_BIT(TRISC,_TRISC_RC4_POSN);
ret = R_OK;
}
return ret;   
}

/**
 * @brief set slave address
 * @param reference I2C configurations @ref I2C_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t I2C_Set_SPADD_value(I2C_t *I2C)
{
STD_Return_t ret = R_NOK;
if(NULL == I2C)
{
ret = R_NOK;    
}
else
{
switch(I2C->I2C_Mode)
{
case I2C_Master_Mode:
SSPADD = 0X09;
break ;
case I2C_Slave_Mode: 
SSPADD = device_address;
break ;
default : ret = R_NOK;
}   
ret = R_OK;
}
return ret;      
}

void I2C_ISR(void)
{
MSSP_Clear_Flag();    
if(I2C_Interrupt_Handler)
{
I2C_Interrupt_Handler();   
}
}
