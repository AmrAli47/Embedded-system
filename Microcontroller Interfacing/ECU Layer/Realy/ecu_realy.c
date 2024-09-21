/* 
 * File:   ecu_relay.c
 * Author: Amr Ali
 *
 * Created on March 16, 2024, 3:38 PM
 */
#include "ecu_relay.h"
/**
 * @brief initialize relay pins
 * @param reference Relay configurations @ref Relay_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Relay_initialize(Relay_t *Relay)
{
STD_Return_t ret = R_NOK;
if(NULL == Relay)
{
ret = R_NOK;    
}
else
{
ret = pin_initialize(&(Relay->Relay_Pin));  
}
return ret;
}
/**
 * @brief Turn on the relay
 * @param reference Relay configurations @ref Relay_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Relay_Turn_on(Relay_t *Relay)
{
STD_Return_t ret = R_NOK;
if(NULL == Relay)
{
ret = R_NOK;    
}
else
{
ret = pin_write_logic(&(Relay->Relay_Pin),High);   
}
return ret;    
}
/**
 * @brief Turn off the relay
 * @param reference Relay configurations @ref Relay_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Relay_Turn_off(Relay_t *Relay)
{
STD_Return_t ret = R_NOK;
if(NULL == Relay)
{
ret = R_NOK;    
}
else
{
ret = pin_write_logic(&(Relay->Relay_Pin),Low);     
}
return ret;   
}
