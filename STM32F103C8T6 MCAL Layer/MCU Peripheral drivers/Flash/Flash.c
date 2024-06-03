/* 
 * File:   Flash.c
 * Author: Amr Ali
 * @brief Flash driver
 */

#include <Flash.h>


/*
 * @brief Erase Flash memory except information block (you should call Flash unlock function before call this function)
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Flash_mass_Erase(void)
{
uint8_t ret_val = E_OK;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
SET_BIT(FLASH->FLASH_CR,FLASH_MASS_ERASE_BIT_POS);
SET_BIT(FLASH->FLASH_CR,FLASH_START_ERASE_BIT_POS);
while((READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS)));
return ret_val;
}

/*
 * @brief lock flash (disable accessibility to write to flash memory control registers)
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t Flash_lock(void)
{
uint8_t ret_val = E_OK;
SET_BIT(FLASH->FLASH_CR,FLASH_LOCK_BIT_POS);
return ret_val;
}

/*
 * @brief unlock flash (Enable accessibility to write to flash memory control registers)
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t Flash_unlock(void)
{
uint8_t ret_val = E_OK;
FLASH->FLASH_KEYR = FLASH_KEY1_VALUE;
FLASH->FLASH_KEYR = FLASH_KEY2_VALUE;
return ret_val;
}

/*
 * @brief erase specific page from flash memory (Note : To use this function, clock must be HSI)
 * @param page address
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Flash_Page_Erase(uint32_t page_address)
{
uint8_t ret_val = E_OK;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
SET_BIT(FLASH->FLASH_CR,FLASH_PAGE_ERASE_BIT_POS);
FLASH->FLASH_AR = page_address;
SET_BIT(FLASH->FLASH_CR,FLASH_START_ERASE_BIT_POS);
while((READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS)));
return ret_val;
}

/*
 * @brief unlock option byte
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Flash_OB_unlock(void)
{
uint8_t ret_val = E_OK;
FLASH->FLASH_OPTKEYR = FLASH_KEY1_VALUE;
FLASH->FLASH_OPTKEYR = FLASH_KEY2_VALUE;
return ret_val;
}


/*
 * @brief lock option byte
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Flash_OB_lock(void)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(FLASH->FLASH_CR,FLASH_OB_LOCK_BIT_POS);
return ret_val;
}

/*
 * @brief erase option bytes
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Flash_Erase_OB(void)
{
uint8_t ret_val = E_OK;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
Flash_unlock();
Flash_OB_unlock();
SET_BIT(FLASH->FLASH_CR,FLASH_OB_ERASE_BIT_EN_POS);
SET_BIT(FLASH->FLASH_CR,FLASH_START_ERASE_BIT_POS);
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
CLEAR_BIT(FLASH->FLASH_CR,FLASH_OB_ERASE_BIT_EN_POS);
Flash_OB_lock();
Flash_lock();
return ret_val;
}


/*
 * @brief select read protection level
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Flash_OB_RD_PR_Level_config(uint8_t level)
{
uint8_t ret_val = E_OK;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
Flash_unlock();
Flash_OB_unlock();
SET_BIT(FLASH->FLASH_CR,OB_PROGRAMMING_BIT_POS);
OB->RDP = level;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
CLEAR_BIT(FLASH->FLASH_CR, OB_PROGRAMMING_BIT_POS);
Flash_OB_lock();
Flash_lock();
return ret_val;
}









