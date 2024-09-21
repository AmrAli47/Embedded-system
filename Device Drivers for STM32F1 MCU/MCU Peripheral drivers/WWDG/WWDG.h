/* 
 * File:   WWDG.h
 * Author: Amr Ali
 * @brief Window Watchdog Timer driver  
 */

#ifndef _WWDG_H_
#define _WWDG_H_



/*************Includes****************/
#include <stdint.h>
#include <stddef.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\core\inc\SCB.h"
#include "RCC.h"
/*************Macro declarations****************/
#define WWDG_BASE_ADDRESS               0x40002C00
#define WWDG                            ((WWDG_Registers_t *)WWDG_BASE_ADDRESS)
#define WWDG_CLK_EN_BIT_POS             11
#define WWDG_PRESCALER_BIT_POS          7
#define WWDG_PRESCALER_MSK              0x3
#define WWDG_MASK                       0x80
#define EARLY_WAKE_INT_EN_BIT_POS       9
#define EARLY_WAKE_FLAG_BIT_POS         0
#define WWDG_ACTIVATION_BIT_POS         7
/*************Data Types Declarations****************/
typedef enum
{
WWDG_divide_by_1,
WWDG_divide_by_2,
WWDG_divide_by_4,
WWDG_divide_by_8
}WWDG_Prescaler_divider_t;

typedef enum
{
Disable_Early_wakeup_interrupt,
Enable_Early_wakeup_interrupt
}Early_wakeup_interrupt_t;

typedef struct
{
void (* WWDG_interrupt_callback)(void);
WWDG_Prescaler_divider_t  Prescaler_divider;
Early_wakeup_interrupt_t  Early_wakeup_interrupt;
}WWDG_t;

typedef struct
{
volatile uint32_t WWDG_CR;
volatile uint32_t WWDG_CFR;
volatile uint32_t WWDG_SR;
}WWDG_Registers_t;


/*************function prototypes****************/
uint8_t WWDG_Init(WWDG_t* _WWDG);
uint8_t WWDG_DeInit(void);
uint8_t WWDG_Refersh(uint8_t reload_value);
uint8_t WWDG_Set_window_value(WWDG_Prescaler_divider_t Prescaler_divider,uint16_t window_value);
#endif
