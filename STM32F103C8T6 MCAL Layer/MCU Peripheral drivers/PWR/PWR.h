/* 
 * File:   PWR.h
 * Author: Amr Ali
 * @brief Power Control driver  
 */

#ifndef _PWR_H_
#define _PWR_H_

/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\core\inc\SCB.h"
#include "RCC.h"
#include "External_Interrupt.h"
/*************Macro declarations****************/
#define PWR_BASE_ADDRESS         			0x40007000
#define PWR                      			((PWR_Registers_t *)PWR_BASE_ADDRESS)
#define SLEEP_DEEP_SLEEP_MODE_BIT_POS		2
#define SLEEP_ON_EXIT_BIT_POS               1
#define POWER_DOWN_DEEPSLEEP_BIT_POS        1
#define VOLTAGE_REGULATOR_MODE_BIT_POS      0
#define WAKEUP_PIN_BIT_POS                  8
#define PVD_EN_BIT_POS                      4
#define PVD_EXTI_BIT_POS                    16
#define PVD_LEVEL_SELECTION_BIT_POS         5
#define PWR_CLOCK_EN_BIT_POS                28
#define PVD_LEVEL_SELECTION_MSK             0x7
#define WFI()                               asm volatile("WFI") /* wait for interrupt */
#define WFE()                               asm volatile("WFE") /* wait for event*/
#define ENABLE_CONFIG_BIT_POS               4

/*************Data Types Declarations****************/
typedef enum
{
wait_for_interrupt,
wait_for_event
}sleep_exit_mode_t;

typedef enum
{
sleep_now,
sleep_on_exit
}sleep_entery_mode_t;

typedef enum
{
voltage_regulator_normal_mode,
voltage_regulator_low_power_mode
}voltage_regulator_mode_t;

typedef enum
{
Level0, 	/*Level0 -> 2.2V */
Level1, 	/*Level1 -> 2.3V */
Level2, 	/*Level2 -> 2.4V */
Level3, 	/*Level3 -> 2.5V */
Level4, 	/*Level4 -> 2.6V */
Level5, 	/*Level5 -> 2.7V */
Level6, 	/*Level6 -> 2.8V */
Level7		/*Level7 -> 2.9V */
}PVD_level_selection_t;

typedef enum
{
PVD_Event,
PVD_Interrupt
}PVD_mode_t;

typedef enum
{
PVD_Rising_Edge,
PVD_Falling_Edge
}PVD_Edge_t;

typedef enum
{
Events_and_Enabled_Interrupts_only_wakeup_the_processor,
Events_and_All_Interrupts_wakeup_the_processor
}wakeup_t;

typedef struct
{
void (*PVD_Callback)(void);
PVD_level_selection_t PVD_Level;
PVD_mode_t            mode;
PVD_Edge_t            edge;
}PVD_config_t;


typedef struct
{
volatile uint32_t PWR_CR;
volatile uint32_t PWR_CSR;
}PWR_Registers_t;


/*************function prototypes****************/
uint8_t Enter_sleep_mode(sleep_entery_mode_t sleep_mode_entry,sleep_exit_mode_t sleep_exit_mode);
uint8_t Enter_stop_mode(sleep_exit_mode_t sleep_exit_mode,voltage_regulator_mode_t voltage_regulator_mode);
uint8_t Enter_standby_mode(void);
uint8_t Processor_Wakeup_config(wakeup_t WKU);
uint8_t Enable_wakeup_pin(void);
uint8_t Disable_wakeup_pin(void);
uint8_t PVD_Init(PVD_config_t* PVD);
uint8_t PVD_DeInit(void);
#endif
