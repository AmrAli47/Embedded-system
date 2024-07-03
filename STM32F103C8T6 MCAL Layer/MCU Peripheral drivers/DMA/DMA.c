/* 
 * File:   	DMA.c
 * Author: Amr Ali
 * @brief Direct Memory Access driver  
 */

#include "DMA.h"
void (*Error_Transfer_Handler_CH1)(void);
void (*Half_Transfer_Handler_CH1)(void);
void (*Complete_Transfer_Handler_CH1)(void);
void (*Error_Transfer_Handler_CH2)(void);
void (*Half_Transfer_Handler_CH2)(void);
void (*Complete_Transfer_Handler_CH2)(void);
void (*Error_Transfer_Handler_CH3)(void);
void (*Half_Transfer_Handler_CH3)(void);
void (*Complete_Transfer_Handler_CH3)(void);
void (*Error_Transfer_Handler_CH4)(void);
void (*Half_Transfer_Handler_CH4)(void);
void (*Complete_Transfer_Handler_CH4)(void);
void (*Error_Transfer_Handler_CH5)(void);
void (*Half_Transfer_Handler_CH5)(void);
void (*Complete_Transfer_Handler_CH5)(void);
void (*Error_Transfer_Handler_CH6)(void);
void (*Half_Transfer_Handler_CH6)(void);
void (*Complete_Transfer_Handler_CH6)(void);
void (*Error_Transfer_Handler_CH7)(void);
void (*Half_Transfer_Handler_CH7)(void);
void (*Complete_Transfer_Handler_CH7)(void);

static uint8_t Enable_DMA1_Clock(void);
static uint8_t Disable_channel(DMA_t* DMA);
static uint8_t set_channel_priority(DMA_t* DMA);
static uint8_t set_channel_direction(DMA_t* DMA);
static uint8_t set_Interrupt_configuration(DMA_t* DMA);
static uint8_t DeInit_Interrupt_configuration(DMA_t* DMA);
uint8_t set_number_of_data_to_transfer(DMA_t* DMA,uint16_t len);
static uint8_t set_Interrupt_Handler(DMA_t* DMA);
static uint8_t set_transfer_type(DMA_t* DMA);
static uint8_t Enable_Circular_Mode(DMA_t* DMA);
static uint8_t set_memory_size(DMA_t* DMA);
static uint8_t set_peripheral_size(DMA_t* DMA);
static uint8_t set_memory_increment_mode(DMA_t* DMA);
static uint8_t set_peripheral_increment_mode(DMA_t* DMA);

uint8_t DMA_Init(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
Enable_DMA1_Clock();
set_channel_priority(DMA);
set_channel_direction(DMA);
set_Interrupt_configuration(DMA);
set_number_of_data_to_transfer(DMA,DMA->number_of_data_to_trasfer);
set_Interrupt_Handler(DMA);
if(Memory_to_memory_mode_enabled == DMA->transfer_type)
{
set_transfer_type(DMA);
}
else
{
/* Nothing */
}
if(Circular_Mode == DMA->mode)
{
Enable_Circular_Mode(DMA);
}
else
{
/* Nothing */
}
if(Peripheral_increment_mode_enabled == DMA->Peripheral_increment_mode)
{
set_peripheral_increment_mode(DMA);
}
else
{
/* Nothing */
}
if(Memory_increment_mode_enabled == DMA->Memory_increment_mode)
{
set_memory_increment_mode(DMA);
}
else
{
/* Nothing */
}
set_memory_size(DMA);
set_peripheral_size(DMA);
return ret_val;
}


uint8_t DMA_DeInit(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
Disable_channel(DMA);
DeInit_Interrupt_configuration(DMA);
return ret_val;
}

