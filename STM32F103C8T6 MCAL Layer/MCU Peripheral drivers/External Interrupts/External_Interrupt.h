/* 
 * File:   External_Interrupt.h
 * Author: Amr Ali
 * @brief External interrupt driver  
 */

#ifndef _EXTERNAL_INTERRUPT_H_
#define _EXTERNAL_INTERRUPT_H_



/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
/*************Macro declarations****************/
#define EXT_INT_BASE_ADDRESS           0x40010400
#define EXT_INT						   ((EXT_INT_T *)0x40010400)
#define EXT_INT_CLOCK_BASE_ADDRESS     0X40021018
#define EXT_INT_CLOCK‬				   (*((uint32_t *)EXT_INT_CLOCK_BASE_ADDRESS))
#define EXT_INT_CLOCK_BIT_POS          0

/*************Data Types Declarations****************/
typedef enum
{
Ext_Int_EV_0,
Ext_Int_EV_1,
Ext_Int_EV_2,
Ext_Int_EV_3,
Ext_Int_EV_4,
Ext_Int_EV_5,
Ext_Int_EV_6,
Ext_Int_EV_7,
Ext_Int_EV_8,
Ext_Int_EV_9,
Ext_Int_EV_10,
Ext_Int_EV_11,
Ext_Int_EV_12,
Ext_Int_EV_13,
Ext_Int_EV_14,
Ext_Int_EV_15,
Ext_Int_EV_16,
Ext_Int_EV_17,
Ext_Int_EV_18
}Ext_Int_Event_t;
typedef enum
{
External_Interurpt,
External_Event
}Request_type_t;
typedef enum
{
Falling_Edge,
Rising_Edge,
Rising_and_Falling_Edge
}Edge_t;
typedef struct
{
volatile uint32_t EXTI_IMR;
volatile uint32_t EXTI_EMR;
volatile uint32_t EXTI_RTSR;
volatile uint32_t EXTI_FTSR;
volatile uint32_t EXTI_SWIER;
volatile uint32_t EXTI_PR;
}EXT_INT_T;

typedef struct
{
Ext_Int_Event_t	Request_Number;
Request_type_t Request_type;
Edge_t 		   Edge;
}Ext_Int_Event_Config_t;


/*************function prototypes****************/
uint8_t Enable_EXT_INT_Clock(void);
uint8_t Disable_EXT_INT_Clock(void);
uint8_t EXT_Req_config(Ext_Int_Event_Config_t *Req);
uint8_t generate_software_interrupt(Ext_Int_Event_t Req);
uint8_t Clear_Pending_Bit(Ext_Int_Event_t Req);

#endif
