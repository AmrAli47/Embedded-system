/* 
 * File:   	CRC.c
 * Author: Amr Ali
 * @brief Cyclic Redundancy check driver  
 */

#include "CRC.h"
static uint8_t Enable_CRC_clock(void);
static uint8_t Disable_CRC_clock(void);


/**
 * @ brief Calculate CRC, starting with initialization value = 0XFFFFFFFF
 * @ Param pointer to data
 * @ Param Length of data
 * @ Param Pointer to CRC Result
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t CRC_Calculate(uint32_t* pdata,uint8_t len,uint32_t* CRC_Result)
{
uint8_t ret_val = E_OK;
uint8_t i = 0;
Enable_CRC_clock();
SET_BIT(CRC->CRC_CR,RESET_CRC_CALC_UNIT_BIT_POS);
for(i=0;i<len;i++)
{
CRC->CRC_DR = *pdata;
pdata++;
}
*CRC_Result = CRC->CRC_DR;
return ret_val ;
}


/**
 * @ brief Calculate CRC, starting with the previously computed CRC as initialization value
 * @ Param pointer to data
 * @ Param Length of data
 * @ Param Pointer to CRC Result
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t CRC_Accumulate(uint32_t* pdata,uint8_t len,uint32_t* CRC_Result)
{
uint8_t ret_val = E_OK;
uint8_t i = 0;
Enable_CRC_clock();
for(i=0;i<len;i++)
{
CRC->CRC_DR = *pdata;
pdata++;
}
*CRC_Result = CRC->CRC_DR;
return ret_val ;
}



/**
 * @ brief De-initialize CRC Peripheral
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t CRC_DeInit(void)
{
uint8_t ret_val = E_OK;
SET_BIT(CRC->CRC_CR,RESET_CRC_CALC_UNIT_BIT_POS);
Disable_CRC_clock();
return ret_val ;
}



/**
 * @ brief Enable CRC clock
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Enable_CRC_clock(void)
{
uint8_t ret_val = E_OK;
SET_BIT(RCC->RCC_AHBENR,CRC_CLOCK_EN_BIT_POS);
return ret_val ;
}

/**
 * @ brief Disable CRC clock
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Disable_CRC_clock(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(RCC->RCC_AHBENR,CRC_CLOCK_EN_BIT_POS);
return ret_val ;
}