uint8_t start_DMA(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: SET_BIT(DMA1->DMA_CCR1,CHANNEL_EN_BIT_POS); break;
case channel_2: SET_BIT(DMA1->DMA_CCR2,CHANNEL_EN_BIT_POS); break;
case channel_3: SET_BIT(DMA1->DMA_CCR3,CHANNEL_EN_BIT_POS); break;
case channel_4: SET_BIT(DMA1->DMA_CCR4,CHANNEL_EN_BIT_POS); break;
case channel_5: SET_BIT(DMA1->DMA_CCR5,CHANNEL_EN_BIT_POS); break;
case channel_6: SET_BIT(DMA1->DMA_CCR6,CHANNEL_EN_BIT_POS); break;
case channel_7: SET_BIT(DMA1->DMA_CCR7,CHANNEL_EN_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}


static uint8_t Disable_channel(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: CLEAR_BIT(DMA1->DMA_CCR1,CHANNEL_EN_BIT_POS); break;
case channel_2: CLEAR_BIT(DMA1->DMA_CCR2,CHANNEL_EN_BIT_POS); break;
case channel_3: CLEAR_BIT(DMA1->DMA_CCR3,CHANNEL_EN_BIT_POS); break;
case channel_4: CLEAR_BIT(DMA1->DMA_CCR4,CHANNEL_EN_BIT_POS); break;
case channel_5: CLEAR_BIT(DMA1->DMA_CCR5,CHANNEL_EN_BIT_POS); break;
case channel_6: CLEAR_BIT(DMA1->DMA_CCR6,CHANNEL_EN_BIT_POS); break;
case channel_7: CLEAR_BIT(DMA1->DMA_CCR7,CHANNEL_EN_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}




static uint8_t set_channel_priority(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1:
DMA1->DMA_CCR1 &= ~(CHANNEL_PRIORITY_MASK);
DMA1->DMA_CCR1 |= (DMA->priority << CHANNEL_PRIORITY_BIT_POS);
break;
case channel_2:
DMA1->DMA_CCR2 &= ~(CHANNEL_PRIORITY_MASK);
DMA1->DMA_CCR2 |= (DMA->priority << CHANNEL_PRIORITY_BIT_POS);
break;
case channel_3:
DMA1->DMA_CCR3 &= ~(CHANNEL_PRIORITY_MASK);
DMA1->DMA_CCR3 |= (DMA->priority << CHANNEL_PRIORITY_BIT_POS);
break;
case channel_4:
DMA1->DMA_CCR4 &= ~(CHANNEL_PRIORITY_MASK);
DMA1->DMA_CCR4 |= (DMA->priority << CHANNEL_PRIORITY_BIT_POS);
break;
case channel_5:
DMA1->DMA_CCR5 &= ~(CHANNEL_PRIORITY_MASK);
DMA1->DMA_CCR5 |= (DMA->priority << CHANNEL_PRIORITY_BIT_POS);
break;
case channel_6:
DMA1->DMA_CCR6 &= ~(CHANNEL_PRIORITY_MASK);
DMA1->DMA_CCR6 |= (DMA->priority << CHANNEL_PRIORITY_BIT_POS);
break;
case channel_7:
DMA1->DMA_CCR7 &= ~(CHANNEL_PRIORITY_MASK);
SET_BIT(DMA1->DMA_CCR7,CHANNEL_PRIORITY_BIT_POS);
DMA1->DMA_CCR7 |= ((DMA->priority) << CHANNEL_PRIORITY_BIT_POS);
break;
default : ret_val = E_NOK;
}
return ret_val;
}



static uint8_t set_channel_direction(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1:
if(Read_from_peripheral == DMA->direction)
{
CLEAR_BIT(DMA1->DMA_CCR1,DATA_DIRECTION_BIT_POS);
}
else if(Read_from_memory == DMA->direction)
{
SET_BIT(DMA1->DMA_CCR1,DATA_DIRECTION_BIT_POS);
}
else
{
ret_val = E_NOK;
}
break;
case channel_2:
if(Read_from_peripheral == DMA->direction)
{
CLEAR_BIT(DMA1->DMA_CCR2,DATA_DIRECTION_BIT_POS);
}
else if(Read_from_memory == DMA->direction)
{
SET_BIT(DMA1->DMA_CCR2,DATA_DIRECTION_BIT_POS);
}
else
{
ret_val = E_NOK;
}
break;
case channel_3:
if(Read_from_peripheral == DMA->direction)
{
CLEAR_BIT(DMA1->DMA_CCR3,DATA_DIRECTION_BIT_POS);
}
else if(Read_from_memory == DMA->direction)
{
SET_BIT(DMA1->DMA_CCR3,DATA_DIRECTION_BIT_POS);
}
else
{
ret_val = E_NOK;
}
break;
case channel_4:
if(Read_from_peripheral == DMA->direction)
{
CLEAR_BIT(DMA1->DMA_CCR4,DATA_DIRECTION_BIT_POS);
}
else if(Read_from_memory == DMA->direction)
{
SET_BIT(DMA1->DMA_CCR4,DATA_DIRECTION_BIT_POS);
}
else
{
ret_val = E_NOK;
}
break;
case channel_5:
if(Read_from_peripheral == DMA->direction)
{
CLEAR_BIT(DMA1->DMA_CCR5,DATA_DIRECTION_BIT_POS);
}
else if(Read_from_memory == DMA->direction)
{
SET_BIT(DMA1->DMA_CCR5,DATA_DIRECTION_BIT_POS);
}
else
{
ret_val = E_NOK;
}
break;
case channel_6:
if(Read_from_peripheral == DMA->direction)
{
CLEAR_BIT(DMA1->DMA_CCR6,DATA_DIRECTION_BIT_POS);
}
else if(Read_from_memory == DMA->direction)
{
SET_BIT(DMA1->DMA_CCR6,DATA_DIRECTION_BIT_POS);
}
else
{
ret_val = E_NOK;
}
break;
case channel_7:
if(Read_from_peripheral == DMA->direction)
{
CLEAR_BIT(DMA1->DMA_CCR7,DATA_DIRECTION_BIT_POS);
}
else if(Read_from_memory == DMA->direction)
{
SET_BIT(DMA1->DMA_CCR7,DATA_DIRECTION_BIT_POS);
}
else
{
ret_val = E_NOK;
}
break;
default : ret_val = E_NOK;
}
return ret_val;
}



