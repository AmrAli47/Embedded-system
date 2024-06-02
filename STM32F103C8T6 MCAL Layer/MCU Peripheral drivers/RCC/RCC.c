/* 
 * File:   RCC.c
 * Author: Amr Ali
 * @brief Reset and clock control driver 
 */

#include "RCC.h"

static uint8_t select_oscillator(RCC_OSC_Init_t* osc);
static uint8_t set_PLL_configuration(PLL_Type_t* PLL_t);
static uint8_t HSE_Pre_Division_factor_config(PLL_Type_t* PLL_t);

/**
 * @brief oscillator configuration
 * @param clock configurtion @param RCC_OSC_Init_t
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t RCC_osc_Config(RCC_OSC_Init_t* osc)
{
uint8_t ret_val = E_OK;
ret_val = select_oscillator(osc);
ret_val |= set_PLL_configuration(&(osc->PLL));
return ret_val;
}


/**
 * @brief select oscillator
 * @param reference to oscillator configuration @param RCC_OSC_Init_t
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
static uint8_t select_oscillator(RCC_OSC_Init_t* osc)
{
uint8_t ret_val = E_OK;
switch(osc->oscillator_type)
{
case High_Speed_External_Oscillator:
switch(osc->Ext_OSC)
{
case High_Speed_External_Oscillator_Not_bypassed: CLEAR_BIT(RCC->RCC_CR,EXTERNAL_OSC_BYPASS_BIT); break;
case High_Speed_External_Oscillator_bypassed: 	  SET_BIT(RCC->RCC_CR,EXTERNAL_OSC_BYPASS_BIT); break;
default : ret_val = E_NOK;
}
SET_BIT(RCC->RCC_CR,RCC_CR_HSEON_POS);
while(!(READ_BIT(RCC->RCC_CR,RCC_CR_HSE_READY_FLAG_POS)));
break;
case High_Speed_Internal_Oscillator:
SET_BIT(RCC->RCC_CR,RCC_CR_HSION_POS);
while(!(READ_BIT(RCC->RCC_CR,RCC_CR_HSI_READY_FLAG_POS)));
break;
default : ret_val = E_NOK;
}
return ret_val;
}



/**
 * @brief set PLL Configuration
 * @param reference to PLL Configuration
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
static uint8_t set_PLL_configuration(PLL_Type_t* PLL_t)
{
uint8_t ret_val = E_OK;
uint32_t reg_temp = 0;
switch(PLL_t->PLL_State)
{
case PLL_DISBLE: CLEAR_BIT(RCC->RCC_CR,PLL_BIT_POS); break;
case PLL_ENABLE:
reg_temp = RCC->RCC_CFGR;
reg_temp &= ~(PLL_SOURCE_BITS_MASK << PLL_SOURCE_BITS_POS);
reg_temp &= ~(PLL_MUL_BITS_MASK << PLL_MUL_BITS_POS);
reg_temp |=  ((PLL_t->PLL_Source) << PLL_SOURCE_BITS_POS);
switch(PLL_t->PLL_Source)
{
case PLL_HSI_oscillator: CLEAR_BIT(RCC->RCC_CFGR,PLL_SOURCE_BITS_POS); break;
case PLL_HSE_oscillator: HSE_Pre_Division_factor_config(PLL_t); break;
default : ret_val = E_NOK;
}
reg_temp |=  ((PLL_t->PLL_mul_factor) << PLL_MUL_BITS_POS);
RCC->RCC_CFGR |= reg_temp;
SET_BIT(RCC->RCC_CR,PLL_BIT_POS);
while(!(READ_BIT(RCC->RCC_CR,PLL_READY_FLAG)));
break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 * @brief configure external oscillator division factor
 * @param reference to PLL Configuration @ref PLL_Type_t
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
static uint8_t HSE_Pre_Division_factor_config(PLL_Type_t* PLL_t)
{
uint8_t ret_val = E_OK;
uint32_t reg_temp = 0;
reg_temp = RCC->RCC_CFGR;
reg_temp &= ~(PLL_PRI_DIV_MASK << PLL_PRI_DIV_POS);
reg_temp |=  ((PLL_t->HSE_Pri_dev_fc) << PLL_PRI_DIV_POS);
SET_BIT(RCC->RCC_CFGR,PLL_SOURCE_BITS_POS);
RCC->RCC_CFGR |= reg_temp;
return ret_val;
}

/**
 * @brief configure system clock
 * @param reference to clock Configuration @ref RCC_CLK_Init_t
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t RCC_clk_Config(RCC_CLK_Init_t* clk)
{
uint32_t reg_temp = 0;
uint8_t ret_val = E_OK;
/* increase flash memory latency to be compatible with CPU speed */
FLASH_ACR_REG |= (FLASH_LATENCY_BIT_MSK << FLASH_LATENCY_BIT_POS);
reg_temp = RCC->RCC_CFGR;
reg_temp |= (clk->clock_type << SYSTEM_CLK_BIT_POS);
reg_temp |= (clk->AHB_Prescaler << AHB_PRESCALER_BIT_POS);
reg_temp |= (clk->APB1_Prescaler << APB1_PRESCALER_BIT_POS);
reg_temp |= (clk->APB2_Prescaler << APB2_PRESCALER_BIT_POS);
RCC->RCC_CFGR = reg_temp;
return ret_val;
}






