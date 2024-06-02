#include "NVIC.h"

/**
 *@ brief Enable specific interrupt
 *@ param interrupt request number @ref NVIC_IRQ_t
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t NVIC_Enabel_IRQ(NVIC_IRQ_t IRQ)
{
uint8_t ret_val = E_OK;
if(IRQ <= 31)
{
NVIC->ISER[0] |= (1 << IRQ);
}
else if (IRQ > 31 && IRQ <60)
{
IRQ -= 32;
NVIC->ISER[1] |= (1 << IRQ);
}
else
{
ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief disable specific interrupt
 *@ param interrupt request number @ref NVIC_IRQ_t
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t NVIC_Disable_IRQ(NVIC_IRQ_t IRQ)
{
uint8_t ret_val = E_OK;
if(IRQ <= 31)
{
NVIC->ICER[0] |= (1 << IRQ);
}
else if (IRQ > 31 && IRQ <60)
{
IRQ -= 32;
NVIC->ICER[1] |= (1 << IRQ);
}
else
{
ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief set pending state for specific interrupt
 *@ param interrupt request number @ref NVIC_IRQ_t
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t NVIC_Set_Pending_State_IRQ(NVIC_IRQ_t IRQ)
{
uint8_t ret_val = E_OK;
if(IRQ <= 31)
{
NVIC->ISPR[0] |= (1 << IRQ);
}
else if (IRQ > 31 && IRQ <60)
{
IRQ -= 32;
NVIC->ISPR[1] |= (1 << IRQ);
}
else
{
ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief clear pending state for specific interrupt
 *@ param interrupt request number @ref NVIC_IRQ_t
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */

uint8_t NVIC_Clear_Pending_State_IRQ(NVIC_IRQ_t IRQ)
{
uint8_t ret_val = E_OK;
if(IRQ <= 31)
{
NVIC->ICPR[0] |= (1 << IRQ);
}
else if (IRQ > 31 && IRQ <60)
{
IRQ -= 32;
NVIC->ICPR[1] |= (1 << IRQ);
}
else
{
ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief Read state for specific interrupt
 *@ param interrupt request number @ref NVIC_IRQ_t
 *@ active state if 1 interrupt is active , if 0 interrupt is inactive
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t NVIC_Get_Active_State_IRQ(NVIC_IRQ_t IRQ,uint8_t *state)
{
uint8_t ret_val = E_OK;
*state = 0;
if(IRQ <= 31)
{
*state = ((NVIC->IABR[0] >> (IRQ)) & ((uint32_t)0x00000001));
}
else if (IRQ > 31 && IRQ <60)
{
IRQ -= 32;
*state = ((NVIC->IABR[1] >> (IRQ)) & ((uint32_t)0x00000001));
}
else
{
ret_val = E_NOK;
}
return ret_val;
}

/**
 *@ brief configure priority groups
 *@ param priority group @ref Priority_Grouping_t
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t NVIC_Set_Priority_group(Priority_Grouping_t PriorityGroup)
{
uint8_t ret_val = E_OK;
uint32_t reg_val = 0;
uint32_t priority_group_temp = ((PriorityGroup) & ((uint32_t) 0x07UL));
reg_val = SCB->AIRCR;
reg_val &= ~((uint32_t)(SCB_AIRCR_VECTKEY_MASK | SCB_PRIORITY_GROUP_MASK));
reg_val |= ((uint32_t)(SET_VECTKEY_VALUE | priority_group_temp << SCB_PRIORITY_GROUP_POS));
SCB->AIRCR = reg_val;
return ret_val;
}

/**
 *@ brief configure priority level for specific interrupt
 *@ param interrupt request number @ref NVIC_IRQ_t
 *@ param priority level
 *@ return function status
 *@ E_OK  function was completed successfully
 *@ E_NOK function was completed unsuccessfully
 * */
uint8_t NVIC_Config_Prioirty_IRQ(NVIC_IRQ_t IRQ,uint32_t Priority)
{
uint8_t ret_val = E_OK;
NVIC->IPR[(IRQ >> 2)] &= ~ (0XFFUL << (BIT_SHIFT(IRQ)));
NVIC->IPR[(IRQ >> 2)] |= (((Priority << PRIORITY_LEVEL_MSK) & 0XFF) << (BIT_SHIFT(IRQ)));
return ret_val;
}
