static uint8_t Enable_DMA1_Clock(void)
{
uint8_t ret_val = E_OK;
SET_BIT(RCC->RCC_AHBENR,DMA_CLOCK_BIT_POS);
return ret_val;
}


static uint8_t set_Interrupt_configuration(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
SET_BIT(DMA1->DMA_CCR1,TRANSFER_ER_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR1,TRANSFER_ER_INT_BIT_POS);
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR1,TRANSFER_HLF_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR1,TRANSFER_HLF_TR_INT_BIT_POS);
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR1,TRANSFER_COM_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR1,TRANSFER_COM_TR_INT_BIT_POS);
}
break;
case channel_2:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
SET_BIT(DMA1->DMA_CCR2,TRANSFER_ER_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR2,TRANSFER_ER_INT_BIT_POS);
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR2,TRANSFER_HLF_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR2,TRANSFER_HLF_TR_INT_BIT_POS);
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR2,TRANSFER_COM_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR2,TRANSFER_COM_TR_INT_BIT_POS);
}
break;
case channel_3:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
SET_BIT(DMA1->DMA_CCR3,TRANSFER_ER_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR3,TRANSFER_ER_INT_BIT_POS);
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR3,TRANSFER_HLF_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR3,TRANSFER_HLF_TR_INT_BIT_POS);
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR3,TRANSFER_COM_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR3,TRANSFER_COM_TR_INT_BIT_POS);
}
break;
case channel_4:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
SET_BIT(DMA1->DMA_CCR4,TRANSFER_ER_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR4,TRANSFER_ER_INT_BIT_POS);
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR4,TRANSFER_HLF_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR4,TRANSFER_HLF_TR_INT_BIT_POS);
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR4,TRANSFER_COM_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR4,TRANSFER_COM_TR_INT_BIT_POS);
}
break;
case channel_5:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
SET_BIT(DMA1->DMA_CCR5,TRANSFER_ER_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR5,TRANSFER_ER_INT_BIT_POS);
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR5,TRANSFER_HLF_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR5,TRANSFER_HLF_TR_INT_BIT_POS);
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR5,TRANSFER_COM_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR5,TRANSFER_COM_TR_INT_BIT_POS);
}
break;
case channel_6:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
SET_BIT(DMA1->DMA_CCR6,TRANSFER_ER_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR6,TRANSFER_ER_INT_BIT_POS);
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR6,TRANSFER_HLF_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR6,TRANSFER_HLF_TR_INT_BIT_POS);
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR6,TRANSFER_COM_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR6,TRANSFER_COM_TR_INT_BIT_POS);
}
break;
case channel_7:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
SET_BIT(DMA1->DMA_CCR7,TRANSFER_ER_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR7,TRANSFER_ER_INT_BIT_POS);
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR7,TRANSFER_HLF_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR7,TRANSFER_HLF_TR_INT_BIT_POS);
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
SET_BIT(DMA1->DMA_CCR7,TRANSFER_COM_TR_INT_BIT_POS);
}
else
{
CLEAR_BIT(DMA1->DMA_CCR7,TRANSFER_COM_TR_INT_BIT_POS);
}
break;
default : ret_val = E_NOK;
}
return ret_val;
}


uint8_t set_number_of_data_to_transfer(DMA_t* DMA,uint16_t len)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: DMA1->DMA_CNDTR1 = DMA->number_of_data_to_trasfer; break;
case channel_2: DMA1->DMA_CNDTR2 = DMA->number_of_data_to_trasfer; break;
case channel_3: DMA1->DMA_CNDTR3 = DMA->number_of_data_to_trasfer; break;
case channel_4: DMA1->DMA_CNDTR4 = DMA->number_of_data_to_trasfer; break;
case channel_5: DMA1->DMA_CNDTR5 = DMA->number_of_data_to_trasfer; break;
case channel_6: DMA1->DMA_CNDTR6 = DMA->number_of_data_to_trasfer; break;
case channel_7: DMA1->DMA_CNDTR7 = DMA->number_of_data_to_trasfer; break;
default : ret_val = E_NOK;
}
return ret_val;
}


uint8_t Set_destination_aaddress(DMA_t* DMA,uint32_t address)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: DMA1->DMA_CPAR1 = address; break;
case channel_2: DMA1->DMA_CPAR2 = address; break;
case channel_3: DMA1->DMA_CPAR3 = address; break;
case channel_4: DMA1->DMA_CPAR4 = address; break;
case channel_5: DMA1->DMA_CPAR5 = address; break;
case channel_6: DMA1->DMA_CPAR6 = address; break;
case channel_7: DMA1->DMA_CPAR7 = address; break;
default : ret_val = E_NOK;
}
return ret_val;
}


