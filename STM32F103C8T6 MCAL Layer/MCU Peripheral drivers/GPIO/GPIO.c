#include "GPIO.h"

/**
 * @brief Enable Clock for specific Port
 * @param Port Number @ref Port_t
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t Enable_Port_Clock(Port_t Port)
{
uint8_t ret_val = E_OK;
switch(Port)
{  
case Port_A: SET_BIT(GPIO_CLOCK_ADD,GPIO_CLOCK_BIT_POS); break ;
case Port_B: SET_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 1)); break ;
case Port_C: SET_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 2)); break ;
case Port_D: SET_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 3)); break ;
case Port_E: SET_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 4)); break ;
case Port_F: SET_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 5)); break ;
case Port_G: SET_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 6)); break ;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 * @brief Disable Clock for specific Port
 * @param Port Number @ref Port_t
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t Disable_Port_Clock(Port_t Port)
{
uint8_t ret_val = E_OK;
switch(Port)
{
case Port_A: CLEAR_BIT(GPIO_CLOCK_ADD,GPIO_CLOCK_BIT_POS); break ;
case Port_B: CLEAR_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 1)); break ;
case Port_C: CLEAR_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 2)); break ;
case Port_D: CLEAR_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 3)); break ;
case Port_E: CLEAR_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 4)); break ;
case Port_F: CLEAR_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 5)); break ;
case Port_G: CLEAR_BIT(GPIO_CLOCK_ADD,(GPIO_CLOCK_BIT_POS + 6)); break ;
default : ret_val = E_NOK;
}
return ret_val;
}


/**
 * @brief configure pin
 * @param reference to pin configuration @ref Pin_config_t
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t GPIO_config(Pin_config_t* GPIO_Pin)
{
uint8_t ret_val = E_OK;
Write_Pin(GPIO_Pin->Port_Num,GPIO_Pin->Pin_Num,Pin_Reset);
switch(GPIO_Pin->Port_Num)
{
case Port_A:
if(GPIO_Pin->Pin_Num <= Pin7)
{
GPIO_PORTA->GPIOx_CRL &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTA->GPIOx_CRL |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTA->GPIOx_CRL |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTA->GPIOx_CRL |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else if(Pin7 < GPIO_Pin->Pin_Num <= Pin15)
{
GPIO_Pin->Pin_Num -= 8;
GPIO_PORTA->GPIOx_CRH &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTA->GPIOx_CRH |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTA->GPIOx_CRH |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTA->GPIOx_CRH |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else
{
ret_val = E_NOK;
}
break ;
case Port_B:
if(GPIO_Pin->Pin_Num <= Pin7)
{
GPIO_PORTB->GPIOx_CRL &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTB->GPIOx_CRL |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTB->GPIOx_CRL |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTB->GPIOx_CRL |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else if(Pin7 < GPIO_Pin->Pin_Num <= Pin15)
{
GPIO_Pin->Pin_Num -= 8;
GPIO_PORTB->GPIOx_CRH &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTB->GPIOx_CRH |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTB->GPIOx_CRH |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTB->GPIOx_CRH |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else
{
ret_val = E_NOK;
}
break ;
case Port_C:
if(GPIO_Pin->Pin_Num <= Pin7)
{
GPIO_PORTC->GPIOx_CRL &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTC->GPIOx_CRL |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTC->GPIOx_CRL |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTC->GPIOx_CRL |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else if(Pin7 < GPIO_Pin->Pin_Num <= Pin15)
{
GPIO_Pin->Pin_Num -= 8;
GPIO_PORTC->GPIOx_CRH &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTC->GPIOx_CRH |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTC->GPIOx_CRH |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTC->GPIOx_CRH |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else
{
ret_val = E_NOK;
}
break ;
case Port_D:
if(GPIO_Pin->Pin_Num <= Pin7)
{
GPIO_PORTD->GPIOx_CRL &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTD->GPIOx_CRL |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTD->GPIOx_CRL |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTD->GPIOx_CRL |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else if(Pin7 < GPIO_Pin->Pin_Num <= Pin15)
{
GPIO_Pin->Pin_Num -= 8;
GPIO_PORTD->GPIOx_CRH &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTD->GPIOx_CRH |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTD->GPIOx_CRH |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTD->GPIOx_CRH |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else
{
ret_val = E_NOK;
}
break ;
case Port_E:
if(GPIO_Pin->Pin_Num <= Pin7)
{
GPIO_PORTE->GPIOx_CRL &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTE->GPIOx_CRL |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTE->GPIOx_CRL |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTE->GPIOx_CRL |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else if(Pin7 < GPIO_Pin->Pin_Num <= Pin15)
{
GPIO_Pin->Pin_Num -= 8;
GPIO_PORTE->GPIOx_CRH &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTE->GPIOx_CRH |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTE->GPIOx_CRH |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTE->GPIOx_CRH |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else
{
ret_val = E_NOK;
}
break ;
case Port_F:
if(GPIO_Pin->Pin_Num <= Pin7)
{
GPIO_PORTF->GPIOx_CRL &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTF->GPIOx_CRL |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTF->GPIOx_CRL |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTF->GPIOx_CRL |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else if(Pin7 < (GPIO_Pin->Pin_Num) <= Pin15)
{
GPIO_Pin->Pin_Num -= 8;
GPIO_PORTF->GPIOx_CRH &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTF->GPIOx_CRH |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTF->GPIOx_CRH |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTF->GPIOx_CRH |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else
{
ret_val = E_NOK;
}
break ;
case Port_G:
if(GPIO_Pin->Pin_Num <= Pin7)
{
GPIO_PORTG->GPIOx_CRL &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTG->GPIOx_CRL |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTG->GPIOx_CRL |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTG->GPIOx_CRL |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else if(Pin7 < GPIO_Pin->Pin_Num <= Pin15)
{
GPIO_Pin->Pin_Num -= 8;
GPIO_PORTG->GPIOx_CRH &= ~(PIN_CLEAR << ((GPIO_Pin->Pin_Num)*4));
GPIO_PORTG->GPIOx_CRH |= ((GPIO_Pin->pin_mode) << ((GPIO_Pin->Pin_Num)*4));
if(GPIO_Pin->pin_mode == Input_mode)
{
GPIO_PORTG->GPIOx_CRH |= ((GPIO_Pin->pin_input_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
else
{
GPIO_PORTG->GPIOx_CRH |= ((GPIO_Pin->pin_output_mode) << (((GPIO_Pin->Pin_Num)*4) + 2));
}
}
else
{
ret_val = E_NOK;
}
default : ret_val = E_NOK;
}
return ret_val;
}




/**
 * @brief Read Pin status
 * @param Port Number @ref Port_t
 * @param Pin Number @ref Pin_t
 * @param pin status
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t Read_Pin_Status(Port_t Port,Pin_t Pin,uint8_t* state)
{
uint8_t ret_val = E_OK;
*state = 0;
switch(Port)
{
case Port_A:
*state = READ_BIT(GPIO_PORTA->GPIOx_IDR,Pin);
break ;
case Port_B:
*state = READ_BIT(GPIO_PORTB->GPIOx_IDR,Pin);
break ;
case Port_C:
*state = READ_BIT(GPIO_PORTC->GPIOx_IDR,Pin);
break ;
case Port_D:
*state = READ_BIT(GPIO_PORTD->GPIOx_IDR,Pin);
break ;
case Port_E:
*state = READ_BIT(GPIO_PORTE->GPIOx_IDR,Pin);
break ;
case Port_F:
*state = READ_BIT(GPIO_PORTF->GPIOx_IDR,Pin);
break ;
case Port_G:
*state = READ_BIT(GPIO_PORTG->GPIOx_IDR,Pin);
break ;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 * @brief write pin logic (Active Low or Active High)
 * @param Port Number @ref Port_t
 * @param Pin Number @ref Pin_t
 * @param Pin status @ref Pin_state
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t Write_Pin(Port_t Port,Pin_t Pin,Pin_state state)
{
uint8_t ret_val = E_OK;
switch(Port)
{
case Port_A:
if(Pin_Set == state)
{
CLEAR_BIT(GPIO_PORTA->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTA->GPIOx_BSRR,Pin);
}
else if(Pin_Reset == state)
{
SET_BIT(GPIO_PORTA->GPIOx_BSRR,(Pin+16));
}
else
{
ret_val = E_NOK;
}
break ;
case Port_B:
if(Pin_Set == state)
{
CLEAR_BIT(GPIO_PORTB->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTB->GPIOx_BSRR,Pin);
}
else if(Pin_Reset == state)
{
SET_BIT(GPIO_PORTB->GPIOx_BSRR,(Pin+16));
}
else
{
ret_val = E_NOK;
}
break ;
case Port_C:
if(Pin_Set == state)
{
CLEAR_BIT(GPIO_PORTC->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTC->GPIOx_BSRR,Pin);
}
else if(Pin_Reset == state)
{
SET_BIT(GPIO_PORTC->GPIOx_BSRR,(Pin+16));
}
else
{
ret_val = E_NOK;
}
break ;
case Port_D:
if(Pin_Set == state)
{
CLEAR_BIT(GPIO_PORTD->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTD->GPIOx_BSRR,Pin);
}
else if(Pin_Reset == state)
{
SET_BIT(GPIO_PORTD->GPIOx_BSRR,(Pin+16));
}
else
{
ret_val = E_NOK;
}
break ;
case Port_E:
if(Pin_Set == state)
{
CLEAR_BIT(GPIO_PORTE->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTE->GPIOx_BSRR,Pin);
}
else if(Pin_Reset == state)
{
SET_BIT(GPIO_PORTE->GPIOx_BSRR,(Pin+16));
}
else
{
ret_val = E_NOK;
}
break ;
case Port_F:
if(Pin_Set == state)
{
CLEAR_BIT(GPIO_PORTF->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTF->GPIOx_BSRR,Pin);
}
else if(Pin_Reset == state)
{
SET_BIT(GPIO_PORTF->GPIOx_BSRR,(Pin+16));
}
else
{
ret_val = E_NOK;
}
break;
case Port_G:
if(Pin_Set == state)
{
CLEAR_BIT(GPIO_PORTG->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTG->GPIOx_BSRR,Pin);
}
else if(Pin_Reset == state)
{
SET_BIT(GPIO_PORTG->GPIOx_BSRR,(Pin+16));
}
else
{
ret_val = E_NOK;
}
break ;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 * @brief Toggle Pin state
 * @param Port Number @ref Port_t
 * @param Pin Number @ref Pin_t
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t Toggle_Pin(Port_t Port,Pin_t Pin)
{
uint8_t ret_val = E_OK;
switch(Port)
{
case Port_A:
if(Pin_Set == READ_BIT(GPIO_PORTA->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTA->GPIOx_BSRR,Pin);
SET_BIT(GPIO_PORTA->GPIOx_BSRR,(Pin +16));
}
else if(Pin_Reset == READ_BIT(GPIO_PORTA->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTA->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTA->GPIOx_BSRR,Pin);
}
else
{
ret_val = E_NOK;
}
break ;
case Port_B:
if(Pin_Set == READ_BIT(GPIO_PORTB->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTB->GPIOx_BSRR,Pin);
SET_BIT(GPIO_PORTB->GPIOx_BSRR,(Pin +16));
}
else if(Pin_Reset == READ_BIT(GPIO_PORTB->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTB->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTB->GPIOx_BSRR,Pin);
}
else
{
ret_val = E_NOK;
}
break ;
case Port_C:
if(Pin_Set == READ_BIT(GPIO_PORTC->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTC->GPIOx_BSRR,Pin);
SET_BIT(GPIO_PORTC->GPIOx_BSRR,(Pin +16));
}
else if(Pin_Reset == READ_BIT(GPIO_PORTC->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTC->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTC->GPIOx_BSRR,Pin);
}
else
{
ret_val = E_NOK;
}
break ;
case Port_D:
if(Pin_Set == READ_BIT(GPIO_PORTD->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTD->GPIOx_BSRR,Pin);
SET_BIT(GPIO_PORTD->GPIOx_BSRR,(Pin +16));
}
else if(Pin_Reset == READ_BIT(GPIO_PORTD->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTD->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTD->GPIOx_BSRR,Pin);
}
else
{
ret_val = E_NOK;
}
break ;
case Port_E:
if(Pin_Set == READ_BIT(GPIO_PORTE->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTE->GPIOx_BSRR,Pin);
SET_BIT(GPIO_PORTE->GPIOx_BSRR,(Pin +16));
}
else if(Pin_Reset == READ_BIT(GPIO_PORTE->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTE->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTE->GPIOx_BSRR,Pin);
}
else
{
ret_val = E_NOK;
}
break ;
case Port_F:
if(Pin_Set == READ_BIT(GPIO_PORTF->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTF->GPIOx_BSRR,Pin);
SET_BIT(GPIO_PORTF->GPIOx_BSRR,(Pin +16));
}
else if(Pin_Reset == READ_BIT(GPIO_PORTF->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTF->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTF->GPIOx_BSRR,Pin);
}
else
{
ret_val = E_NOK;
}
break;
case Port_G:
if(Pin_Set == READ_BIT(GPIO_PORTG->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTG->GPIOx_BSRR,Pin);
SET_BIT(GPIO_PORTG->GPIOx_BSRR,(Pin +16));
}
else if(Pin_Reset == READ_BIT(GPIO_PORTG->GPIOx_ODR,Pin))
{
CLEAR_BIT(GPIO_PORTG->GPIOx_BSRR,(Pin+16));
SET_BIT(GPIO_PORTG->GPIOx_BSRR,Pin);
}
else
{
ret_val = E_NOK;
}
break ;
default : ret_val = E_NOK;
}
return ret_val;
}

























