/* 
 * File:   mcal_timer3.c
 * Author: Amr Ali
 *
 * Created on March 24, 2024, 10:51 PM
 */ 
 
#include "mcal_timer3.h"
static volatile uint16 l_preload_value = 0;
static void (* Timer3_Interrupt_Handler)(void) = NULL;
static STD_Return_t Timer3_Disable(Timer3_t *Timer);
static STD_Return_t Timer3_Enable(Timer3_t *Timer);

static STD_Return_t Timer3_Mode_Selection(Timer3_t *Timer);
static STD_Return_t Timer3_Set_Prscaler_value(Timer3_t *Timer);
static STD_Return_t Timer3_Register_Size_Selection(Timer3_t *Timer);
static STD_Return_t Timer3_Interrupt_Init(Timer3_t *Timer);
static STD_Return_t Timer3_Set_Interrupt_Handler(Timer3_t *Timer);

/**
 * @brief initialize Timer 3
 * @param Timer configuration @ref Timer3_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer3_Init(Timer3_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
ret = Timer3_Disable(Timer);
ret = Timer3_Mode_Selection(Timer);
ret = Timer3_Set_Prscaler_value(Timer);
ret = Timer3_Register_Size_Selection(Timer);
TMR3H = (uint8)((Timer->Preaload_value) >> 8);
TMR3L = (uint8)(Timer->Preaload_value);
l_preload_value = Timer->Preaload_value;
ret = Timer3_Interrupt_Init(Timer);
ret = Timer3_Set_Interrupt_Handler(Timer);
ret = Timer3_Enable(Timer);
ret = R_OK;    
}
return ret;
}

/**
 * @brief de-initialize Timer 3
 * @param Timer configuration @ref Timer3_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer3_DeInit(Timer3_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
ret = Timer3_Disable(Timer);
ret = R_OK;    
}
return ret;
}

/**
 * @brief write value to Timer 3 register
 * @param Timer configuration @ref Timer3_t
 * @param value which will be written in Timer 0 register
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer3_Write_value(Timer3_t *Timer,uint16 value)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
TMR3H = (uint8)((value) >> 8);
TMR3L = (uint8)(value);
ret = R_OK;    
}
return ret;
}

/**
 * @brief read value from Timer 3 register
 * @param Timer configuration @ref Timer3_t
 * @param value 
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer3_Read_value(Timer3_t *Timer,uint16 *value)
{
STD_Return_t ret = R_NOK;
uint8 l_timer_low = 0,l_timer_high = 0 ;
if((NULL == Timer) || (NULL == value))
{
ret = R_NOK;    
}
else
{
l_timer_low  =  (TMR3L); 
l_timer_high =  (TMR3H); 
*value = (uint16)((l_timer_high << 8) + l_timer_low);
ret = R_OK;    
}
return ret;
}

/* Timer 3 interrupt service routine */
void Timer3_ISR(void)
{
Timer3_Clear_Flag();
TMR3H = (uint8)((l_preload_value) >> 8);
TMR3L = (uint8)(l_preload_value);
if(Timer3_Interrupt_Handler)
{
Timer3_Interrupt_Handler();   
}    
}



/**
 * @brief disable Timer 3
 * @param Timer configuration @ref Timer3_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer3_Disable(Timer3_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer3_Module_Disable();
Timer3_Clear_Flag();
Timer3_Interrupt_Disable();
ret = R_OK;    
}
return ret;    
}


/**
 * @brief Enable Timer 3
 * @param Timer configuration @ref Timer3_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer3_Enable(Timer3_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer3_Module_Enable();
ret = R_OK;    
}
return ret;    
}
/**
 * @brief select Timer 3 Mode (Timer or Counter Mode)
 * @param Timer configuration @ref Timer3_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer3_Mode_Selection(Timer3_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
switch(Timer->Timer_Mode)
{
case Timer3_as_a_Timer: Timer3_Timer_Mode(); break; 
case Timer3_as_a_Counter: Timer3_Counter_Mode(); 
if(Timer->Counter_Mode == Timer3_Counter_Synchronous)
{
Timer3_Synchronous_Counter();    
}
else if(Timer->Counter_Mode == Timer3_Counter_Asynchronous)
{
Timer3_Asynchronous_Counter();    
}
else{/*Nothing*/}
break; 
default : ret = R_NOK;
}
ret = R_OK;    
}
return ret;  
}
/**
 * @brief set Timer 3 Prescaler value 
 * @param Timer configuration @ref Timer3_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer3_Set_Prscaler_value(Timer3_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Set_Prescaler_value(Timer->Prescaler_value);
ret = R_OK;    
}
return ret;    
}
/**
 * @brief set Timer 3 register size 
 * @param Timer configuration @ref Timer3_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer3_Register_Size_Selection(Timer3_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
switch(Timer->Register_Size)
{
case Timer3_8_Bit_Mode:   Timer3_8_Bit_Register();  break; 
case Timer3_16_Bit_Mode:  Timer3_16_Bit_Register(); break; 
default : ret = R_NOK;
}
ret = R_OK;    
}
return ret;    
}


/**
 * @brief set Timer 3 interrupt hander  
 * @param Timer configuration @ref Timer3_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer3_Set_Interrupt_Handler(Timer3_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer3_Interrupt_Handler = Timer->Timer3_Interrupt_Handler;
ret = R_OK;    
}
return ret;    
}
/**
 * @brief initialize Timer 3 interrupt  
 * @param Timer configuration @ref Timer3_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer3_Interrupt_Init(Timer3_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;
}
else
{
Peripheral_Interrupt_Enable(); 
Timer3_Clear_Flag();   
Timer3_Interrupt_Enable();
#if (Interrupt_Priority_Enable == 1)
if(Timer->Priority == High_Piority)
{
Timer3_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(Timer->Priority == Low_Priority)
{
Timer3_Interrupt_Low_Priority();
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





