/* 
 * File:   systick.h
 * Author: Amr Ali
 * @brief system timer driver driver 
 */

#include "systick.h"

void (*systick_callback)(void);
uint8_t timer_state = periodic_mode;

/*
 * @ brief configure system timer
 * @ param freference to system timer configuration @ref systick_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
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
return ret_val;
}
/*
 * @brief read remaining ticks
 * @param reference to remaining ticks
 * @return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Get_Remaining_Ticks(uint32_t* Remaining_Ticks)
{
uint8_t ret_val = E_NOK;
*Remaining_Ticks = SYSTICK->SYST_CVR;
ret_val = E_OK;
return ret_val;
}
/*
 * @ brief read elapsed ticks
 * @ param reference to elapsed ticks
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Get_Elapsed_Ticks(uint32_t* Elsapsed_Ticks)
{
uint8_t ret_val = E_NOK;
*Elsapsed_Ticks = SYSTICK->SYST_RVR - SYSTICK->SYST_CVR;
ret_val = E_OK;
return ret_val;
}

/*
 * @ brief delay
 * @ param to system timer configuration @ref systick_t
 * @ param dealy value in ms
 * @return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t delay_msec(systick_t* system_timer,uint32_t m_seconds)
{
uint8_t ret_val = E_OK;
SYSTICK->SYST_RVR = 0;
SYSTICK->SYST_CVR = 0;
uint32_t temp_val = 0;
switch(system_timer->timer_clock)
{
case processor_clock:
temp_val = ((m_seconds / 1000) * (PROCESSSOR_CLOCK_VAL - 1));
if(temp_val > RELOAD_REG_MAX_VALUE)
{
SYSTICK->SYST_RVR = RELOAD_REG_MAX_VALUE;
}
else
{
SYSTICK->SYST_RVR = temp_val;
}
start_systick_timer();
while(!(READ_BIT(SYSTICK->SYST_CSR,SYSTICK_TIMER_FLAG_BIT_POS)));
break;
case external_clock:
temp_val = ((m_seconds / 1000) * (EXTERNAL_CLOCK_VAL - 1));
if(temp_val > RELOAD_REG_MAX_VALUE)
{
SYSTICK->SYST_RVR = RELOAD_REG_MAX_VALUE;
}
else
{
SYSTICK->SYST_RVR = temp_val;
}
start_systick_timer();
while(!(READ_BIT(SYSTICK->SYST_CSR,SYSTICK_TIMER_FLAG_BIT_POS)));
break;
default : ret_val = E_NOK;
}
return ret_val;
}

/*
 * @ brief start timer
 * @return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t start_systick_timer(void)
{
uint8_t ret_val = E_OK;
SET_BIT(SYSTICK->SYST_CSR,SYSTICK_TIMER_ENABLE_BIT_POS);
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






















