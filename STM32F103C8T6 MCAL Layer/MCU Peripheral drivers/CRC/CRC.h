/* 
 * File:   	CRC.h
 * Author: Amr Ali
 * @brief Cyclic Redundancy check driver  
 */
#ifndef _CRC_H_
#define _CRC_H_

/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
#include "RCC.h"
/*************Macro declarations****************/
#define CRC_BASE_ADDRESS               0x40023000
#define CRC							   ((CRC_t *)CRC_BASE_ADDRESS)
#define CRC_CLOCK_EN_BIT_POS           6
#define RESET_CRC_CALC_UNIT_BIT_POS    0

/*************Data Types Declarations****************/
typedef struct
{
volatile uint32_t CRC_DR;
volatile uint32_t CRC_IDR;
volatile uint32_t CRC_CR;
}CRC_t;


/*************function prototypes****************/
uint8_t CRC_Calculate(uint32_t* pdata,uint8_t len,uint32_t* CRC_Result);
uint8_t CRC_Accumulate(uint32_t* pdata,uint8_t len,uint32_t* CRC_Result);
uint8_t CRC_DeInit(void);

#endif
