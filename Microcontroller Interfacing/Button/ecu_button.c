/* 
 * File:   ecu_button.c
 * Author: Amr Ali
 *
 * Created on March 16, 2024, 1:19 AM
 */
#include "ecu_button.h"
/* reference to Port status register*/
volatile uint8 *PORT_REG[5] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
/**
 * @brief initialize Button Pins
 * @param reference to Button configurations @ref Button_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Button_initialize(Button_t *Button)
{
STD_Return_t ret = R_NOK;
if(NULL == Button)
{
ret = R_NOK;    
}
else
{
ret = pin_direction_initialize(&(Button->Button_Pin));
ret = R_OK;    
}
return ret;
}
/**
 * @brief read Button status
 * @param reference to Button configurations @ref Button_t
 * @param Button status 
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t get_Button_status(Button_t *Button,Button_status_t *Button_status)
{
logic_t logic_status = 0;
STD_Return_t ret = R_NOK;
if(NULL == Button)
{
ret = R_NOK;    
}
else
{
ret = get_pin_logic(&(Button->Button_Pin),&logic_status);
if(Active_Low == Button->Button_Active_t)
{
if(Low == logic_status)   
{
*Button_status = Button_Pressed ;    
}
else
{
*Button_status = Button_Released;      
}
}
else if (Active_High == Button->Button_Active_t)
{
if(High == logic_status)   
{
*Button_status = Button_Pressed;    
}
else
{
*Button_status = Button_Released;      
}
}
else{/*Nothing*/}
ret = R_OK;    
}
return ret;    
}