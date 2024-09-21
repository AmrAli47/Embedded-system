/* 
 * File:   IWDG.h
 * Author: Amr Ali
 * @brief independent Watchdog Timer driver  
 */

#ifndef _IWDG_H_
#define _IWDG_H_



/*************Includes****************/
#include <stdint.h>
#include <stddef.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\core\inc\SCB.h"
#include "RCC.h"
#include "PWR.h"
/*************Macro declarations****************/
#define IWDG_BASE_ADDRESS               0x40003000
#define IWDG                            ((IWDG_Registers_t *)IWDG_BASE_ADDRESS)
#define IWDG_START_KEY                  0xCCCC
#define EN_ACCESS_KEY                   0x5555
#define IWDG_RELOAD_KEY                 0xAAAA
/*************Data Types Declarations****************/
typedef enum
{
divide_by_4,
divide_by_8,
divide_by_16,
divide_by_32,
divide_by_64,
divide_by_128,
divide_by_256,
}Prescaler_divider_t;

typedef struct
{
uint16_t 			 reload_value;
Prescaler_divider_t  Prescaler_divider;
}IWDG_t;

typedef struct
{
volatile uint32_t IWDG_KR;
volatile uint32_t IWDG_PR;
volatile uint32_t IWDG_RLR;
volatile uint32_t IWDG_SR;
}IWDG_Registers_t;


/*************function prototypes****************/
uint8_t start_IWDG(void);
uint8_t IWDG_Init(IWDG_t* _IWDG);
uint8_t IWDG_referesh(void);
#endif
