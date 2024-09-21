/* 
 * File:   SCB.c
 * Author: Amr Ali
 * @brief system control block driver 
 */
#include "SCB.h"

/**
 *@ brief Enable specific Fault
 *@ param Fault @ref Fault_t
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Enable_Fault(Fault_t fault)
{
uint8_t ret_val = E_OK;
switch(fault)
{
case Usage_Fault: SET_BIT(SCB->SHCRS,USAGE_FAULT_EN_BIT_POS); break;
case Mem_Manage_Fault: SET_BIT(SCB->SHCRS,MEM_MANAGE_FAULT_EN_BIT_POS); break;
case Bus_Fault:	SET_BIT(SCB->SHCRS,BUS_FAULT_EN_BIT_POS);	break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief Disable specific Fault
 *@ param Fault @ref Fault_t
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Disable_Fault(Fault_t fault)
{
uint8_t ret_val = E_OK;
switch(fault)
{
case Usage_Fault: CLEAR_BIT(SCB->SHCRS,USAGE_FAULT_EN_BIT_POS); break;
case Mem_Manage_Fault: CLEAR_BIT(SCB->SHCRS,MEM_MANAGE_FAULT_EN_BIT_POS); break;
case Bus_Fault:	CLEAR_BIT(SCB->SHCRS,BUS_FAULT_EN_BIT_POS);	break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief Set Pending Bit for specific Fault
 *@ param Fault @ref Fault_t
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Fault_Set_Pending_Bit(Fault_t fault)
{
uint8_t ret_val = E_OK;
switch(fault)
{
case Usage_Fault: SET_BIT(SCB->SHCRS,USAGE_FAULT_PENDING_BIT_POS); break;
case Mem_Manage_Fault: SET_BIT(SCB->SHCRS,MEM_MANAGE_FAULT_PENDING_BIT_POS); break;
case Bus_Fault:	SET_BIT(SCB->SHCRS,BUS_FAULT_PENDING_BIT_POS);	break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief Clear Pending Bit for specific Fault
 *@ param Fault @ref Fault_t
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t Fault_Clear_Pending_Bit(Fault_t fault)
{
uint8_t ret_val = E_OK;
switch(fault)
{
case Usage_Fault: CLEAR_BIT(SCB->SHCRS,USAGE_FAULT_PENDING_BIT_POS); break;
case Mem_Manage_Fault: CLEAR_BIT(SCB->SHCRS,MEM_MANAGE_FAULT_PENDING_BIT_POS); break;
case Bus_Fault:	CLEAR_BIT(SCB->SHCRS,BUS_FAULT_PENDING_BIT_POS);	break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief Read address of the location that generated a MemManage fault
 *@ param address
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t cause_of_MemManage_fault(uint32_t* address)
{
uint8_t ret_val = E_OK;
/* check if  MMAR holds a valid fault address */
if(READ_BIT(SCB->CFSR,MEM_MANAGE_FAULT_ADDRESS_VALID_BIT_POS))
{
*address = SCB->MMAR;
}
else
{
/* processor will come here if  MMAR holds a invalid fault address */
*address = 0;
}
return ret_val;
}



/**
 *@ brief Read address of the location that generated a Bus fault
 *@ param address
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t cause_of_Bus_fault(uint32_t* address)
{
uint8_t ret_val = E_OK;
/* check if  MMAR holds a valid fault address */
if(READ_BIT(SCB->CFSR,BUS_FAULT_ADDRESS_VALID_BIT_POS))
{
*address = SCB->BFAR;
}
else
{
/* processor will come here if  MMAR holds a invalid fault address */
*address = 0;
}
return ret_val;
}


/**
 *@ brief set Handler Priority
 *@ param priority value
 *@ param handler
 *@ param address
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t set_Handler_Priority(uint8_t priority,Handler_t handler)
{
uint8_t ret_val = E_OK;
switch(handler)
{
case Usage_Fault_Handler: 		 SCB->SHPR1 |= (priority << USAGE_FAULT_PRI_BIT_POS); break;
case Bus_Fault_Handler:   		 SCB->SHPR1 |= (priority << BUS_FAULT_PRI_BIT_POS); break;
case mem_manage_Fault_Handler:   SCB->SHPR1 |= (priority << MEMMANAGE_FAULT_PRI_BIT_POS); break;
case SV_Call_Handler: 			 SCB->SHPR2 |= (priority << SV_CALL_HANDLER_PRI_BIT_POS); break;
case Systick_Handler: 			 SCB->SHPR3 |= (priority << SYSTICK_HANDLER_PRI_BIT_POS); break;
case Pend_SV_Handler: 			 SCB->SHPR3 |= (priority << PEND_SV_HANDLER_PRI_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief set Pending Bit for specific interrupt
 *@ param Interrupt
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t set_Interrupt_Pending_Bit(Interrupt_t Interrupt_Handler)
{
uint8_t ret_val = E_OK;
switch(Interrupt_Handler)
{
case NMI:     SET_BIT(SCB->ICSR,NMI_SET_PENDING_BIT_POS); break;
case PendSV:  SET_BIT(SCB->ICSR,PENDSV_SET_PENDING_BIT_POS); break;
case Systick: SET_BIT(SCB->ICSR,SYSTICK_SET_PENDING_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief clear Pending Bit for specific interrupt
 *@ param Interrupt
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t clear_Interrupt_Pending_Bit(Interrupt_t Interrupt_Handler)
{
uint8_t ret_val = E_OK;
switch(Interrupt_Handler)
{
case PendSV:  SET_BIT(SCB->ICSR,PENDSV_CLEAR_PENDING_BIT_POS); break;
case Systick: SET_BIT(SCB->ICSR,SYSTICK_CLEAR_PENDING_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}


/**
 *@ brief Enable All configurable interrupts
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
__attribute__((naked)) void Enable_All_Configurable_interrupts(void)
{
	asm volatile("MOV R0,#0");
	asm volatile("MSR PRIMASK,R0");
	asm volatile("BX LR");
}

/**
 *@ brief Disable All interrupts except Hard Fault, NMI, Reset
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
__attribute__((naked)) void Disable_All_Configurable_interrupts(void)
{
	asm volatile("MOV R0,#1");
	asm volatile("MSR PRIMASK,R0");
	asm volatile("BX LR");
}

/**
 *@ brief Eanble All interrupts
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
__attribute__((naked)) void Enable_All_interrupts(void)
{
	asm volatile("MOV R0,#0");
	asm volatile("MSR FAULTMASK,R0");
	asm volatile("BX LR");
}

/**
 *@ brief Disable All interrupts except NMI, Reset
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
__attribute__((naked)) void Disable_All_interrupts(void)
{
	asm volatile("MOV R0,#1");
	asm volatile("MSR FAULTMASK,R0");
	asm volatile("BX LR");
}

