/* 
 * File:   RTC.h
 * Author: Amr Ali
 * @brief Real Time clock driver  
 */
#ifndef _RTC_H_
#define _RTC_H_

/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
#include "BKP.h"
#include "RCC.h"
/*************Macro declarations****************/
#define RTC_BASE_ADDRESS          		0x40002800
#define RTC				          		((RTC_Registers_t *)RTC_BASE_ADDRESS)
#define RTC_CLK_EN_BIT_POS        		15
#define RTC_CLK_SRC_SELEC_BIT_POS  		8
#define RTC_OVFL_INT_EN_BIT_POS     	2
#define RTC_ALARM_INT_EN_BIT_POS    	1
#define RTC_SECOND_INT_EN_BIT_POS   	0
#define RTC_OPERATION_OFF_BIT_POS   	5
#define SECOND_FLAG_BIT_POS         	0
#define ALARM_FLAG_BIT_POS          	1
#define OVERFLOW_FLAG_BIT_POS       	2
#define RTC_ENTER_CONFIG_MOD_BIT_POS	4
#define LOW_ALARM_REG_MSK           	0x0000FFFF
#define HIGH_ALARM_REG_MSK          	0xFFFF0000
#define LOW_PRESCA_REG_MSK				0x0000FFFF
#define HIGH_PRESCA_REG_MSK				0x000F0000
#define LEAP_YEAR						1
#define NOT_LEAP_YEAR                   0
#define LOW_COUNT_REG_MSK       		0x0000FFFF
#define HIGH_COUNT_REG_MSK       		0xFFFF0000
#define ENABLE                          1
#define ALARM_INT_DIS_BIT_POS           0xFD
#define SECND_INT_DIS_BIT_POS           0xFE
#define OVERFL_INT_DIS_BIT_POS          0xFB
/*************Data Types Declarations****************/
typedef enum
{
LSE_used_as_RTC_clock = 1,
LSI_used_as_RTC_clock = 2,
HSE_divided_by_128_used_as_RTC_clock = 3
}RTC_clock_source_t;


typedef enum
{
Disable_Alarm_Interrupt,
Enable_Alarm_Interrupt
}Alarm_Interrupt_t;

typedef enum
{
Disable_seconds_Interrupt,
Enable_seconds_Interrupt
}seconds_Interrupt_t;


typedef enum
{
Disable_overflow_Interrupt,
Enable_overflow_Interrupt
}overflow_Interrupt_t;

typedef struct
{
void (* Alarm_Interrupt_callback)(void);
void (* Seconds_Interrupt_callback)(void);
void (* overflow_Interrupt_callback)(void);
RTC_clock_source_t   RTC_clock_source;
Alarm_Interrupt_t    Alarm_Interrupt;
seconds_Interrupt_t  seconds_Interrupt;
overflow_Interrupt_t overflow_Interrupt;
uint32_t             Alarm_Value;
uint32_t             Presclaer_Value; /* fTR_CLK = fRTCCLK/(PRL[19:0]+1) */
}RTC_t;

typedef struct
{
volatile uint32_t RTC_CRH;
volatile uint32_t RTC_CRL;
volatile uint32_t RTC_PRLH;
volatile uint32_t RTC_PRLL;
volatile uint32_t RTC_DIVH;
volatile uint32_t RTC_DIVL;
volatile uint32_t RTC_CNTH;
volatile uint32_t RTC_CNTL;
volatile uint32_t RTC_ALRH;
volatile uint32_t RTC_ALRL;
}RTC_Registers_t;

/*************function prototypes****************/
uint8_t RTC_Init(RTC_t* _RTC);
uint8_t RTC_DeInit(RTC_t* _RTC);
uint8_t Set_RTC(uint16_t year,uint8_t month,uint8_t date,uint8_t hour,uint8_t minute,uint8_t second);
uint8_t Get_RTC(uint16_t* year,uint8_t* month,uint8_t* date,uint8_t* hour,uint8_t* minute,uint8_t* second);
#endif
