/* 
 * File:   External_Interrupt.c
 * Author: Amr Ali
 * @brief External interrupt driver  
 */

#include "External_Interrupt.h"
/*
 * @brief Enable external interrupt clock
 * @return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Enable_EXT_INT_Clock(void)
{
uint8_t ret_val = E_OK;
SET_BIT(EXT_INT_CLOCK‬,EXT_INT_CLOCK_BIT_POS);
return ret_val;
}

/*
 * @brief Disable external interrupt clock
 * @return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Disable_EXT_INT_Clock(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(EXT_INT_CLOCK‬,EXT_INT_CLOCK_BIT_POS);
return ret_val;
}

/*
 * @brief configure external request
 * @param reference to external request configuration @ref Ext_Int_Event_Config_t
 * @return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t EXT_Req_config(Ext_Int_Event_Config_t *Req)
{
uint8_t ret_val = E_OK;
switch(Req->Request_type)
{
case External_Interurpt:
SET_BIT(EXT_INT->EXTI_IMR,Req->Request_Number);
break;
case External_Event:
SET_BIT(EXT_INT->EXTI_EMR,Req->Request_Number);
break;
default : ret_val = E_NOK;
}
switch(Req->Edge)
{
case Falling_Edge:
SET_BIT(EXT_INT->EXTI_FTSR,Req->Request_Number);
SET_BIT(EXT_INT->EXTI_PR,Req->Request_Number);
break;
case Rising_Edge:
SET_BIT(EXT_INT->EXTI_RTSR,Req->Request_Number);
SET_BIT(EXT_INT->EXTI_PR,Req->Request_Number);
break;
case Rising_and_Falling_Edge:
SET_BIT(EXT_INT->EXTI_RTSR,Req->Request_Number);
SET_BIT(EXT_INT->EXTI_FTSR,Req->Request_Number);
SET_BIT(EXT_INT->EXTI_PR,Req->Request_Number);
break;
default : ret_val = E_NOK;
}

return ret_val;
}

/*
 * @brief generate interrupt by software
 * @param request number @ref Ext_Int_Event_t
 * @return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t generate_software_interrupt(Ext_Int_Event_t Req)
{
uint8_t ret_val = E_OK;
SET_BIT(EXT_INT->EXTI_SWIER,Req);
return ret_val;
}

/*
 * @brief clear pending state
 * @param request number @ref Ext_Int_Event_t
 * @return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Clear_Pending_Bit(Ext_Int_Event_t Req)
{
uint8_t ret_val = E_OK;
SET_BIT(EXT_INT->EXTI_PR,Req);
return ret_val;
}
