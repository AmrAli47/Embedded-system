/* 
 * File:   Flash.h
 * Author: Amr Ali
 * @brief Flash driver
 */
#ifndef _FLASH_H_
#define _FLASH_H_



/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
/*************Macro declarations****************/
#define FLASH_BASE_ADDRESS        0x40022000
#define FLASH                     ((FLASH_T *)0x40022000)
#define FLASH_LATENCY_BITS_PIS    		 0
#define FLASH_BUSY_FLAG_BIT_POS    		 0
#define FLASH_MASS_ERASE_BIT_POS   		 2
#define FLASH_PAGE_ERASE_BIT_POS   		 1
#define FLASH_START_ERASE_BIT_POS        6
#define FLASH_KEY1_VALUE                 0x45670123
#define FLASH_KEY2_VALUE                 0xCDEF89AB
#define FLASH_LOCK_BIT_POS               7
#define FLASH_OB_LOCK_BIT_POS			 9
#define OB_PROGRAMMING_BIT_POS           4
#define RDB_LEVEL_0                      0xA5
#define RDB_LEVEL_1                      0x00
#define OB_BASE_ADDRESS                  0x1FFFF800
#define OB								 ((OB_T *)OB_BASE_ADDRESS)
#define FLASH_OB_ERASE_BIT_EN_POS        5


/*************Data Types Declarations****************/
typedef enum
{
zero_wait_state, //if SYSCLK (system clock) 0 < SYSCLK≤ 24 MHz
one_wait_state,  //if SYSCLK (system clock) 24 MHz < SYSCLK ≤ 48 MHz
two_wait_state   //if SYSCLK (system clock) 48 MHz < SYSCLK ≤ 72 MHz
}FLASH_Latency_T;
typedef struct
{
volatile uint32_t FLASH_ACR;
volatile uint32_t FLASH_KEYR;
volatile uint32_t FLASH_OPTKEYR;
volatile uint32_t FLASH_SR;
volatile uint32_t FLASH_CR;
volatile uint32_t FLASH_AR;
volatile uint32_t FLASH_OBR;
volatile uint32_t FLASH_WRPR;
}FLASH_T;

typedef struct
{
volatile uint16_t RDP;
volatile uint16_t USER;
volatile uint16_t Data0;
volatile uint16_t Data1;
volatile uint16_t WRP0;
volatile uint16_t WRP1;
volatile uint16_t WRP2;
volatile uint16_t WRP3;
}OB_T;


/*************function prototypes****************/
uint8_t Flash_lock(void);
uint8_t Flash_unlock(void);
uint8_t Flash_mass_Erase(void);
uint8_t Flash_Page_Erase(uint32_t page_address);
uint8_t Flash_OB_lock(void);
uint8_t Flash_OB_unlock(void);
uint8_t Flash_OB_Launch(void);
uint8_t Flash_OB_RD_PR_Level_config(uint8_t level);
uint8_t Flash_Erase_OB(void);
#endif