uint8_t Set_source_aaddress(DMA_t* DMA,uint32_t address)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: DMA1->DMA_CMAR1 = address; break;
case channel_2: DMA1->DMA_CMAR2 = address; break;
case channel_3: DMA1->DMA_CMAR3 = address; break;
case channel_4: DMA1->DMA_CMAR4 = address; break;
case channel_5: DMA1->DMA_CMAR5 = address; break;
case channel_6: DMA1->DMA_CMAR6 = address; break;
case channel_7: DMA1->DMA_CMAR7 = address; break;
default : ret_val = E_NOK;
}
return ret_val;
}



static uint8_t set_Interrupt_Handler(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
Error_Transfer_Handler_CH1 = DMA->Error_Transfer_callback;
}
else
{
Error_Transfer_Handler_CH1 = NULL;
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
Half_Transfer_Handler_CH1 = DMA->Half_Transfer_callback;
}
else
{
Half_Transfer_Handler_CH1 = NULL;
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
Complete_Transfer_Handler_CH1 = DMA->Complete_Transfer_callback;
}
else
{
Complete_Transfer_Handler_CH1 = NULL;
}
break;
case channel_2:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
Error_Transfer_Handler_CH2 = DMA->Error_Transfer_callback;
}
else
{
Error_Transfer_Handler_CH2 = NULL;
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
Half_Transfer_Handler_CH2 = DMA->Half_Transfer_callback;
}
else
{
Half_Transfer_Handler_CH2 = NULL;
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
Complete_Transfer_Handler_CH2 = DMA->Complete_Transfer_callback;
}
else
{
Complete_Transfer_Handler_CH2 = NULL;
}
break;
case channel_3:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
Error_Transfer_Handler_CH3 = DMA->Error_Transfer_callback;
}
else
{
Error_Transfer_Handler_CH3 = NULL;
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
Half_Transfer_Handler_CH3 = DMA->Half_Transfer_callback;
}
else
{
Half_Transfer_Handler_CH3 = NULL;
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
Complete_Transfer_Handler_CH3 = DMA->Complete_Transfer_callback;
}
else
{
Complete_Transfer_Handler_CH3 = NULL;
}
break;
case channel_4:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
Error_Transfer_Handler_CH4 = DMA->Error_Transfer_callback;
}
else
{
Error_Transfer_Handler_CH4 = NULL;
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
Half_Transfer_Handler_CH4 = DMA->Half_Transfer_callback;
}
else
{
Half_Transfer_Handler_CH4 = NULL;
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
Complete_Transfer_Handler_CH4 = DMA->Complete_Transfer_callback;
}
else
{
Complete_Transfer_Handler_CH4 = NULL;
}
break;
case channel_5:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
Error_Transfer_Handler_CH5 = DMA->Error_Transfer_callback;
}
else
{
Error_Transfer_Handler_CH5 = NULL;
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
Half_Transfer_Handler_CH5 = DMA->Half_Transfer_callback;
}
else
{
Half_Transfer_Handler_CH5 = NULL;
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
Complete_Transfer_Handler_CH5 = DMA->Complete_Transfer_callback;
}
else
{
Complete_Transfer_Handler_CH5 = NULL;
}
break;
case channel_6:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
Error_Transfer_Handler_CH6 = DMA->Error_Transfer_callback;
}
else
{
Error_Transfer_Handler_CH6 = NULL;
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
Half_Transfer_Handler_CH6 = DMA->Half_Transfer_callback;
}
else
{
Half_Transfer_Handler_CH6 = NULL;
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
Complete_Transfer_Handler_CH6 = DMA->Complete_Transfer_callback;
}
else
{
Complete_Transfer_Handler_CH6 = NULL;
}
break;
case channel_7:
if(Transfer_error_interrupt_Enable == DMA->Error_interrupt)
{
Error_Transfer_Handler_CH7 = DMA->Error_Transfer_callback;
}
else
{
Error_Transfer_Handler_CH7 = NULL;
}
if(Half_Transfer_interrupt_Enable == DMA->Half_Transfer_interrupt)
{
Half_Transfer_Handler_CH7 = DMA->Half_Transfer_callback;
}
else
{
Half_Transfer_Handler_CH7 = NULL;
}
if(complete_Transfer_interrupt_Enable == DMA->Complete_Transfer_interrupt)
{
Complete_Transfer_Handler_CH7 = DMA->Complete_Transfer_callback;
}
else
{
Complete_Transfer_Handler_CH7 = NULL;
}
break;
default : ret_val = E_NOK;
}
return ret_val;
}

