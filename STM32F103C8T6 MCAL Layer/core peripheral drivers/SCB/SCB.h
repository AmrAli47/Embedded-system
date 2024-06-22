/* 
 * File:   SCB.h
 * Author: Amr Ali
 * @brief system control block driver 
 */
#ifndef _SCB_H_
#define _SCB_H_

/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
/*************Macro declarations****************/
#define SCB_BASE_ADDRESS          				0xE000ED00
#define SCB                       				((SCB_t *)SCB_BASE_ADDRESS)
#define USAGE_FAULT_EN_BIT_POS    				18
#define BUS_FAULT_EN_BIT_POS      				17
#define MEM_MANAGE_FAULT_EN_BIT_POS     		16
#define USAGE_FAULT_PENDING_BIT_POS    			12
#define BUS_FAULT_PENDING_BIT_POS      			14
#define MEM_MANAGE_FAULT_PENDING_BIT_POS    	13
#define MEM_MANAGE_FAULT_ADDRESS_VALID_BIT_POS  7
#define BUS_FAULT_ADDRESS_VALID_BIT_POS         15
#define USAGE_FAULT_PRI_BIT_POS                 16
#define BUS_FAULT_PRI_BIT_POS                   8
#define MEMMANAGE_FAULT_PRI_BIT_POS             0
#define SV_CALL_HANDLER_PRI_BIT_POS             24
#define SYSTICK_HANDLER_PRI_BIT_POS             24
#define PEND_SV_HANDLER_PRI_BIT_POS             16
#define NMI_SET_PENDING_BIT_POS                 31
#define PENDSV_SET_PENDING_BIT_POS              28
#define PENDSV_CLEAR_PENDING_BIT_POS            27
#define SYSTICK_SET_PENDING_BIT_POS             26
#define SYSTICK_CLEAR_PENDING_BIT_POS           25
/*************Data Types Declarations****************/
typedef enum
{
Usage_Fault,
Mem_Manage_Fault,
Bus_Fault
}Fault_t;

typedef enum
{
Usage_Fault_Handler,
Bus_Fault_Handler,
mem_manage_Fault_Handler,
SV_Call_Handler,
Systick_Handler,
Pend_SV_Handler
}Handler_t;

typedef enum
{
NMI,
PendSV,
Systick
}Interrupt_t;

typedef struct
{
volatile uint32_t CPUID;
volatile uint32_t ICSR;
volatile uint32_t VTOR;
volatile uint32_t AIRCR;
volatile uint32_t SCR;
volatile uint32_t CCR;
volatile uint32_t SHPR1;
volatile uint32_t SHPR2;
volatile uint32_t SHPR3;
volatile uint32_t SHCRS;
volatile uint32_t CFSR;
volatile uint32_t HFSR;
volatile uint32_t reserved[2];
volatile uint32_t MMAR;
volatile uint32_t BFAR;
volatile uint32_t AFSR;
}SCB_t;


/*************function prototypes****************/
uint8_t Enable_Fault(Fault_t fault);
uint8_t Disable_Fault(Fault_t fault);
uint8_t Fault_Set_Pending_Bit(Fault_t fault);
uint8_t Fault_Clear_Pending_Bit(Fault_t fault);
uint8_t cause_of_MemManage_fault(uint32_t* address);
uint8_t cause_of_Bus_fault(uint32_t* address);
uint8_t set_Handler_Priority(uint8_t priority,Handler_t handler);
uint8_t set_Interrupt_Pending_Bit(Interrupt_t Interrupt_Handler);
uint8_t clear_Interrupt_Pending_Bit(Interrupt_t Interrupt_Handler);
__attribute__((naked)) void Enable_All_Configurable_interrupts(void);
__attribute__((naked)) void Disable_All_Configurable_interrupts(void);
__attribute__((naked)) void Enable_All_interrupts(void);
__attribute__((naked)) void Disable_All_interrupts(void);

#endif
