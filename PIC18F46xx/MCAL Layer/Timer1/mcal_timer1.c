/* 
 * File:   mcal_timer1.c
 * Author: Amr Ali
 *
 * Created on March 24, 2024, 5:56 AM
 */

#include "mcal_timer1.h"
static volatile uint16 l_preload_value = 0;
static void (* Timer1_Interrupt_Handler)(void) = NULL;
static STD_Return_t Timer1_Disable(Timer1_t *Timer);
static STD_Return_t Timer1_Enable(Timer1_t *Timer);

static STD_Return_t Timer1_Mode_Selection(Timer1_t *Timer);
static STD_Return_t Timer1_Set_Prscaler_value(Timer1_t *Timer);
static STD_Return_t Timer1_Register_Size_Selection(Timer1_t *Timer);
static STD_Return_t Timer1_Select_Oscillator(Timer1_t *Timer);
static STD_Return_t Timer1_Interrupt_Init(Timer1_t *Timer);
static STD_Return_t Timer1_Set_Interrupt_Handler(Timer1_t *Timer);

/**
 * @brief initialize Timer 1
 * @param Timer configuration @ref Timer1_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer1_Init(Timer1_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
ret = Timer1_Disable(Timer);

ret = Timer1_Mode_Selection(Timer);
ret = Timer1_Set_Prscaler_value(Timer);

ret = Timer1_Register_Size_Selection(Timer);
TMR1H = (uint8)((Timer->Preaload_value) >> 8);
TMR1L = (uint8)(Timer->Preaload_value);
l_preload_value = Timer->Preaload_value;
ret = Timer1_Select_Oscillator(Timer);
ret = Timer1_Interrupt_Init(Timer);
ret = Timer1_Set_Interrupt_Handler(Timer);
ret = Timer1_Enable(Timer);
ret = R_OK;    
}
return ret;
}

/**
 * @brief de-initialize Timer 1
 * @param Timer configuration @ref Timer1_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer1_DeInit(Timer1_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
ret = Timer1_Disable(Timer);
ret = R_OK;    
}
return ret;
}

/**
 * @brief write value to Timer 1 register
 * @param Timer configuration @ref Timer1_t
 * @param value which will be written in Timer 1 register
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer1_Write_value(Timer1_t *Timer,uint16 value)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
TMR1H = (uint8)((value) >> 8);
TMR1L = (uint8)(value);
ret = R_OK;    
}
return ret;
}

/**
 * @brief read value from Timer 1 register
 * @param Timer configuration @ref Timer1_t
 * @param value
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer1_Read_value(Timer1_t *Timer,uint16 *value)
{
STD_Return_t ret = R_NOK;
uint8 l_timer_low = 0,l_timer_high = 0 ;
if((NULL == Timer) || (NULL == value))
{
ret = R_NOK;    
}
else
{
l_timer_low  =  (TMR1L); 
l_timer_high =  (TMR1H); 
*value = (uint16)((l_timer_high << 8) + l_timer_low);
ret = R_OK;    
}
return ret;
}

/* Timer 1 interrupt service routine */
void Timer1_ISR(void)
{
Timer1_Clear_Flag();
TMR1H = (uint8)((l_preload_value) >> 8);
TMR1L = (uint8)(l_preload_value);
if(Timer1_Interrupt_Handler)
{
Timer1_Interrupt_Handler();   
}    
}



/**
 * @brief disable Timer 1
 * @param Timer configuration @ref Timer1_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer1_Disable(Timer1_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer1_Module_Disable();
Timer1_Clear_Flag();
Timer1_Interrupt_Disable();
ret = R_OK;    
}
return ret;    
}


/**
 * @brief Enable Timer 1
 * @param Timer configuration @ref Timer1_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer1_Enable(Timer1_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer1_Module_Enable();
ret = R_OK;    
}
return ret;    
}
/**
 * @brief select Timer 1 Mode (Timer or Counter Mode)
 * @param Timer configuration @ref Timer1_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer1_Mode_Selection(Timer1_t *Timer)
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
case Timer1_as_a_Timer: Timer1_Timer_Mode(); break; 
case Timer1_as_a_Counter: Timer1_Counter_Mode(); 
if(Timer->Counter_Mode == Counter_Synchronous)
{
Timer1_Synchronous_Counter();    
}
else if(Timer->Counter_Mode == Counter_Asynchronous)
{
Timer1_Asynchronous_Counter();    
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
 * @brief set Timer 1 Prescaler value 
 * @param Timer configuration @ref Timer1_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer1_Set_Prscaler_value(Timer1_t *Timer)
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
 * @brief set Timer 1 register size 
 * @param Timer configuration @ref Timer1_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer1_Register_Size_Selection(Timer1_t *Timer)
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
case Timer1_8_Bit_Mode:   Timer1_8_Bit_Register();  break; 
case Timer1_16_Bit_Mode:  Timer1_16_Bit_Register(); break; 
default : ret = R_NOK;
}
ret = R_OK;    
}
return ret;    
}


/**
 * @brief set Timer 1 interrupt hander  
 * @param Timer configuration @ref Timer1_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer1_Set_Interrupt_Handler(Timer1_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer1_Interrupt_Handler = Timer->Timer1_Interrupt_Handler;
ret = R_OK;    
}
return ret;    
}
/**
 * @brief initialize Timer 1 interrupt  
 * @param Timer configuration @ref Timer1_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer1_Interrupt_Init(Timer1_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;
}
else
{
Peripheral_Interrupt_Enable(); 
Timer1_Clear_Flag();   
Timer1_Interrupt_Enable();
#if (Interrupt_Priority_Enable == 1)
if(Timer->Priority == High_Piority)
{
Timer1_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(Timer->Priority == Low_Priority)
{
Timer1_Interrupt_Low_Priority();
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
 * @brief select Timer1 oscillator  
 * @param Timer configuration @ref Timer1_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer1_Select_Oscillator(Timer1_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
switch(Timer->Timer1_oscillaotr)
{
case Timer1_oscillator_Enable:   Enable_Timer1_oscillator();  break; 
case Timer1_oscillator_Disable:  Disable_Timer1_oscillator(); break; 
default : ret = R_NOK;
}
ret = R_OK;    
}
return ret;   
}



