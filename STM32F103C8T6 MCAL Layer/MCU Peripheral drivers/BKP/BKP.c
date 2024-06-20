/* 
 * File:   BKP.c
 * Author: Amr Ali
 * @brief Backup Register driver  
 */

#include "BKP.h"
void (* Tamper_Interrupt_Handler)(void);

/**
 * @ brief Enable Write Access to Backup Registers
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Enable_write_access_to_BKP(void)
{
uint8_t ret_val = E_OK;
SET_BIT(RCC->RCC_APB1ENR,PWR_CLOCK_EN_BIT_POS);
SET_BIT(RCC->RCC_APB1ENR,BKP_CLOCK_EN_BIT_POS);
SET_BIT(PWR->PWR_CR,BKP_WR_ACCESS_EN_BIT_POS);
return ret_val;
}

/**
 * @ brief Initialize TAMPER
 * @ param pointer to TAMPER configuration @ref TAMPER_Config_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Tamper_Init(TAMPER_Config_t* Tamper)
{
uint8_t ret_val = E_OK;
if(High_level_on_Pin_reset_BKP_Registers == Tamper->TAMPER_Pin_Active_Level)
{
CLEAR_BIT(BKP->BKP_CR,TAMPER_PIN_ACT_LEVEL_POS);
}
else if(High_level_on_Pin_reset_BKP_Registers == Tamper->TAMPER_Pin_Active_Level)
{
SET_BIT(BKP->BKP_CR,TAMPER_PIN_ACT_LEVEL_POS);
}
else
{
ret_val = E_NOK;
}
if(Enable_TAMPER_Interrupt == Tamper->TAMPER_Interrupt)
{
SET_BIT(BKP->BKP_CSR,TAMPER_INT_EN_BIT_POS);
Tamper_Interrupt_Handler = Tamper->Tamper_Interrupt_Callback;
}
else if(Disable_TAMPER_Interrupt == Tamper->TAMPER_Interrupt)
{
CLEAR_BIT(BKP->BKP_CSR,TAMPER_INT_EN_BIT_POS);
Tamper_Interrupt_Handler = NULL;
}
else
{
ret_val = E_NOK;
}
SET_BIT(BKP->BKP_CSR,TAMPER_CLEAR_EVENT_FLAG_BIT_POS);
SET_BIT(BKP->BKP_CSR,TAMPER_CLEAR_INT_FLAG_BIT_POS);
SET_BIT(BKP->BKP_CR,TAMPER_PIN_EN_BIT_POS);
return ret_val;
}

/**
 * @ brief De-initialize TAMPER
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Tamper_DeInit(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(BKP->BKP_CR,TAMPER_PIN_EN_BIT_POS);
CLEAR_BIT(BKP->BKP_CSR,TAMPER_INT_EN_BIT_POS);
SET_BIT(BKP->BKP_CSR,TAMPER_CLEAR_EVENT_FLAG_BIT_POS);
SET_BIT(BKP->BKP_CSR,TAMPER_CLEAR_INT_FLAG_BIT_POS);
return ret_val;
}

/**
 * @ brief  store two bytes in backup register
 * @ param register number (There is 10 Backup registers so register number range is from 0 to 9,each register can store
 *   16 bits in it)
 * @ param data which will be stored in BKP Register
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t store_2_bytes(uint8_t register_number,uint16_t data)
{
uint8_t ret_val = E_OK;
if(register_number <= 9)
{
BKP->BKP_DR[register_number] = CLEAR_BKP_REGISTER;
BKP->BKP_DR[register_number] = data;
}
else
{
ret_val = E_NOK;
}
return ret_val;
}

/* Tamper interrupt Handler */
void TAMPER_IRQHandler(void)
{
SET_BIT(BKP->BKP_CSR,TAMPER_CLEAR_EVENT_FLAG_BIT_POS);
SET_BIT(BKP->BKP_CSR,TAMPER_CLEAR_INT_FLAG_BIT_POS);
if(Tamper_Interrupt_Handler)
{
Tamper_Interrupt_Handler();
}
}

/**
 * @ brief outputs RTC Alarm or RTC second Pulse on TAMPER Pin -> PC13
 * @ param output selection RTC Alarm or RTC second pulse @ ref  Alarm_second_output_selection_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Alarm_or_second_output_Enable(Alarm_second_output_selection_t Alarm_second_output_selection)
{
uint8_t ret_val = E_OK;
SET_BIT(BKP->BKP_RTCCR,ALARM_SECOND_OUT_EN_BIT_POS);
if(RTC_Alarm_pulse_output_selected == Alarm_second_output_selection)
{
CLEAR_BIT(BKP->BKP_RTCCR,ALARM_OR_SECOND_OUT_SELEC_BIT_POS);
}
else if(RTC_Second_pulse_output_selected == Alarm_second_output_selection)
{
SET_BIT(BKP->BKP_RTCCR,ALARM_OR_SECOND_OUT_SELEC_BIT_POS);
}
else
{
ret_val = E_NOK;
}

return ret_val;
}

/**
 * @ brief outputs RTC clock on TAMPER Pin (output on TAMPER Pin will be RTC Frequency / 64)
 * for example if RTC Frequency was 32768 HZ, output frequency on PC13 Pin will be 512 HZ which is 32768 / 64
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Read_RTC_Clock(void)
{
uint8_t ret_val = E_OK;
SET_BIT(BKP->BKP_RTCCR,READ_RTC_CLK_EN_BIT_POS);
return ret_val;
}

/**
 * @ brief Set RTC Calibration value
 * @ param calibration value (value range is from 0 to 127)
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t Set_RTC_Calibration_value(uint8_t value)
{
uint8_t ret_val = E_OK;
if((0 <= value) && (value <= 127))
{
BKP->BKP_RTCCR &= ~RTC_CALB_MSK_VALUE;
BKP->BKP_RTCCR |= value;
}
else
{
ret_val = E_NOK;
}
return ret_val;
}