static uint8_t DeInit_Interrupt_configuration(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: SET_BIT(DMA1->DMA_IFCR,GLOBAL_INT_CLEAR_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR1,TRANSFER_COM_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR1,TRANSFER_HLF_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR1,TRANSFER_ER_INT_BIT_POS);
break;
case channel_2: SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 4));
CLEAR_BIT(DMA1->DMA_CCR2,TRANSFER_COM_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR2,TRANSFER_HLF_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR2,TRANSFER_ER_INT_BIT_POS);
break;
case channel_3: SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 8));
CLEAR_BIT(DMA1->DMA_CCR3,TRANSFER_COM_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR3,TRANSFER_HLF_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR3,TRANSFER_ER_INT_BIT_POS);
break;
case channel_4: SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 12));
CLEAR_BIT(DMA1->DMA_CCR4,TRANSFER_COM_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR4,TRANSFER_HLF_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR4,TRANSFER_ER_INT_BIT_POS);
break;
case channel_5: SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 16));
CLEAR_BIT(DMA1->DMA_CCR5,TRANSFER_COM_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR5,TRANSFER_HLF_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR5,TRANSFER_ER_INT_BIT_POS);
break;
case channel_6: SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 20));
CLEAR_BIT(DMA1->DMA_CCR6,TRANSFER_COM_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR6,TRANSFER_HLF_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR6,TRANSFER_ER_INT_BIT_POS);
break;
case channel_7: SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 24));
CLEAR_BIT(DMA1->DMA_CCR7,TRANSFER_COM_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR7,TRANSFER_HLF_TR_INT_BIT_POS);
CLEAR_BIT(DMA1->DMA_CCR7,TRANSFER_ER_INT_BIT_POS);
break;
default : ret_val = E_NOK;
}
return ret_val;
}

void DMA1_Channel1_IRQHandler(void)
{
if((NULL != Error_Transfer_Handler_CH1) && (1 == READ_BIT(DMA1->DMA_ISR,ERROR_TRANSFER_FLAG_BIT_POS)))
{
SET_BIT(DMA1->DMA_IFCR,ERROR_TRANSFER_FLAG_BIT_POS);
if(Error_Transfer_Handler_CH1)
{
Error_Transfer_Handler_CH1();
}
else
{
/* Nothing */
}
}
else if((NULL != Half_Transfer_Handler_CH1) && (1 == READ_BIT(DMA1->DMA_ISR,HALF_TRANSFER_FLAG_BIT_POS)))
{
SET_BIT(DMA1->DMA_IFCR,HALF_TRANSFER_FLAG_BIT_POS);
if(Half_Transfer_Handler_CH1)
{
Half_Transfer_Handler_CH1();
}
else
{
/* Nothing */
}
}
else if((NULL != Complete_Transfer_Handler_CH1) && (1 == READ_BIT(DMA1->DMA_ISR,COMP_TRANSFER_FLAG_BIT_POS)))
{
SET_BIT(DMA1->DMA_IFCR,COMP_TRANSFER_FLAG_BIT_POS);
if(Complete_Transfer_Handler_CH1)
{
Complete_Transfer_Handler_CH1();
}
else
{
/* Nothing */
}
}
else
{
/*Nothing*/
}
SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS));
}


void DMA1_Channel2_IRQHandler(void)
{
if((NULL != Error_Transfer_Handler_CH2) && (1 == READ_BIT(DMA1->DMA_ISR,(ERROR_TRANSFER_FLAG_BIT_POS + 4))))
{
SET_BIT(DMA1->DMA_IFCR,(ERROR_TRANSFER_FLAG_BIT_POS + 4));
if(Error_Transfer_Handler_CH2)
{
Error_Transfer_Handler_CH2();
}
else
{
/* Nothing */
}
}
else if((NULL != Half_Transfer_Handler_CH2) && (1 == READ_BIT(DMA1->DMA_ISR,(HALF_TRANSFER_FLAG_BIT_POS + 4))))
{
SET_BIT(DMA1->DMA_IFCR,(HALF_TRANSFER_FLAG_BIT_POS + 4));
if(Half_Transfer_Handler_CH2)
{
Half_Transfer_Handler_CH2();
}
else
{
/* Nothing */
}
}
else if((NULL != Complete_Transfer_Handler_CH2) && (1 == READ_BIT(DMA1->DMA_ISR,(COMP_TRANSFER_FLAG_BIT_POS + 4))))
{
SET_BIT(DMA1->DMA_IFCR,(COMP_TRANSFER_FLAG_BIT_POS + 4));
if(Complete_Transfer_Handler_CH2)
{
Complete_Transfer_Handler_CH2();
}
else
{
/* Nothing */
}
}
else
{
/*Nothing*/
}
SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 4));
}

