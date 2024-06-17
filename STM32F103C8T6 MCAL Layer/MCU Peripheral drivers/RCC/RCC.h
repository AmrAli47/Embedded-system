/* 
 * File:   RCC.h
 * Author: Amr Ali
 * @brief Reset and clock control driver  
 */

 
#ifndef _RCC_H_
#define _RCC_H_

/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
/*************Macro declarations****************/
#define RCC_BASE_ADDRESS (0x40021000)
#define RCC              ((RCC_Type_t *)(RCC_BASE_ADDRESS))
#define RCC_CR_HSEON_POS    		16UL
#define RCC_CR_HSION_POS    		0UL
#define RCC_CR_HSE_READY_FLAG_POS   17U
#define RCC_CR_HSI_READY_FLAG_POS   1U
#define PLL_DISABLE_VAL             0U
#define PLL_ENABLE_VAL              1U
#define PLL_BIT_POS                 24U
#define PLL_MUL_BITS_POS            18U
#define PLL_SOURCE_BITS_POS         16U
#define PLL_SOURCE_BITS_MSK         1U
#define PLL_PRI_DIV_POS             17U
#define PLL_MUL_BITS_MASK		    (uint32_t)0x0F
#define PLL_SOURCE_BITS_MASK        (uint32_t)0x01
#define PLL_PRI_DIV_MASK            (uint32_t)0x01
#define PLL_READY_FLAG              25U
#define SYSTEM_CLK_BIT_POS 			0
#define AHB_PRESCALER_BIT_POS 	    4
#define APB1_PRESCALER_BIT_POS 	    8
#define APB2_PRESCALER_BIT_POS 	    11
#define FLASH_ACR_REG               (*((uint32_t *)0x40022000))
#define FLASH_LATENCY_BIT_POS       0
#define FLASH_LATENCY_BIT_MSK       2
#define EXTERNAL_OSC_BYPASS_BIT     18U
#define AHB_PRESCLAER_BIT_POS       4
#define AHB_PRESCLAER_MSK           0xF
#define APB_PRESCLAER_MSK           0x7
#define HSI_VALUE                   8000000


/*************Data Types Declarations****************/

typedef struct
{
volatile uint32_t RCC_CR;
volatile uint32_t RCC_CFGR;
volatile uint32_t RCC_CIR;
volatile uint32_t RCC_APB2RSTR;
volatile uint32_t RCC_APB1RSTR;
volatile uint32_t RCC_AHBENR;
volatile uint32_t RCC_APB2ENR;
volatile uint32_t RCC_APB1ENR;
volatile uint32_t RCC_BDCR;
volatile uint32_t RCC_CSR;
volatile uint32_t RCC_AHBSTR;
volatile uint32_t RCC_CFGR2;
}RCC_Type_t;

typedef enum
{
High_Speed_External_Oscillator,
High_Speed_Internal_Oscillator,
}OSC_Type_t;

typedef enum
{
High_Speed_External_Oscillator_Not_bypassed,
High_Speed_External_Oscillator_bypassed,
}Ext_oscillator_t;

typedef enum
{
HSI_Selected_as_system_clock,
HSE_Selected_as_system_clock,
PLL_Selected_as_system_clock,
}Clock_Type_t;

typedef enum
{
AHB_Prescaler_DIV_BY_1   = 0,
AHB_Prescaler_DIV_BY_2   = 8,
AHB_Prescaler_DIV_BY_4   = 9,
AHB_Prescaler_DIV_BY_8   = 10,
AHB_Prescaler_DIV_BY_16   = 11,
AHB_Prescaler_DIV_BY_46   = 12,
AHB_Prescaler_DIV_BY_128  = 13,
AHB_Prescaler_DIV_BY_256  = 14,
AHB_Prescaler_DIV_BY_512  = 15
}AHB_Prescaler_Type_t;

typedef enum
{
APB_Prescaler_DIV_BY_1    = 0,
APB_Prescaler_DIV_BY_2    = 4,
APB_Prescaler_DIV_BY_4    = 5,
APB_Prescaler_DIV_BY_8    = 6,
APB_Prescaler_DIV_BY_16   = 7
}APB_Prescaler_Type_t;

typedef enum
{
PLL_DISBLE,
PLL_ENABLE
}PLL_state_T;

typedef enum
{
PLL_MUL_2 = 0,
PLL_MUL_3 = 1,
PLL_MUL_4 = 2,
PLL_MUL_5 = 3,
PLL_MUL_6 = 4,
PLL_MUL_7 = 5,
PLL_MUL_8 = 6,
PLL_MUL_9 = 7,
PLL_MUL_10 = 8,
PLL_MUL_11 = 9,
PLL_MUL_12 = 10,
PLL_MUL_13 = 11,
PLL_MUL_14 = 12,
PLL_MUL_15 = 13,
PLL_MUL_16 = 14,
}PLL_mul_T;

typedef enum
{
PLL_HSI_oscillator,
PLL_HSE_oscillator
}PLL_Source_t;

typedef enum
{
Pre_Div_1,
Pre_Div_2,
}PLL_HSE_Pre_divison_factor_t;

typedef struct
{
PLL_Source_t   PLL_Source;
PLL_state_T    PLL_State;
PLL_mul_T      PLL_mul_factor;
PLL_HSE_Pre_divison_factor_t HSE_Pri_dev_fc; // used in case of source was HSE
}PLL_Type_t;

typedef struct
{
OSC_Type_t oscillator_type;             // @ref OSC_Type_t
Ext_oscillator_t Ext_OSC;			   // @ref Ext_oscillator_t used only in case oscillator type was external oscillator
PLL_Type_t           PLL;             // @ref PLL_Type_t
uint32_t 		Ext_OSC_VAL;          // this value range from 4 MHZ -> 16 MHZ
}RCC_OSC_Init_t;

typedef struct
{
Clock_Type_t 		 clock_type;         // @ref Clock_Type_t
AHB_Prescaler_Type_t AHB_Prescaler;     // @ref AHB_Prescaler_Type_t
APB_Prescaler_Type_t APB1_Prescaler;   // @ref APB_Prescaler_Type_t
APB_Prescaler_Type_t APB2_Prescaler;  // @ref APB_Prescaler_Type_t
}RCC_CLK_Init_t;

/*************function prototypes****************/
uint8_t RCC_osc_Config(RCC_OSC_Init_t* osc);
uint8_t RCC_clk_Config(RCC_CLK_Init_t* clk);
uint8_t get_SYSCLK_clock(RCC_OSC_Init_t* osc,uint32_t* SYSCLK_val);
uint8_t get_HCLK_clock(RCC_OSC_Init_t* osc,uint32_t* HCLK_val);
uint8_t get_PCLK1_clock(RCC_OSC_Init_t* osc,uint32_t* PCLK1_val);
uint8_t get_PCLK2_clock(RCC_OSC_Init_t* osc,uint32_t* PCLK2_val);
#endif

