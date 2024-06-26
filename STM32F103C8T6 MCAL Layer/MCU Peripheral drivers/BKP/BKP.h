/* 
 * File:   BKP.h
 * Author: Amr Ali
 * @brief Backup Register driver  
 */

#ifndef _BKP_H_
#define _BKP_H_



/*************Includes****************/
#include <stdint.h>
#include <stddef.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\core\inc\SCB.h"
#include "RCC.h"
#include "PWR.h"
/*************Macro declarations****************/
#define BKP_BASE_ADDRESS         			0x40006C04
#define BKP                      			((BKP_Registers_t *)BKP_BASE_ADDRESS)
#define BKP_CLOCK_EN_BIT_POS                27
#define BKP_WR_ACCESS_EN_BIT_POS            8
#define TAMPER_PIN_EN_BIT_POS               0
#define TAMPER_PIN_ACT_LEVEL_POS            1
#define TAMPER_INT_EN_BIT_POS               2
#define TAMPER_CLEAR_EVENT_FLAG_BIT_POS     0
#define TAMPER_CLEAR_INT_FLAG_BIT_POS       1
#define CLEAR_BKP_REGISTER                  0x0000
#define ALARM_SECOND_OUT_EN_BIT_POS         8
#define ALARM_OR_SECOND_OUT_SELEC_BIT_POS   9
#define READ_RTC_CLK_EN_BIT_POS             7
#define RTC_CALB_MSK_VALUE                  0x7f
/*************Data Types Declarations****************/
typedef enum
{
High_level_on_Pin_reset_BKP_Registers,
Low_level_on_Pin_reset_BKP_Registers
}TAMPER_Pin_Active_Level_t;

typedef enum
{
Enable_TAMPER_Interrupt,
Disable_TAMPER_Interrupt
}TAMPER_Interrupt_t;


typedef struct
{
void (* Tamper_Interrupt_Callback)(void);
TAMPER_Pin_Active_Level_t	TAMPER_Pin_Active_Level;
TAMPER_Interrupt_t          TAMPER_Interrupt;
}TAMPER_Config_t;

typedef enum
{
RTC_Alarm_pulse_output_selected,
RTC_Second_pulse_output_selected
}Alarm_second_output_selection_t;

typedef struct
{
volatile uint32_t BKP_DR[10]; /* you can store 20 Bytes of data in registers form DR1 -> DR10 */
volatile uint32_t BKP_RTCCR;
volatile uint32_t BKP_CR;
volatile uint32_t BKP_CSR;
}BKP_Registers_t;


/*************function prototypes****************/
uint8_t Enable_write_access_to_BKP(void);
uint8_t Disable_write_access_to_BKP(void);
uint8_t Tamper_Init(TAMPER_Config_t* Tamper);
uint8_t Tamper_DeInit(void);
uint8_t store_2_bytes(uint8_t register_number,uint16_t data);
uint8_t Alarm_or_second_output_Enable(Alarm_second_output_selection_t Alarm_second_output_selection);
uint8_t Read_RTC_Clock(void);
uint8_t Set_RTC_Calibration_value(uint8_t value);
#endif