void DMA1_Channel3_IRQHandler(void)
{
if((NULL != Error_Transfer_Handler_CH3) && (1 == READ_BIT(DMA1->DMA_ISR,(ERROR_TRANSFER_FLAG_BIT_POS + 8))))
{
SET_BIT(DMA1->DMA_IFCR,(ERROR_TRANSFER_FLAG_BIT_POS + 8));
if(Error_Transfer_Handler_CH3)
{
Error_Transfer_Handler_CH3();
}
else
{
/* Nothing */
}
}
else if((NULL != Half_Transfer_Handler_CH3) && (1 == READ_BIT(DMA1->DMA_ISR,(HALF_TRANSFER_FLAG_BIT_POS + 8))))
{
SET_BIT(DMA1->DMA_IFCR,(HALF_TRANSFER_FLAG_BIT_POS + 8));
if(Half_Transfer_Handler_CH3)
{
Half_Transfer_Handler_CH3();
}
else
{
/* Nothing */
}
}
else if((NULL != Complete_Transfer_Handler_CH3) && (1 == READ_BIT(DMA1->DMA_ISR,(COMP_TRANSFER_FLAG_BIT_POS + 8))))
{
SET_BIT(DMA1->DMA_IFCR,(COMP_TRANSFER_FLAG_BIT_POS + 8));
if(Complete_Transfer_Handler_CH3)
{
Complete_Transfer_Handler_CH3();
}
else
{
/* Nothing */
}
}
else
{
/*Nothing*/
}
SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 8));
}

void DMA1_Channel4_IRQHandler(void)
{
if((NULL != Error_Transfer_Handler_CH4) && (1 == READ_BIT(DMA1->DMA_ISR,(ERROR_TRANSFER_FLAG_BIT_POS + 12))))
{
SET_BIT(DMA1->DMA_IFCR,(ERROR_TRANSFER_FLAG_BIT_POS + 12));
if(Error_Transfer_Handler_CH4)
{
Error_Transfer_Handler_CH4();
}
else
{
/* Nothing */
}
}
else if((NULL != Half_Transfer_Handler_CH4) && (1 == READ_BIT(DMA1->DMA_ISR,(HALF_TRANSFER_FLAG_BIT_POS + 12))))
{
SET_BIT(DMA1->DMA_IFCR,(HALF_TRANSFER_FLAG_BIT_POS + 12));
if(Half_Transfer_Handler_CH4)
{
Half_Transfer_Handler_CH4();
}
else
{
/* Nothing */
}
}
else if((NULL != Complete_Transfer_Handler_CH4) && (1 == READ_BIT(DMA1->DMA_ISR,(COMP_TRANSFER_FLAG_BIT_POS + 12))))
{
SET_BIT(DMA1->DMA_IFCR,(COMP_TRANSFER_FLAG_BIT_POS + 12));
if(Complete_Transfer_Handler_CH4)
{
Complete_Transfer_Handler_CH4();
}
else
{
/* Nothing */
}
}
else
{
/*Nothing*/
}
SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 12));
}

void DMA1_Channel5_IRQHandler(void)
{
if((NULL != Error_Transfer_Handler_CH5) && (1 == READ_BIT(DMA1->DMA_ISR,(ERROR_TRANSFER_FLAG_BIT_POS + 16))))
{
SET_BIT(DMA1->DMA_IFCR,(ERROR_TRANSFER_FLAG_BIT_POS + 16));
if(Error_Transfer_Handler_CH5)
{
Error_Transfer_Handler_CH5();
}
else
{
/* Nothing */
}
}
else if((NULL != Half_Transfer_Handler_CH5) && (1 == READ_BIT(DMA1->DMA_ISR,(HALF_TRANSFER_FLAG_BIT_POS + 16))))
{
SET_BIT(DMA1->DMA_IFCR,(HALF_TRANSFER_FLAG_BIT_POS + 16));
if(Half_Transfer_Handler_CH5)
{
Half_Transfer_Handler_CH5();
}
else
{
/* Nothing */
}
}
else if((NULL != Complete_Transfer_Handler_CH5) && (1 == READ_BIT(DMA1->DMA_ISR,(COMP_TRANSFER_FLAG_BIT_POS + 16))))
{
SET_BIT(DMA1->DMA_IFCR,(COMP_TRANSFER_FLAG_BIT_POS + 16));
if(Complete_Transfer_Handler_CH5)
{
Complete_Transfer_Handler_CH5();
}
else
{
/* Nothing */
}
}
else
{
/*Nothing*/
}
SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 16));
}

