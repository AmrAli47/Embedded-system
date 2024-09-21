/* 
 * File:   IWDG.c
 * Author: Amr Ali
 * @brief independent Watchdog Timer driver  
 */
#include "IWDG.h"

static uint8_t Enable_Write_Access_to_registers(void);

/**
 * @ brief start IWDG
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t start_IWDG(void)
{
uint8_t ret_val = E_OK;
IWDG->IWDG_KR = IWDG_START_KEY;
return ret_val;
}

/**
 * @ brief Initialize IWDG
 * @ param IWDG configuration @ref IWDG_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t IWDG_Init(IWDG_t* _IWDG)
{
uint8_t ret_val = E_OK;
Enable_Write_Access_to_registers();
IWDG->IWDG_PR = _IWDG->Prescaler_divider;
IWDG->IWDG_RLR = _IWDG->reload_value;
return ret_val;
}

/**
 * @ brief Refresh IWDG
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t IWDG_referesh(void)
{
uint8_t ret_val = E_OK;
IWDG->IWDG_KR = IWDG_RELOAD_KEY;
return ret_val;
}


/**
 * @ brief Enable Write Access to IWDG_PR and IWDG_RLR registers
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Enable_Write_Access_to_registers(void)
{
uint8_t ret_val = E_OK;
IWDG->IWDG_KR = EN_ACCESS_KEY;
return ret_val;
}
