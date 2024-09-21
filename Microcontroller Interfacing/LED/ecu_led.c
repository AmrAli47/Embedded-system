/* 
 * File:   ecu_led.h
 * Author: Amr Ali
 *
 * Created on March 14, 2024, 8:06 PM
 */
#include "ecu_led.h"
/* reference to latch control register */
volatile uint8 *LAT_REG[5]  =  {&LATA,&LATB,&LATC,&LATD,&LATE};
/**
 * @brief initialize led pins
 * @param reference Led configurations @ref Led_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Led_initialize(Led_t *Led)
{
STD_Return_t ret = R_NOK;
/* check if pointer has null address  */
if(NULL == Led)
{
ret = R_NOK;    
}
else
{
/* initialize led pins */
ret = pin_initialize(&(Led->Led_Pin));
ret = R_OK;    
}
return ret;
}

/**
 * @brief Turn on the led
 * @param reference Led configurations @ref Led_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Led_Turn_on(Led_t *Led)
{
STD_Return_t ret = R_NOK;
/* check if pointer has null address  */
if(NULL == Led)
{
ret = R_NOK;    
}
else
{
/* Turn on the Led */   
ret = pin_write_logic(&(Led->Led_Pin),High);
ret = R_OK;    
}
return ret;
}

/**
 * @brief Turn off the led
 * @param reference Led configurations @ref Led_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Led_Turn_off(Led_t *Led)
{
STD_Return_t ret = R_NOK;
/* check if pointer has null address  */
if(NULL == Led)
{
ret = R_NOK;    
}
else
{
/* Turn off the Led */   
ret = pin_write_logic(&(Led->Led_Pin),Low);
ret = R_OK;    
}
return ret;    
}

/**
 * @brief toggle led status
 * @param reference Led configurations @ref Led_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Led_Toggle(Led_t *Led)
{
uint8 state = 0;
STD_Return_t ret = R_NOK;
/* check if pointer has null address  */
if(NULL == Led)
{
ret = R_NOK;    
}
else
{
/* Toggle Led status */  
state = READ_BIT(*LAT_REG[Led->Led_Pin.Port_Number],Led->Led_Pin.Pin_Number);
switch(state)
{
case LED_ON: pin_write_logic(&(Led->Led_Pin),Low); break;
case LED_OFF:  pin_write_logic(&(Led->Led_Pin),High);  break;
default : ret = R_NOK;
}
ret = R_OK;    
}
return ret;    
}