void DMA1_Channel6_IRQHandler(void)
{
if((NULL != Error_Transfer_Handler_CH6) && (1 == READ_BIT(DMA1->DMA_ISR,(ERROR_TRANSFER_FLAG_BIT_POS + 20))))
{
SET_BIT(DMA1->DMA_IFCR,(ERROR_TRANSFER_FLAG_BIT_POS + 20));
if(Error_Transfer_Handler_CH6)
{
Error_Transfer_Handler_CH6();
}
else
{
/* Nothing */
}
}
else if((NULL != Half_Transfer_Handler_CH6) && (1 == READ_BIT(DMA1->DMA_ISR,(HALF_TRANSFER_FLAG_BIT_POS + 20))))
{
SET_BIT(DMA1->DMA_IFCR,(HALF_TRANSFER_FLAG_BIT_POS + 20));
if(Half_Transfer_Handler_CH6)
{
Half_Transfer_Handler_CH6();
}
else
{
/* Nothing */
}
}
else if((NULL != Complete_Transfer_Handler_CH6) && (1 == READ_BIT(DMA1->DMA_ISR,(COMP_TRANSFER_FLAG_BIT_POS + 20))))
{
SET_BIT(DMA1->DMA_IFCR,(COMP_TRANSFER_FLAG_BIT_POS + 20));
if(Complete_Transfer_Handler_CH6)
{
Complete_Transfer_Handler_CH6();
}
else
{
/* Nothing */
}
}
else
{
/*Nothing*/
}
SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 20));
}


void DMA1_Channel7_IRQHandler(void)
{
if((NULL != Error_Transfer_Handler_CH7) && (1 == READ_BIT(DMA1->DMA_ISR,(ERROR_TRANSFER_FLAG_BIT_POS + 24))))
{
SET_BIT(DMA1->DMA_IFCR,(ERROR_TRANSFER_FLAG_BIT_POS + 24));
if(Error_Transfer_Handler_CH7)
{
Error_Transfer_Handler_CH7();
}
else
{
/* Nothing */
}
}
else if((NULL != Half_Transfer_Handler_CH7) && (1 == READ_BIT(DMA1->DMA_ISR,(HALF_TRANSFER_FLAG_BIT_POS + 24))))
{
SET_BIT(DMA1->DMA_IFCR,(HALF_TRANSFER_FLAG_BIT_POS + 24));
if(Half_Transfer_Handler_CH7)
{
Half_Transfer_Handler_CH7();
}
else
{
/* Nothing */
}
}
else if((NULL != Complete_Transfer_Handler_CH7) && (1 == READ_BIT(DMA1->DMA_ISR,(COMP_TRANSFER_FLAG_BIT_POS + 24))))
{
SET_BIT(DMA1->DMA_IFCR,(COMP_TRANSFER_FLAG_BIT_POS + 24));
if(Complete_Transfer_Handler_CH7)
{
Complete_Transfer_Handler_CH7();
}
else
{
/* Nothing */
}
}
else
{
/*Nothing*/
}
SET_BIT(DMA1->DMA_IFCR,(GLOBAL_INT_CLEAR_BIT_POS + 24));
}


