/* 
 * File:   PWR.c
 * Author: Amr Ali
 * @brief Power Control driver  
 */

#include "PWR.h"

static uint8_t Enable_PVD(void);
static uint8_t Disable_PVD(void);
static uint8_t Enable_PVD_Clock(void);
static uint8_t Disable_PVD_Clock(void);
static void (*PVD_Handler)(void);
/**
 * @ brief Enter sleep mode
 * @ param sleep entry mode @ref sleep_entery_mode_t
 * @ param sleep exit mode @ref sleep_exit_mode_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Enter_sleep_mode(sleep_entery_mode_t sleep_mode_entry,sleep_exit_mode_t sleep_exit_mode)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(SCB->SCR,SLEEP_DEEP_SLEEP_MODE_BIT_POS);
if(sleep_now == sleep_mode_entry)
{
CLEAR_BIT(SCB->SCR,SLEEP_ON_EXIT_BIT_POS);
if(wait_for_interrupt == sleep_exit_mode)
{
WFI();
}
else if(wait_for_event == sleep_exit_mode)
{
WFE();
}
else
{
ret_val = E_NOK;
}
}
else if(sleep_on_exit == sleep_mode_entry)
{
SET_BIT(SCB->SCR,SLEEP_ON_EXIT_BIT_POS);
WFI();
}
else
{
ret_val = E_NOK;
}
return ret_val ;
}


/**
 * @ brief Enter stop mode
 * @ param sleep exit mode @ref sleep_exit_mode_t
 * @ param voltage regulator mode mode @ref voltage_regulator_mode_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Enter_stop_mode(sleep_exit_mode_t sleep_exit_mode,voltage_regulator_mode_t voltage_regulator_mode)
{
uint8_t ret_val = E_OK;
SET_BIT(SCB->SCR,SLEEP_DEEP_SLEEP_MODE_BIT_POS);
CLEAR_BIT(PWR->PWR_CR,POWER_DOWN_DEEPSLEEP_BIT_POS);
if(voltage_regulator_normal_mode == voltage_regulator_mode)
{
CLEAR_BIT(PWR->PWR_CR,VOLTAGE_REGULATOR_MODE_BIT_POS);
}
else if(voltage_regulator_low_power_mode == voltage_regulator_mode)
{
SET_BIT(PWR->PWR_CR,VOLTAGE_REGULATOR_MODE_BIT_POS);
}
else
{
ret_val = E_NOK;
}
if(wait_for_interrupt == sleep_exit_mode)
{
WFI();
}
else if(wait_for_event == sleep_exit_mode)
{
WFE();
}
else
{
ret_val = E_NOK;
}
return ret_val ;
}

/**
 * @ brief Enter standby mode
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Enter_standby_mode(void)
{
uint8_t ret_val = E_OK;
SET_BIT(SCB->SCR,SLEEP_DEEP_SLEEP_MODE_BIT_POS);
SET_BIT(PWR->PWR_CR,POWER_DOWN_DEEPSLEEP_BIT_POS);
WFI();
return ret_val ;
}

/**
 * @ brief Enable wakeup pin (pin is used for wakeup from Standby mode and forced in input pull down
 *   configuration (rising edge on WKUP pin wakes-up the system from Standby mode)).
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Enable_wakeup_pin(void)
{
uint8_t ret_val = E_OK;
SET_BIT(PWR->PWR_CSR,WAKEUP_PIN_BIT_POS);
return ret_val ;
}


/**
 * @ brief Disable wakeup pin ( pin is used for general purpose I/O. An event on the WKUP pin does not wakeup
 *	  the device from Standby mode.
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Disable_wakeup_pin(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(PWR->PWR_CSR,WAKEUP_PIN_BIT_POS);
return ret_val ;
}



/**
 * @ brief Enable Programmable Voltage detector
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Enable_PVD(void)
{
uint8_t ret_val = E_OK;
SET_BIT(PWR->PWR_CR,PVD_EN_BIT_POS);
return ret_val ;
}

/**
 * @ brief Disable Programmable Voltage detector
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Disable_PVD(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(PWR->PWR_CR,PVD_EN_BIT_POS);
return ret_val ;
}


/**
 * @ brief initialize Programmable Voltage detector
 * @ param PVD configuration @ref PVD_config_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t PVD_Init(PVD_config_t* PVD)
{
uint8_t ret_val = E_OK;
Enable_PVD_Clock();
PWR->PWR_CR &= ~(PVD_LEVEL_SELECTION_MSK << PVD_LEVEL_SELECTION_BIT_POS);
PWR->PWR_CR |= ((PVD->PVD_Level) << PVD_LEVEL_SELECTION_BIT_POS);
if(PVD_Interrupt == PVD->mode)
{
SET_BIT(EXT_INT->EXTI_IMR,PVD_EXTI_BIT_POS);
}
else if(PVD_Event == PVD->mode)
{
SET_BIT(EXT_INT->EXTI_EMR,PVD_EXTI_BIT_POS);
}
else
{
ret_val = E_NOK;
}

if(PVD_Rising_Edge == PVD->edge)
{
SET_BIT(EXT_INT->EXTI_RTSR,PVD_EXTI_BIT_POS);
}
else if(PVD_Falling_Edge == PVD->edge)
{
SET_BIT(EXT_INT->EXTI_FTSR,PVD_EXTI_BIT_POS);
}
else
{
ret_val = E_NOK;
}
PVD_Handler = PVD->PVD_Callback;
Enable_PVD();
return ret_val ;
}

/**
 * @ brief De-initialize Programmable Voltage detector
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t PVD_DeInit(void)
{
uint8_t ret_val = E_NOK;
CLEAR_BIT(EXT_INT->EXTI_IMR,PVD_EXTI_BIT_POS);
CLEAR_BIT(EXT_INT->EXTI_EMR,PVD_EXTI_BIT_POS);
CLEAR_BIT(EXT_INT->EXTI_RTSR,PVD_EXTI_BIT_POS);
CLEAR_BIT(EXT_INT->EXTI_FTSR,PVD_EXTI_BIT_POS);
Disable_PVD();
Disable_PVD_Clock();
return ret_val;
}

/**
 * @ brief Enable PVD Clock
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Enable_PVD_Clock(void)
{
uint8_t ret_val = E_OK;
SET_BIT(RCC->RCC_APB1ENR,PWR_CLOCK_EN_BIT_POS);
return ret_val ;
}
/**
 * @ brief Disable PVD Clock
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Disable_PVD_Clock(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(RCC->RCC_APB1ENR,PWR_CLOCK_EN_BIT_POS);
return ret_val ;
}


/* PVD Interrupt Handler*/
void PVD_IRQHandler(void)
{
if(PVD_Handler)
{
PVD_Handler();
}
}

