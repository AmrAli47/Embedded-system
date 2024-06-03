/* 
 * File:   systick.h
 * Author: Amr Ali
 * @brief system timer driver driver 
 */
#ifndef _SYSTICK_H_
#define _SYSTICK_H_


/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
/*************Macro declarations****************/
#define SYSTICK_TIMER_BASE_ADDRESS     0XE000E010
#define SYSTICK                        ((systick_Register *)0XE000E010)
#define SYSTICK_TIMER_ENABLE_BIT_POS   	   0
#define SYSTICK_TIMER_EXCEPTION_BIT_POS    1
#define SYSTICK_TIMER_CLOCK_BIT_POS        2
#define SYSTICK_TIMER_FLAG_BIT_POS         16




/*************Data Types Declarations****************/
typedef struct
{
volatile uint32_t SYST_CSR;
volatile uint32_t SYST_RVR;
volatile uint32_t SYST_CVR;
volatile uint32_t SYST_CALIB;
}systick_Register;

typedef enum
{
single_mode,
periodic_mode
}systick_mode_t;

typedef enum
{
Disbale,
Enable
}systick_exception_t;

typedef enum
{
external_clock, /* external clock = processor clock divide by 8 */
processor_clock
}systick_clock_source_t;

typedef struct
{
uint32_t reload_value;
systick_mode_t timer_mode; // @ ref systick_mode_t
systick_exception_t timer_exception; // @ ref systick_exception_t
systick_clock_source_t timer_clock; // @ ref systick_clock_source_t
void (*ptr_function)(void);
}systick_t;


/*************function prototypes****************/
uint8_t configure_systick_timer(systick_t* system_timer);
uint8_t Get_Remaining_Ticks(uint32_t* Remaining_Ticks);
uint8_t Get_Remaining_Ticks(uint32_t* Remaining_Ticks);
uint8_t Get_Elapsed_Ticks(uint32_t* Elsapsed_Ticks);
#endif