static uint8_t set_transfer_type(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: SET_BIT(DMA1->DMA_CCR1,MEM_TO_MEM_MODE_BIT_POS); break;
case channel_2: SET_BIT(DMA1->DMA_CCR2,MEM_TO_MEM_MODE_BIT_POS); break;
case channel_3: SET_BIT(DMA1->DMA_CCR3,MEM_TO_MEM_MODE_BIT_POS); break;
case channel_4: SET_BIT(DMA1->DMA_CCR4,MEM_TO_MEM_MODE_BIT_POS); break;
case channel_5: SET_BIT(DMA1->DMA_CCR5,MEM_TO_MEM_MODE_BIT_POS); break;
case channel_6: SET_BIT(DMA1->DMA_CCR6,MEM_TO_MEM_MODE_BIT_POS); break;
case channel_7: SET_BIT(DMA1->DMA_CCR7,MEM_TO_MEM_MODE_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}


static uint8_t Enable_Circular_Mode(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: SET_BIT(DMA1->DMA_CCR1,CIRCULAR_MODE_BIT_POS); break;
case channel_2: SET_BIT(DMA1->DMA_CCR2,CIRCULAR_MODE_BIT_POS); break;
case channel_3: SET_BIT(DMA1->DMA_CCR3,CIRCULAR_MODE_BIT_POS); break;
case channel_4: SET_BIT(DMA1->DMA_CCR4,CIRCULAR_MODE_BIT_POS); break;
case channel_5: SET_BIT(DMA1->DMA_CCR5,CIRCULAR_MODE_BIT_POS); break;
case channel_6: SET_BIT(DMA1->DMA_CCR6,CIRCULAR_MODE_BIT_POS); break;
case channel_7: SET_BIT(DMA1->DMA_CCR7,CIRCULAR_MODE_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}



static uint8_t set_memory_size(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: DMA1->DMA_CCR1 &= ~(MEM_SIZE_BITS_MASK); DMA1->DMA_CCR1 |= (DMA->Memory_Size << MEM_SIZE_BITS_POS); break;
case channel_2: DMA1->DMA_CCR2 &= ~(MEM_SIZE_BITS_MASK); DMA1->DMA_CCR2 |= (DMA->Memory_Size << MEM_SIZE_BITS_POS); break;
case channel_3: DMA1->DMA_CCR3 &= ~(MEM_SIZE_BITS_MASK); DMA1->DMA_CCR3 |= (DMA->Memory_Size << MEM_SIZE_BITS_POS); break;
case channel_4: DMA1->DMA_CCR4 &= ~(MEM_SIZE_BITS_MASK); DMA1->DMA_CCR4 |= (DMA->Memory_Size << MEM_SIZE_BITS_POS); break;
case channel_5: DMA1->DMA_CCR5 &= ~(MEM_SIZE_BITS_MASK); DMA1->DMA_CCR5 |= (DMA->Memory_Size << MEM_SIZE_BITS_POS); break;
case channel_6: DMA1->DMA_CCR6 &= ~(MEM_SIZE_BITS_MASK); DMA1->DMA_CCR6 |= (DMA->Memory_Size << MEM_SIZE_BITS_POS); break;
case channel_7: DMA1->DMA_CCR7 &= ~(MEM_SIZE_BITS_MASK); DMA1->DMA_CCR7 |= (DMA->Memory_Size << MEM_SIZE_BITS_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}



static uint8_t set_peripheral_size(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: DMA1->DMA_CCR1 &= ~(PERIPHERAL_SIZEBITS_MASK); DMA1->DMA_CCR1 |= (DMA->Peripheral_Size << PERIPHERAL_SIZE_BITS_POS); break;
case channel_2: DMA1->DMA_CCR2 &= ~(PERIPHERAL_SIZEBITS_MASK); DMA1->DMA_CCR2 |= (DMA->Peripheral_Size << PERIPHERAL_SIZE_BITS_POS); break;
case channel_3: DMA1->DMA_CCR3 &= ~(PERIPHERAL_SIZEBITS_MASK); DMA1->DMA_CCR3 |= (DMA->Peripheral_Size << PERIPHERAL_SIZE_BITS_POS); break;
case channel_4: DMA1->DMA_CCR4 &= ~(PERIPHERAL_SIZEBITS_MASK); DMA1->DMA_CCR4 |= (DMA->Peripheral_Size << PERIPHERAL_SIZE_BITS_POS); break;
case channel_5: DMA1->DMA_CCR5 &= ~(PERIPHERAL_SIZEBITS_MASK); DMA1->DMA_CCR5 |= (DMA->Peripheral_Size << PERIPHERAL_SIZE_BITS_POS); break;
case channel_6: DMA1->DMA_CCR6 &= ~(PERIPHERAL_SIZEBITS_MASK); DMA1->DMA_CCR6 |= (DMA->Peripheral_Size << PERIPHERAL_SIZE_BITS_POS); break;
case channel_7: DMA1->DMA_CCR7 &= ~(PERIPHERAL_SIZEBITS_MASK); DMA1->DMA_CCR7 |= (DMA->Peripheral_Size << PERIPHERAL_SIZE_BITS_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}


static uint8_t set_memory_increment_mode(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: SET_BIT(DMA1->DMA_CCR1,MEM_INC_MOD_BIT_POS);  break;
case channel_2: SET_BIT(DMA1->DMA_CCR2,MEM_INC_MOD_BIT_POS);  break;
case channel_3: SET_BIT(DMA1->DMA_CCR3,MEM_INC_MOD_BIT_POS);  break;
case channel_4: SET_BIT(DMA1->DMA_CCR4,MEM_INC_MOD_BIT_POS);  break;
case channel_5: SET_BIT(DMA1->DMA_CCR5,MEM_INC_MOD_BIT_POS);  break;
case channel_6: SET_BIT(DMA1->DMA_CCR6,MEM_INC_MOD_BIT_POS);  break;
case channel_7: SET_BIT(DMA1->DMA_CCR7,MEM_INC_MOD_BIT_POS);  break;
default : ret_val = E_NOK;
}
return ret_val;
}
static uint8_t set_peripheral_increment_mode(DMA_t* DMA)
{
uint8_t ret_val = E_OK;
switch(DMA->channel)
{
case channel_1: SET_BIT(DMA1->DMA_CCR1,PERIPH_INC_MOD_BIT_POS);  break;
case channel_2: SET_BIT(DMA1->DMA_CCR2,PERIPH_INC_MOD_BIT_POS);  break;
case channel_3: SET_BIT(DMA1->DMA_CCR3,PERIPH_INC_MOD_BIT_POS);  break;
case channel_4: SET_BIT(DMA1->DMA_CCR4,PERIPH_INC_MOD_BIT_POS);  break;
case channel_5: SET_BIT(DMA1->DMA_CCR5,PERIPH_INC_MOD_BIT_POS);  break;
case channel_6: SET_BIT(DMA1->DMA_CCR6,PERIPH_INC_MOD_BIT_POS);  break;
case channel_7: SET_BIT(DMA1->DMA_CCR7,PERIPH_INC_MOD_BIT_POS);  break;
default : ret_val = E_NOK;
}
return ret_val;
}






