/* 
 * File:   mcal_gpio.c
 * Author: Amr Ali
 *
 * Created on March 14, 2024, 8:07 PM
 */
#include "mcal_gpio.h"
/* Reference to data direction control register */
volatile uint8 *TRIS_REG[5] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/* Reference to data latch control register */
volatile uint8 *LAT_REG[5]  =  {&LATA,&LATB,&LATC,&LATD,&LATE};
/* Reference to port status register */
volatile uint8 *PORT_REG[5] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

/**
 * @brief initialize the direction of specific pin @ref Direction_t
 * @param pin_config pointer to pin configuration @ref Pin_Cofnig_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t pin_direction_initialize(Pin_Cofnig_t *pin_config)
{
STD_Return_t ret = R_NOK;   
/* check if pointer has null address  
 * check if pin number is higher than number of pins for each port in MCU
 * check if Port number is higher than number ports in the MCU
 */
if((NULL == pin_config)||(pin_config->Pin_Number > 7)||(pin_config->Port_Number > 3))
{
ret = R_NOK;     
}
else
{
switch(pin_config->direction)
{
/* set pin direction to input */
case Input: SET_BIT (*TRIS_REG[pin_config->Port_Number],pin_config->Pin_Number); break;
/* set pin direction to output */
case Output: CLEAR_BIT (*TRIS_REG[pin_config->Port_Number],pin_config->Pin_Number); break;
default : ret = R_NOK; 
}    
ret = R_OK;
}
return ret;
}   

/**
 * @brief read pin direction status @ref Direction_t
 * @param pin_config pointer to pin configuration @ref Pin_Cofnig_t
 * @param direction status 
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */

STD_Return_t get_pin_direction_initialize(Pin_Cofnig_t *pin_config,Direction_t *direction_status)
{
STD_Return_t ret = R_NOK;   
/* check if pointer has null address  
 * check if pin number is higher than number of pins for each port in MCU
 * check if Port number is higher than number ports in the MCU
 */
if((NULL == pin_config)||(pin_config->Pin_Number > 7)||(pin_config->Port_Number > 3)||(NULL == direction_status))
{
ret = R_NOK;     
}
else
{
/* read pin direction status */
*direction_status = READ_BIT(*TRIS_REG[pin_config->Port_Number],pin_config->Pin_Number);
ret = R_OK;
}
return ret;
}          

/**
 * @brief set pin to specific logic @ref logic_t
 * @param pin_config pointer to pin configuration @ref Pin_Cofnig_t
 * @param pin logic 
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t pin_write_logic(Pin_Cofnig_t *pin_config,logic_t logic)
{
STD_Return_t ret = R_NOK;   
/* check if pointer has null address  
 * check if pin number is higher than number of pins for each port in MCU
 * check if Port number is higher than number ports in the MCU
 */
if((NULL == pin_config)||(pin_config->Pin_Number > 7)||(pin_config->Port_Number > 3))
{
ret = R_NOK;     
}
else
{
switch(logic)
{
/* set pin logic to high output 5 volt */
case High: SET_BIT (*LAT_REG[pin_config->Port_Number],pin_config->Pin_Number); break;
/* set pin logic to low output zero volt */
case Low: CLEAR_BIT (*LAT_REG[pin_config->Port_Number],pin_config->Pin_Number); break;
default : ret = R_NOK; 
}    
ret = R_OK;
}
return ret;    
}      
/**
 * @brief read pin logic @ref logic_t
 * @param pin_config pointer to pin configuration @ref Pin_Cofnig_t
 * @param logic status 
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t get_pin_logic(Pin_Cofnig_t *pin_config,logic_t *logic_status)
{
STD_Return_t ret = R_NOK;   
/* check if pointer has null address  
 * check if pin number is higher than number of pins for each port in MCU
 * check if Port number is higher than number ports in the MCU
 */
