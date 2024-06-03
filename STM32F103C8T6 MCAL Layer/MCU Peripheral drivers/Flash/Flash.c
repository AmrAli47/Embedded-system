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

/*
 * @brief Read Pages Protection status
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint32_t Read_Flash_WR_Reg(void)
{
return ((uint32_t)(READ_REG(FLASH->FLASH_WRPR)));
}

/*
 * @brief Enable Write Protection for pages
 * @param number of pages -> Note : memory consists of 128 pages and there are 32 bits to control write protection for 128 bits
 * so each bit enable write protection for 4 pages, for example if you want to enable protection for first four pages
 * you need to set first two bits so pages value should be 0x3
 * 1 -> write protection not active, 0 -> write protection active
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t Flash_WR_PR_Enable(uint32_t pages)
{
uint8_t ret_val = E_OK;
uint16_t WRP0_Data = 0xFFFF;
uint16_t WRP1_Data = 0xFFFF;
uint16_t WRP2_Data = 0xFFFF;
uint16_t WRP3_Data = 0xFFFF;

pages = ((uint32_t)(~((~(0xFFFFFFFF)) | pages)));

WRP0_Data = ((uint16_t)((pages & OB_WRP_PAG0_TO_PAG31_MSK)));
WRP1_Data = ((uint16_t)((pages & OB_WRP_PAG32_TO_PAG63_MSK) >> 8));
WRP2_Data = ((uint16_t)((pages & OB_WRP_PAG64_TO_PAG95_MSK) >> 16));
WRP3_Data = ((uint16_t)((pages & OB_WRP_PAG96_TO_PAG127_MSK) >> 24));

while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
Flash_unlock();
Flash_OB_unlock();
SET_BIT(FLASH->FLASH_CR, OB_PROGRAMMING_BIT_POS);

OB->WRP0 &= WRP0_Data;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
OB->WRP1 &= WRP1_Data;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
OB->WRP2 &= WRP2_Data;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
OB->WRP3 &= WRP3_Data;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));

CLEAR_BIT(FLASH->FLASH_CR, OB_PROGRAMMING_BIT_POS);
Flash_OB_lock();
Flash_lock();
return ret_val;
}

/*
 * @brief Disable Write Protection for pages
 * @param number of pages -> Note : memory consists of 128 pages and there are 32 bits to control write protection for 128 bits
 * so each bit disable write protection for 4 pages, for example if you want to enable protection for first four pages
 * you need to set first two bits so pages value should be 0x0
 * 1 -> write protection not active, 0 -> write protection active
 * @return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Flash_WR_PR_Disble(uint32_t pages)
{
uint8_t ret_val = E_OK;
uint16_t WRP0_Data = 0xFFFF;
uint16_t WRP1_Data = 0xFFFF;
uint16_t WRP2_Data = 0xFFFF;
uint16_t WRP3_Data = 0xFFFF;

pages = ((uint32_t)(Read_Flash_WR_Reg() | pages));

WRP0_Data = ((uint16_t)((pages & OB_WRP_PAG0_TO_PAG31_MSK)));
WRP1_Data = ((uint16_t)((pages & OB_WRP_PAG32_TO_PAG63_MSK) >> 8));
WRP2_Data = ((uint16_t)((pages & OB_WRP_PAG64_TO_PAG95_MSK) >> 16));
WRP3_Data = ((uint16_t)((pages & OB_WRP_PAG96_TO_PAG127_MSK) >> 24));

while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
Flash_unlock();
Flash_OB_unlock();
SET_BIT(FLASH->FLASH_CR, OB_PROGRAMMING_BIT_POS);

OB->WRP0 |= WRP0_Data;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
OB->WRP1 |= WRP1_Data;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
OB->WRP2 |= WRP2_Data;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));
OB->WRP3 |= WRP3_Data;
while(READ_BIT(FLASH->FLASH_SR,FLASH_BUSY_FLAG_BIT_POS));

CLEAR_BIT(FLASH->FLASH_CR, OB_PROGRAMMING_BIT_POS);
Flash_OB_lock();
Flash_lock();
return ret_val;
}

