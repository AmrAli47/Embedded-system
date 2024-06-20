/* 
 * File:   WWDG.c
 * Author: Amr Ali
 * @brief Window Watchdog Timer driver  
 */

#include "WWDG.h"
static uint8_t Enable_WWDG_Clock(void);
static uint8_t Disable_WWDG_Clock(void);
static void (* WWDG_interrupt_Handler)(void);

/**
 * @ brief initialize WWDG
 * @ param WWDG configuration @ref WWDG_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t WWDG_Init(WWDG_t* _WWDG)
{
uint8_t ret_val = E_OK;
Enable_WWDG_Clock();
WWDG->WWDG_CFR &= ~(WWDG_PRESCALER_MSK << WWDG_PRESCALER_BIT_POS);
WWDG->WWDG_CFR |= ((_WWDG->Prescaler_divider) << WWDG_PRESCALER_BIT_POS);
if(Enable_Early_wakeup_interrupt == _WWDG->Early_wakeup_interrupt)
{
SET_BIT(WWDG->WWDG_CFR,EARLY_WAKE_INT_EN_BIT_POS);
WWDG_interrupt_Handler = _WWDG->WWDG_interrupt_callback;
}
else
{
/* Nothing */
}
SET_BIT(WWDG->WWDG_CR,WWDG_ACTIVATION_BIT_POS);
return ret_val;
}

/**
 * @ brief De-initialize WWDG
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t WWDG_DeInit(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(WWDG->WWDG_CR,WWDG_ACTIVATION_BIT_POS);
Disable_WWDG_Clock();
return ret_val;
}

/**
 * @ brief refresh WWDG (reload value range should be from 0x7E to 0x40), Note 0X40 will cause immediate reset
 * @ param reload value
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t WWDG_Refersh(uint8_t reload_value)
{
uint8_t ret_val = E_OK;
Enable_WWDG_Clock();
reload_value |= WWDG_MASK;
WWDG->WWDG_CR = reload_value;
return ret_val;
}

/**
 * @ brief Enable WWDG clock
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Enable_WWDG_Clock(void)
{
uint8_t ret_val = E_OK;
SET_BIT(RCC->RCC_APB1ENR,WWDG_CLK_EN_BIT_POS);
return ret_val;
}

/**
 * @ brief Disable WWDG clock
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Disable_WWDG_Clock(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(RCC->RCC_APB1ENR,WWDG_CLK_EN_BIT_POS);
return ret_val;
}
/**
 * @ brief set window value
 * @ param window value (This value range is from 0x40 to 0x7F)
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t WWDG_Set_window_value(WWDG_Prescaler_divider_t Prescaler_divider,uint16_t window_value)
{
uint8_t ret_val = E_OK;
Enable_WWDG_Clock();
window_value |= (Prescaler_divider << WWDG_PRESCALER_BIT_POS);
WWDG->WWDG_CFR = window_value;
return ret_val;
}

/* WWDG interrupt Handler */
void WWDG_IRQHandler(void)
{
CLEAR_BIT(WWDG->WWDG_SR,EARLY_WAKE_FLAG_BIT_POS);
if(WWDG_interrupt_Handler)
{
WWDG_interrupt_Handler();
}
}
