/* 
 * File:   mcal_timer2.C
 * Author: Amr Ali
 *
 * Created on March 24, 2024, 10:49 PM
 */
#include "mcal_timer2.h"

static volatile uint8 l_preload_value = 0;
static void (* Timer2_Interrupt_Handler)(void) = NULL; 
static STD_Return_t Timer2_Disable(Timer2_t *Timer);
static STD_Return_t Timer2_Enable(Timer2_t *Timer);

static STD_Return_t Timer2_Set_Prscaler_value(Timer2_t *Timer);
static STD_Return_t Timer2_Set_Postscaler_value(Timer2_t *Timer);
static STD_Return_t Timer2_Interrupt_Init(Timer2_t *Timer);
static STD_Return_t Timer2_Set_Interrupt_Handler(Timer2_t *Timer);

/**
 * @brief initialize Timer 2
 * @param Timer configuration @ref Timer2_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer2_Init(Timer2_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
ret = Timer2_Disable(Timer);
ret = Timer2_Set_Prscaler_value(Timer);
ret = Timer2_Set_Postscaler_value(Timer);
PR2 = (uint8)(Timer->Preaload_value);
TMR2 = (uint8)0;
l_preload_value = Timer->Preaload_value;
ret = Timer2_Interrupt_Init(Timer);
ret = Timer2_Set_Interrupt_Handler(Timer);
ret = Timer2_Enable(Timer);
ret = R_OK;    
}
return ret;
}

/**
 * @brief de-initialize Timer 2
 * @param Timer configuration @ref Timer2_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer2_DeInit(Timer2_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
ret = Timer2_Disable(Timer);
ret = R_OK;    
}
return ret;
}

/**
 * @brief write value to Timer 2 register
 * @param Timer configuration @ref Timer2_t
 * @param value which will be written in Timer 2 register
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer2_Write_value(Timer2_t *Timer,uint8 value)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
PR2 = (uint8)(value);
ret = R_OK;    
}
return ret;
}

/**
 * @brief read value from Timer 2 register
 * @param Timer configuration @ref Timer2_t
 * @param value 
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Timer2_Read_value(Timer2_t *Timer,uint8 *value)
{
STD_Return_t ret = R_NOK;
if((NULL == Timer) || (NULL == value))
{
ret = R_NOK;    
}
else
{
*value = (uint8)(TMR2);
ret = R_OK;    
}
return ret;
}

/* Timer 2 interrupt service routine */
void Timer2_ISR(void)
{
Timer2_Clear_Flag();
TMR2 = (uint8)0;
PR2 = (uint8)(l_preload_value);
if(Timer2_Interrupt_Handler)
{
Timer2_Interrupt_Handler();   
}    
}



/**
 * @brief disable Timer 2
 * @param Timer configuration @ref Timer2_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer2_Disable(Timer2_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer2_Module_Disable();
Timer2_Clear_Flag();
Timer2_Interrupt_Disable();
ret = R_OK;    
}
return ret;    
}


/**
 * @brief Enable Timer 2
 * @param Timer configuration @ref Timer2_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer2_Enable(Timer2_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer2_Module_Enable();
ret = R_OK;    
}
return ret;    
}

/**
 * @brief set Timer 2 Prescaler value 
 * @param Timer configuration @ref Timer2_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer2_Set_Prscaler_value(Timer2_t *Timer)
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
 * @brief set Timer 2 Postscaler value 
 * @param Timer configuration @ref Timer2_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer2_Set_Postscaler_value(Timer2_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Set_Postscaler_value(Timer->Postscaler_value);
ret = R_OK;    
}
return ret;    
}




/**
 * @brief set Timer 2 interrupt hander  
 * @param Timer configuration @ref Timer2_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer2_Set_Interrupt_Handler(Timer2_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;    
}
else
{
Timer2_Interrupt_Handler = Timer->Timer2_Interrupt_Handler;
ret = R_OK;    
}
return ret;    
}
/**
 * @brief initialize Timer 0 interrupt  
 * @param Timer configuration @ref Timer2_t
 * @return status of the function
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Timer2_Interrupt_Init(Timer2_t *Timer)
{
STD_Return_t ret = R_NOK;
if(NULL == Timer)
{
ret = R_NOK;
}
else
{
Peripheral_Interrupt_Enable(); 
Timer2_Clear_Flag();   
Timer2_Interrupt_Enable();
#if (Interrupt_Priority_Enable == 1)
if(Timer->Priority == High_Piority)
{
Timer2_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(Timer->Priority == Low_Priority)
{
Timer2_Interrupt_Low_Priority();
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