if((NULL == pin_config)||(pin_config->Pin_Number > 7)||(pin_config->Port_Number > 3)||(NULL == logic_status))
{
ret = R_NOK;     
}
else
{
/* read pin logic status */
*logic_status = READ_BIT(*PORT_REG[pin_config->Port_Number],pin_config->Pin_Number); 
ret = R_OK;
}
return ret;      
}     

/**
 * @brief toggle pin logic @ref logic_t
 * @param pin_config pointer to pin configuration @ref Pin_Cofnig_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t pin_toggle_logic(Pin_Cofnig_t *pin_config)
{
STD_Return_t ret = R_NOK; 
/* check if pointer has null address  
 * check if pin number is higher than number of pins for each port in MCU
 * check if Port number is higher than number ports in the MCU
 */
if((NULL == pin_config)||(pin_config->Pin_Number > 7)||(pin_config->Port_Number > 3))
{
ret = R_NOK;     
}
else
{
/* toggle pin logic */
TOGGLE_BIT(*LAT_REG[pin_config->Port_Number],pin_config->Pin_Number); 
ret = R_OK;
}
return ret;     
}  
/**
 * @brief initialize pin direction and set it to low logic avoid floating voltage on it
 * @param pin_config pointer to pin configuration @ref Pin_Cofnig_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t pin_initialize(Pin_Cofnig_t *pin_config)
{
STD_Return_t ret = R_NOK;  
/* check if pointer has null address  
 * check if pin number is higher than number of pins for each port in MCU
 * check if Port number is higher than number ports in the MCU
 */
if((NULL == pin_config)||(pin_config->Pin_Number > 7)||(pin_config->Port_Number > 3))
{
ret = R_NOK;     
}
else
{
switch(pin_config->direction)
{
/* set pin as input with low logic*/
case Input:  SET_BIT   (*TRIS_REG[pin_config->Port_Number],pin_config->Pin_Number); pin_write_logic(pin_config,Low) ; break;
/* set pin as output with low logic*/
case Output: CLEAR_BIT (*TRIS_REG[pin_config->Port_Number],pin_config->Pin_Number); pin_write_logic(pin_config,Low) ; break;
default : ret = R_NOK; 
}    
ret = R_OK;
}
return ret;       
}
/**
 * @brief initialize port direction
 * @param port number  @ref Port_Number_t
 * @param port direction
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t port_direction_initialize(Port_Number_t port,uint8 direction)
{
STD_Return_t ret = R_OK;   
/* initialize port direction */
*TRIS_REG[port] = direction;
return ret;      
}      
/**
 * @brief read port direction
 * @param port number  @ref Port_Number_t
 * @param port direction status
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t get_port_direction(Port_Number_t port,uint8 *direction)
{
STD_Return_t ret = R_OK; 
/* check if pointer has null address */
if(direction == NULL)
{
STD_Return_t ret = R_NOK;    
}
else
{
/* read port direction */
*direction = *TRIS_REG[port];    
}
return ret;        
}      

/**
 * @brief write port logic
 * @param port number  @ref Port_Number_t
 * @param port logic
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */

STD_Return_t port_write_logic(Port_Number_t port,uint8 logic)
{
STD_Return_t ret = R_OK;
/* set port logic*/
*LAT_REG[port] = logic;
return ret;       
}     
/**
 * @brief read port logic
 * @param port number  @ref Port_Number_t
 * @param port logic
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */

STD_Return_t get_port_logic(Port_Number_t port,uint8 *logic)
{
STD_Return_t ret = R_OK; 
/* check if pointer has null address */
if(logic == NULL)
{
STD_Return_t ret = R_NOK;    
}
else
{
/* read port logic */
*logic = *LAT_REG[port];   
}
return ret;          
}        
/**
 * @brief toggle port logic
 * @param port number  @ref Port_Number_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t port_toggle_logic(Port_Number_t port)
{
STD_Return_t ret = R_OK;   
/* toggle port logic */
*LAT_REG[port] ^= PORT_MASK;
return ret;     
}  