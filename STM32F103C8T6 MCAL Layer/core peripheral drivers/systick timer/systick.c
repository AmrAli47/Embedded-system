/* 
 * File:   systick.c
 * Author: Amr Ali
 * @brief system timer driver driver 
 */
#include "systick.h"

void (*systick_callback)(void);
uint8_t timer_state = periodic_mode;

/*
 * @brief configure system timer
 * reference to system timer configuration @ref systick_t
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t configure_systick_timer(systick_t* system_timer)
{
uint8_t ret_val = E_OK;
SYSTICK->SYST_RVR = 0;
SYSTICK->SYST_CVR = 0;
switch(system_timer->timer_clock)
{
case external_clock : CLEAR_BIT(SYSTICK->SYST_CSR,SYSTICK_TIMER_CLOCK_BIT_POS); break;
case processor_clock: SET_BIT(SYSTICK->SYST_CSR,SYSTICK_TIMER_CLOCK_BIT_POS);   break;
default : ret_val = E_NOK;
}
switch(system_timer->timer_exception)
{
case Disbale : CLEAR_BIT(SYSTICK->SYST_CSR,SYSTICK_TIMER_EXCEPTION_BIT_POS); break;
case Enable: SET_BIT(SYSTICK->SYST_CSR,SYSTICK_TIMER_EXCEPTION_BIT_POS);
systick_callback = system_timer->ptr_function;
break;
default : ret_val = E_NOK;
}
SYSTICK->SYST_RVR = system_timer->reload_value;
if(single_mode == system_timer->timer_mode)
{
timer_state = single_mode;
}
else
{/* Nothing */}
SET_BIT(SYSTICK->SYST_CSR,SYSTICK_TIMER_ENABLE_BIT_POS);
return ret_val;
}
/*
 * @brief read remaining ticks
 * pointer to remaining ticks
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Get_Remaining_Ticks(uint32_t* Remaining_Ticks)
{
uint8_t ret_val = E_NOK;
*Remaining_Ticks = SYSTICK->SYST_CVR;
ret_val = E_OK;
return ret_val;
}
/*
 * @brief read elapsed ticks
 * pointer to elapsed ticks
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Get_Elapsed_Ticks(uint32_t* Elsapsed_Ticks)
{
uint8_t ret_val = E_NOK;
*Elsapsed_Ticks = SYSTICK->SYST_RVR - SYSTICK->SYST_CVR;
ret_val = E_OK;
return ret_val;
}

/*
 * @brief system timer interrupt handler
 * */
void SysTick_Handler(void)
{
if(timer_state == single_mode)
{
CLEAR_BIT(SYSTICK->SYST_CSR,SYSTICK_TIMER_ENABLE_BIT_POS);
}
else
{/* Nothing */}
if(systick_callback)
{
systick_callback();
}
}
























