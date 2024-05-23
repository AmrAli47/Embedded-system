/* 
 * File:   mcal_timer0.c
 * Author: Amr Ali
 *
 * Created on March 24, 2024, 2:59 AM
 */

#include "mcal_timer0.h"
static volatile uint16 l_preload_value = 0;
static void (* Timer0_Interrupt_Handler)(void) = NULL;
static STD_Return_t Timer0_Disable(Timer0_t *Timer);
static STD_Return_t Timer0_Enable(Timer0_t *Timer);
static STD_Return_t Timer0_Mode_Selection(Timer0_t *Timer);
static STD_Return_t Timer0_Prscaler_Selection(Timer0_t *Timer);
static STD_Return_t Timer0_Register_Size_Selection(Timer0_t *Timer);
static STD_Return_t Timer0_Interrupt_Init(Timer0_t *Timer);
static STD_Return_t Timer0_Set_Interrupt_Handler(Timer0_t *Timer);

/**
 * @brief initialize Timer 0
 * @param Timer configuration @ref Timer0_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer0_Init(Timer0_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
ret = Timer0_Disable(Timer);
ret = Timer0_Mode_Selection(Timer);
ret = Timer0_Prscaler_Selection(Timer);
ret = Timer0_Register_Size_Selection(Timer);
TMR0H = (uint8)((Timer->Preaload_value) >> 8);
TMR0L = (uint8)(Timer->Preaload_value);
l_preload_value = Timer->Preaload_value;
ret = Timer0_Interrupt_Init(Timer);
ret = Timer0_Set_Interrupt_Handler(Timer);
ret = Timer0_Enable(Timer);
ret = R_OK;    
}
return ret;
}

/**
 * @brief de-initialize Timer 0
 * @param Timer configuration @ref Timer0_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer0_DeInit(Timer0_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
ret = Timer0_Disable(Timer);
ret = R_OK;    
}
return ret;
}

/**
 * @brief write value to Timer 0 register
 * @param Timer configuration @ref Timer0_t
 * @param value which will be written in Timer 0 register
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer0_Write_value(Timer0_t *Timer,uint16 value)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
TMR0H = (uint8)((value) >> 8);
TMR0L = (uint8)(value);
ret = R_OK;    
}
return ret;
}

/**
 * @brief read value from Timer 0 register
 * @param Timer configuration @ref Timer0_t
 * @param value 
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer0_Read_value(Timer0_t *Timer,uint16 *value)
{
STD_Return_t ret = R_NOK;
uint8 l_timer_low = 0,l_timer_high = 0 ;
if((NULL == Timer) || (NULL == value))
{
ret = R_NOK;    
}
else
{
l_timer_low  =  (TMR0L); 
l_timer_high =  (TMR0H); 
*value = (uint16)((l_timer_high << 8) + l_timer_low);
ret = R_OK;    
}
return ret;
}

/* Timer 0 interrupt service routine */
void Timer0_ISR(void)
{
Timer0_Clear_Flag();
TMR0H = (uint8)((l_preload_value) >> 8);
TMR0L = (uint8)(l_preload_value);
if(Timer0_Interrupt_Handler)
{
Timer0_Interrupt_Handler();   
}    
}



/**
 * @brief disable Timer 0
 * @param Timer configuration @ref Timer0_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer0_Disable(Timer0_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer0_Module_Disable();
Timer0_Clear_Flag();
Timer0_Interrupt_Disable();
ret = R_OK;    
}
return ret;    
}


/**
 * @brief Enable Timer 0
 * @param Timer configuration @ref Timer0_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer0_Enable(Timer0_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer0_Module_Enable();
ret = R_OK;    
}
return ret;    
}

/**
 * @brief select Timer 0 Mode (Timer or Counter Mode)
 * @param Timer configuration @ref Timer0_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer0_Mode_Selection(Timer0_t *Timer)
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
case Timer_Mode: Timer0_Timer_Mode(); break; 
case Counter_Mode: Timer0_Counter_Mode(); 
if(Timer->Counter_Edge == Falling_Edge)
{
Timer0_Counter_Fallig_Edge();    
}
else if(Timer->Counter_Edge == Rising_Edge)
{
Timer0_Counter_Rising_Edge();    
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
 * @brief set Timer 0 Prescaler value 
 * @param Timer configuration @ref Timer0_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer0_Prscaler_Selection(Timer0_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
switch(Timer->Prescaler_Select)
{
case Presclaer_Feature_Disable: Disable_Prescaler_Feature(); break; 
case Presclaer_Feature_Enable:  Enable_Prescaler_Feature(); 
Set_Prescaler_value(Timer->Prescaler_value);
break; 
default : ret = R_NOK;
}
ret = R_OK;    
}
return ret;    
}
/**
 * @brief set Timer 0 register size 
 * @param Timer configuration @ref Timer0_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer0_Register_Size_Selection(Timer0_t *Timer)
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
case Timer0_8_Bit_Mode:   Timer0_8_Bit_Register();  break; 
case Timer0_16_Bit_Mode:  Timer0_16_Bit_Register(); break; 
default : ret = R_NOK;
}
ret = R_OK;    
}
return ret;    
}


/**
 * @brief set Timer 0 interrupt hander  
 * @param Timer configuration @ref Timer0_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer0_Set_Interrupt_Handler(Timer0_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer0_Interrupt_Handler = Timer->Timer0_Interrupt_Handler;
ret = R_OK;    
}
return ret;    
}
/**
 * @brief initialize Timer 0 interrupt  
 * @param Timer configuration @ref Timer0_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer0_Interrupt_Init(Timer0_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;
}
else
{
Peripheral_Interrupt_Enable(); 
Timer0_Clear_Flag();   
Timer0_Interrupt_Enable();
#if (Interrupt_Priority_Enable == 1)
if(Timer->Priority == High_Piority)
{
Timer0_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(Timer->Priority == Low_Priority)
{
Timer0_Interrupt_Low_Priority();
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
