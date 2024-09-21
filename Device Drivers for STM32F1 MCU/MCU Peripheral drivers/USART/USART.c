/* 
 * File:   	USART.c
 * Author: Amr Ali
 * @brief Universal Synchronous Asynchronous Receiver Transmitter driver  
 */

#include "USART.h"
char* Transmission_ptr_data = NULL;
char* Reception_ptr_data = NULL;
uint8_t Transmission_size = 0;
uint8_t Reception_size = 0;
USART_Registers_t*  ptr_Instance = NULL;
uint8_t counter = 0;
state_t Transmission_state = Ready;
state_t Reception_state    = Ready;
USART_t* l_usart = NULL;


extern RCC_OSC_Init_t oscillator;
void (* USART1_Error_Interrupt_Handler)(void);
void (* USART2_Error_Interrupt_Handler)(void);
void (* USART3_Error_Interrupt_Handler)(void);
void (* USART1_Transmission_Complete_Interrupt_Handler)(void);
void (* USART2_Transmission_Complete_Interrupt_Handler)(void);
void (* USART3_Transmission_Complete_Interrupt_Handler)(void);
void (* USART1_data_register_is_empty_Interrupt_Handler)(void);
void (* USART2_data_register_is_empty_Interrupt_Handler)(void);
void (* USART3_data_register_is_empty_Interrupt_Handler)(void);
void (* USART1_CTS_Interrupt_Handler)(void);
void (* USART2_CTS_Interrupt_Handler)(void);
void (* USART3_CTS_Interrupt_Handler)(void);
void (* USART1_idle_line_Interrupt_Handler)(void);
void (* USART2_idle_line_Interrupt_Handler)(void);
void (* USART3_idle_line_Interrupt_Handler)(void);
void (* USART1_receive_data_Interrupt_Handler)(void);
void (* USART2_receive_data_Interrupt_Handler)(void);
void (* USART3_receive_data_Interrupt_Handler)(void);
void (* USART1_Transmit_data_Interrupt_Handler)(void);
void (* USART2_Transmit_data_Interrupt_Handler)(void);
void (* USART3_Transmit_data_Interrupt_Handler)(void);


static uint8_t Enable_USART_clock(USART_Peripherals_t USART);
static uint8_t Disable_USART_clock(USART_Peripherals_t USART);
static uint8_t Enable_USART(USART_t* USART);
static uint8_t Disable_USART(USART_t* USART);
static uint8_t set_word_length(USART_t* USART);
static uint8_t set_stop_bits_length(USART_t* USART);
static uint8_t configure_Transmitter_mode(USART_t* USART);
static uint8_t configure_Receiver_mode(USART_t* USART);
static uint8_t configure_Parity(USART_t* USART);
static uint8_t configure_clock(USART_t* USART);
static uint8_t configure_Baud_Rate(USART_t* USART);
static uint8_t configure_Interrupt(USART_t* USART);
static uint8_t set_half_duplex_mode(USART_t* USART);
static uint8_t configure_dma(USART_t* USART);
static uint8_t configure_hardware_flow_control(USART_t* USART);
static uint8_t Enable_transmission_interrupt(USART_t* USART);
static uint8_t Enable_Reception_interrupt(USART_t* USART);
static uint8_t Disable_transmission_interrupt(USART_Registers_t* USART_Inst);
static uint8_t Disable_Reception_interrupt(USART_Registers_t* USART_Inst);
static uint8_t Transmit_interrupt(USART_Registers_t* USART_Inst);
static uint8_t Receive_interrupt(USART_Registers_t* USART_Inst);

/**
 * @ brief Enable USART Module clock
 * @ param USART Peripherals @ref USART_Peripherals_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Enable_USART_clock(USART_Peripherals_t USART)
{
uint8_t ret_val = E_OK;
switch(USART)
{
case USART1: SET_BIT(RCC->RCC_APB2ENR,USART1_CLOCK_EN_BIT_POS); break;
case USART2: SET_BIT(RCC->RCC_APB1ENR,USART2_CLOCK_EN_BIT_POS); break;
case USART3: SET_BIT(RCC->RCC_APB1ENR,USART3_CLOCK_EN_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 * @ brief Disable USART Module clock
 * @ param USART Peripherals @ref USART_Peripherals_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Disable_USART_clock(USART_Peripherals_t USART)
{
uint8_t ret_val = E_OK;
switch(USART)
{
case USART1: CLEAR_BIT(RCC->RCC_APB2ENR,USART1_CLOCK_EN_BIT_POS); break;
case USART2: CLEAR_BIT(RCC->RCC_APB1ENR,USART2_CLOCK_EN_BIT_POS); break;
case USART3: CLEAR_BIT(RCC->RCC_APB1ENR,USART3_CLOCK_EN_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 * @ brief Initialize USART Module
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t USART_Init(USART_t* USART)
{
uint8_t ret_val = E_OK;
l_usart = USART;
Enable_USART(USART);
set_word_length(USART);
set_stop_bits_length(USART);
configure_Parity(USART);
if(Synchronous == USART->USART_mode)
{
configure_clock(USART);
}
else if(Asynchronous == USART->USART_mode)
{
configure_Baud_Rate(USART);
}
else
{
/* Nothing */
}
if(Enable_half_duplex_mode == USART->Half_duplex_mode)
{
set_half_duplex_mode(USART);
}
else
{
/* Nothing */
}
if((Enable_DMA_Receiver == USART->Receiver_DMA) || (Enable_DMA_Transmitter == USART->Transmitter_DMA))
{
configure_dma(USART);
}
else
{
/* Nothing */
}
if((Enable_RTS == USART->RTS_Hardware) || (Enable_CTS == USART->CTS_Hardware))
{
configure_hardware_flow_control(USART);
}
else
{
/* Nothing */
}
configure_Transmitter_mode(USART);
configure_Receiver_mode(USART);
configure_Interrupt(USART);
return ret_val;
}


/**
 * @ brief De-initialize USART Module
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t USART_DeInit(USART_t* USART)
{
uint8_t ret_val = E_OK;
Disable_USART(USART);
return ret_val;
}

/**
 * @ brief Set data field length
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t set_word_length(USART_t* USART)
{
uint8_t ret_val = E_OK;
switch(USART->word_length)
{
case data_length_len_8: CLEAR_BIT(USART->Instance->USART_CR1,WORD_LENGTH_BIT_BIT_POS); break;
case data_length_len_9: SET_BIT(USART->Instance->USART_CR1,WORD_LENGTH_BIT_BIT_POS); break;
default : ret_val = E_NOK;
}
return ret_val;
}


/**
 * @ brief Enable USART Module
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Enable_USART(USART_t* USART)
{
uint8_t ret_val = E_OK;
Enable_USART_clock(USART->USART_Per);
SET_BIT(USART->Instance->USART_CR1,USART_EN_BIT_POS);
return ret_val;
}


/**
 * @ brief Disable USART Module
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Disable_USART(USART_t* USART)
{
uint8_t ret_val = E_OK;
Disable_USART_clock(USART->USART_Per);
CLEAR_BIT(USART->Instance->USART_CR1,USART_EN_BIT_POS);
return ret_val;
}

/**
 * @ brief set stop bits length
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t set_stop_bits_length(USART_t* USART)
{
uint8_t ret_val = E_OK;
(USART->Instance->USART_CR2) &= ~(USART_STOP_BITS_MSK);
(USART->Instance->USART_CR2) |= (USART->stop_bits_len << USART_STOP_BITS_POS);
return ret_val;
}


/**
 * @ brief configure Transmitter mode
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t configure_Transmitter_mode(USART_t* USART)
{
uint8_t ret_val = E_OK;
if(Enable_Transmitter == USART->Tansmitter_mode)
{
SET_BIT(USART->Instance->USART_CR1,TRANSMITTER_EN_BIT_POS);
}
else if(Disable_Transmitter == USART->Tansmitter_mode)
{
CLEAR_BIT(USART->Instance->USART_CR1,TRANSMITTER_EN_BIT_POS);
}
else
{
/* Nothing */
}
return ret_val;
}

/**
 * @ brief configure Receiver mode
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t configure_Receiver_mode(USART_t* USART)
{
uint8_t ret_val = E_OK;
if(Enable_Receiver == USART->Receiver_mode)
{
SET_BIT(USART->Instance->USART_CR1,RECEIVER_EN_BIT_POS);
}
else if(Disable_Receiver == USART->Receiver_mode)
{
CLEAR_BIT(USART->Instance->USART_CR1,RECEIVER_EN_BIT_POS);
}
else
{
/* Nothing */
}
return ret_val;
}


/**
 * @ brief configure Parity
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t configure_Parity(USART_t* USART)
{
uint8_t ret_val = E_OK;
if(Enable_Parity_control == USART->Parity_control)
{
SET_BIT(USART->Instance->USART_CR1,PARITY_CONTROL_BIT_POS);
if(Even_parity == USART->Parity)
{
CLEAR_BIT(USART->Instance->USART_CR1,PARITY_SELECTION_BIT_POS);
}
else if(Odd_parity == USART->Parity)
{
SET_BIT(USART->Instance->USART_CR1,PARITY_SELECTION_BIT_POS);
}
else
{
/* Nothing */
}
}
else if(disable_Parity_control == USART->Parity_control)
{
CLEAR_BIT(USART->Instance->USART_CR1,PARITY_CONTROL_BIT_POS);
}
else
{
/* Nothing */
}
return ret_val;
}

/**
 * @ brief configure USART clock
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t configure_clock(USART_t* USART)
{
uint8_t ret_val = E_OK;
SET_BIT(USART->Instance->USART_CR2,CLOCK_EN_BIT_POS);
if(idle_state_is_high == USART->clock_polarity)
{
SET_BIT(USART_1->USART_CR2,CLOCK_POLARITY_BIT_POS);
}
else if(idle_state_is_low == USART->clock_polarity)
{
CLEAR_BIT(USART->Instance->USART_CR2,CLOCK_POLARITY_BIT_POS);
}
else
{
/* Nothing */
}
if(data_capture_edge_in_first_clock_transition == USART->clock_phase)
{
CLEAR_BIT(USART->Instance->USART_CR2,CLOCK_PHASE_BIT_POS);
}
else if(data_capture_edge_in_second_clock_transition == USART->clock_phase)
{
SET_BIT(USART->Instance->USART_CR2,CLOCK_PHASE_BIT_POS);
}
else
{
/* Nothing */
}
if(No_clock_pulse_in_last_bit == USART->Last_bit_clock_pulse)
{
CLEAR_BIT(USART->Instance->USART_CR2,LAST_BIT_CLOCK_PULSE_BIT_POS);
}
else if(Send_clock_pulse_in_last_bit == USART->Last_bit_clock_pulse)
{
SET_BIT(USART->Instance->USART_CR2,LAST_BIT_CLOCK_PULSE_BIT_POS);
}
else
{
/* Nothing */
}

return ret_val;
}

/**
 * @ brief configure USART Baud Rate
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t configure_Baud_Rate(USART_t* USART)
{
uint8_t ret_val = E_OK;
uint32_t PLCK1_temp_val,PLCK2_temp_val = 0;
uint8_t shift_val = 4;
double temp_val,temp_frac = 0 ;
switch(USART->USART_Per)
{
case USART1:
get_PCLK2_clock((RCC_OSC_Init_t *)&oscillator,&PLCK2_temp_val);
temp_val = PLCK2_temp_val/(DIVIDE_VAL * (USART->Baud_rate_val));
temp_frac = temp_val - ((uint32_t)temp_val);
temp_val -= temp_frac;
temp_frac *= 16;
temp_frac = ceil(temp_frac);
/* convert decimal to hexadecimal */
USART_1->USART_BRR |= (((uint32_t)temp_frac)%16);
while(temp_val > 0)
{
USART_1->USART_BRR |= (((uint32_t)temp_val % 16) << shift_val);
temp_val /= 16;
shift_val += 4;
}
break;
case USART2:
get_PCLK1_clock((RCC_OSC_Init_t *)&oscillator,&PLCK1_temp_val);
temp_val = PLCK1_temp_val/(DIVIDE_VAL * (USART->Baud_rate_val));
temp_frac = temp_val - ((uint32_t)temp_val);
temp_val -= temp_frac;
temp_frac *= 16;
temp_frac = ceil(temp_frac);
/* convert decimal to hexadecimal */
USART_2->USART_BRR |= (((uint32_t)temp_frac)%16);
while(temp_val > 0)
{
USART_2->USART_BRR |= (((uint32_t)temp_val % 16) << shift_val);
temp_val /= 16;
shift_val += 4;
}
break;
case USART3:
get_PCLK1_clock((RCC_OSC_Init_t *)&oscillator,&PLCK1_temp_val);
temp_val = PLCK1_temp_val/(DIVIDE_VAL * (USART->Baud_rate_val));
temp_frac = temp_val - ((uint32_t)temp_val);
temp_val -= temp_frac;
temp_frac *= 16;
temp_frac = ceil(temp_frac);
/* convert decimal to hexadecimal */
USART_3->USART_BRR |= (((uint32_t)temp_frac)%16);
while(temp_val > 0)
{
USART_3->USART_BRR |= (((uint32_t)temp_val % 16) << shift_val);
temp_val /= 16;
shift_val += 4;
}
break;
default : ret_val = E_NOK;
}
return ret_val;
}


/**
 * @ brief Enable Reception interrupt
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Enable_Reception_interrupt(USART_t* USART)
{
uint8_t ret_val = E_OK;
switch(USART->USART_Per)
{
case USART1:
USART1_receive_data_Interrupt_Handler = USART->Receive_data_Interrupt_Handler;
break;
case USART2:
USART2_receive_data_Interrupt_Handler = USART->Receive_data_Interrupt_Handler;
break;
case USART3:
USART3_receive_data_Interrupt_Handler = USART->Receive_data_Interrupt_Handler;
break;
default : ret_val = E_NOK;
}
SET_BIT(USART->Instance->USART_CR1,RECEIVE_INT_EN_BIT_POS);
return ret_val;
}

/**
 * @ brief Disable Reception interrupt
 * @ param USART Registers @ref USART_Registers_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Disable_Reception_interrupt(USART_Registers_t* USART_Inst)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(USART_Inst->USART_CR1,RECEIVE_INT_EN_BIT_POS);
counter = 0;
SET_BIT(USART_Inst->USART_CR1,RECEIVER_EN_BIT_POS);
SET_BIT(USART_Inst->USART_CR1,TRANSMITTER_EN_BIT_POS);
Reception_state = Ready;
return ret_val;
}

/**
 * @ brief Configure USART Interrupts
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t configure_Interrupt(USART_t* USART)
{
uint8_t ret_val = E_OK;
switch(USART->USART_Per)
{
case USART1:
if(Error_interrupt_Enable == USART->Error_interrupt)
{
SET_BIT(USART_1->USART_CR3,ERROR_INT_EN_BIT_POS);
USART1_Error_Interrupt_Handler = USART->Error_Interrupt_Handler;
}
else
{
/* Nothing */
}
if(Enable_CTS_Interrupt == USART->CTS_Interrupt)
{
SET_BIT(USART_1->USART_CR3,CTS_INT_EN_BIT_POS);
USART1_CTS_Interrupt_Handler = USART->CTS_Interrupt_Handler;
}
else
{
/* Nothing */
}
if(idle_line_interrupt_Enable == USART->idle_line_interrupt)
{
SET_BIT(USART_1->USART_CR1,IDLE_LINE_INT_EN_BIT_POS);
USART1_idle_line_Interrupt_Handler = USART->idle_line_Interrupt_Handler;
}
else
{
/* Nothing */
}
break;
case USART2:
if(Error_interrupt_Enable == USART->Error_interrupt)
{
SET_BIT(USART_2->USART_CR3,ERROR_INT_EN_BIT_POS);
USART2_Error_Interrupt_Handler = USART->Error_Interrupt_Handler;
}
else
{
/* Nothing */
}
if(Enable_CTS_Interrupt == USART->CTS_Interrupt)
{
SET_BIT(USART_2->USART_CR3,CTS_INT_EN_BIT_POS);
USART2_CTS_Interrupt_Handler = USART->CTS_Interrupt_Handler;
}
else
{
/* Nothing */
}
if(idle_line_interrupt_Enable == USART->idle_line_interrupt)
{
SET_BIT(USART_2->USART_CR1,IDLE_LINE_INT_EN_BIT_POS);
USART2_idle_line_Interrupt_Handler = USART->idle_line_Interrupt_Handler;
}
else
{
/* Nothing */
}
break;
case USART3:
if(Error_interrupt_Enable == USART->Error_interrupt)
{
SET_BIT(USART_3->USART_CR3,ERROR_INT_EN_BIT_POS);
USART3_Error_Interrupt_Handler = USART->Error_Interrupt_Handler;
}
else
{
/* Nothing */
}
if(Enable_CTS_Interrupt == USART->CTS_Interrupt)
{
SET_BIT(USART_3->USART_CR3,CTS_INT_EN_BIT_POS);
USART3_CTS_Interrupt_Handler = USART->CTS_Interrupt_Handler;
}
else
{
/* Nothing */
}
if(idle_line_interrupt_Enable == USART->idle_line_interrupt)
{
SET_BIT(USART_3->USART_CR1,IDLE_LINE_INT_EN_BIT_POS);
USART3_idle_line_Interrupt_Handler = USART->idle_line_Interrupt_Handler;
}
else
{
/* Nothing */
}
break;
default : ret_val = E_NOK;
}
return ret_val;
}

/**
 * @ brief Configure half duplex mode
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t set_half_duplex_mode(USART_t* USART)
{
uint8_t ret_val = E_OK;
SET_BIT(USART->Instance->USART_CR3,HALF_DUPLEX_MODE_EN_BIT_POS);
return ret_val;
}

/**
 * @ brief Configure DMA
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t configure_dma(USART_t* USART)
{
uint8_t ret_val = E_OK;
if(Enable_DMA_Receiver == USART->Receiver_DMA)
{
SET_BIT(USART->Instance->USART_CR3,RECEIVER_DMA_EN_BIT_POS);
}
else
{
/* Nothing */
}
if(Enable_DMA_Transmitter == USART->Transmitter_DMA)
{
SET_BIT(USART->Instance->USART_CR3,TRANSMITTER_DMA_EN_BIT_POS);
}
else
{
/* Nothing */
}
return ret_val;
}

/**
 * @ brief Configure hardware flow control
 * @ param USART Configuration @ref USART_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t configure_hardware_flow_control(USART_t* USART)
{
uint8_t ret_val = E_OK;
if(Enable_CTS == USART->CTS_Hardware)
{
SET_BIT(USART->Instance->USART_CR3,CTS_EN_BIT_POS);
}
else
{
/* Nothing */
}
if(Enable_RTS == USART->RTS_Hardware)
{
SET_BIT(USART->Instance->USART_CR3,RTS_EN_BIT_POS);
}
else
{
/* Nothing */
}
return ret_val;
}

/**
 * @ brief Tranmsit data in blocking mode
 * @ param USART Configuration @ref USART_t
 * @ param pointer to data
 * @ param data length
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t USART_Transmit_Data_Blocking(USART_t* USART,char* data,uint8_t len)
{
uint8_t ret_val = E_OK;
uint8_t i = 0;
while(i < len)
{
while(!(READ_BIT(USART->Instance->USART_SR,DATA_REG_EMPTY_FLAG_BIT_POS)));
USART->Instance->USART_DR = DATA_REG_MASK & ((char)(*data));
data++;
i++;
}
return ret_val;
}

/**
 * @ brief Receive data in blocking mode
 * @ param USART Configuration @ref USART_t
 * @ param pointer to data
 * @ param data length
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t USART_Receive_Data_Blocking(USART_t* USART,char* data,uint8_t len)
{
uint8_t ret_val = E_OK;
uint8_t i =0;
while(!(READ_BIT(USART->Instance->USART_SR,RECEIVE_DATA_FLAG_BIT_POS)));
while(i < len)
{
while(!(READ_BIT(USART->Instance->USART_SR,RECEIVE_DATA_FLAG_BIT_POS)));
data[i] = ((USART->Instance->USART_DR) & DATA_REG_MASK);
i++;
}
return ret_val;
}

/**
 * @ brief Enable Transmission Interrupt
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Enable_transmission_interrupt(USART_t* USART)
{
uint8_t ret_val = E_OK;
switch(USART->USART_Per)
{
case USART1:
USART1_Transmit_data_Interrupt_Handler = USART->Transmit_data_Interrupt_Handler;
break;
case USART2:
USART2_Transmit_data_Interrupt_Handler = USART->Transmit_data_Interrupt_Handler;
break;
case USART3:
USART3_Transmit_data_Interrupt_Handler = USART->Transmit_data_Interrupt_Handler;
break;
default : ret_val = E_NOK;
}
SET_BIT(USART->Instance->USART_CR1,DATA_REG_EMPTY_INT_EN_BIT_POS);
return ret_val;
}

/**
 * @ brief  Disable Transmission Interrupt
 * @ return function status
 * @ E_OK   function was completed successfully
 * @ E_NOK  function was completed unsuccessfully
 * */
static uint8_t Disable_transmission_interrupt(USART_Registers_t* USART_Inst)
{
uint8_t ret_val = E_OK;
CLEAR_BIT(USART_Inst->USART_CR1,DATA_REG_EMPTY_INT_EN_BIT_POS);
SET_BIT(USART_Inst->USART_CR1,TRANSMITTER_EN_BIT_POS);
SET_BIT(USART_Inst->USART_CR1,RECEIVER_EN_BIT_POS);
Transmission_state = Ready;
return ret_val;
}

/**
 * @ brief Tranmsit data in I mode
 * @ param USART Configuration @ref USART_t
 * @ param pointer to data
 * @ param data length
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t USART_Transmit_Data_Interrupt(USART_t* USART,char* data,uint8_t len)
{
uint8_t ret_val = E_OK;
if(Transmission_state == Ready)
{
Transmission_state = Busy;
Transmission_size = len;
Transmission_ptr_data = data;
ptr_Instance = USART->Instance;
USART->Instance->USART_DR = DATA_REG_MASK & ((char)(*Transmission_ptr_data));
Enable_transmission_interrupt(USART);
}
else if(Transmission_state == Busy)
{
ret_val = E_NOK;
}
return ret_val;
}


/**
 * @ brief Receiving data in Interrupt mode
 * @ param USART Configuration @ref USART_t
 * @ param pointer to data
 * @ param data length
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t USART_Receive_Data_Interrupt(USART_t* USART,char* data,uint8_t len)
{
uint8_t ret_val = E_OK;
if(Reception_state == Ready)
{
Reception_state = Busy;
Reception_size = len;
Reception_ptr_data = data;
ptr_Instance = USART->Instance;
Enable_Reception_interrupt(USART);
}
else if(Reception_state == Busy)
{
ret_val = E_NOK;
}
return ret_val;
}


/**
 * @ brief Transmit data in interrupt mode (helper function)
 * @ param USART Registers @ref USART_Registers_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Transmit_interrupt(USART_Registers_t* USART_Inst)
{
uint8_t ret_val = E_OK;
USART_Inst->USART_DR = DATA_REG_MASK & ((char)(*Transmission_ptr_data));
return ret_val;
}

/**
 * @ brief Receive data in interrupt mode (helper function)
 * @ param USART Registers @ref USART_Registers_t
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
static uint8_t Receive_interrupt(USART_Registers_t* USART_Inst)
{
uint8_t ret_val = E_OK;
Reception_ptr_data[counter] = ((USART_Inst->USART_DR) & DATA_REG_MASK);
counter++;
return ret_val;
}

/**
 * @ brief Transmit data using DMA
 * @ param USART Configurations @ref USART_t
 * @ param DMA Configurations @ref USART_t
 * @ param pointer to data
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t USART_Transmit_Data_DMA(USART_t* USART,DMA_t* DMA,char* data,uint16_t len)
{
uint8_t ret_val = E_NOK;
DMA_DeInit(DMA);
DMA_Init(DMA);
DMA->number_of_data_to_trasfer = len;
set_number_of_data_to_transfer(DMA,len);
Set_source_aaddress(DMA,(uint32_t)data);
Set_destination_aaddress(DMA,(uint32_t)&(USART_1->USART_DR));
CLEAR_BIT(USART->Instance->USART_SR,TRANSMISSION_COMP_INT_EN_BIT_POS);
SET_BIT(USART->Instance->USART_CR1,TRANSMITTER_EN_BIT_POS);
start_DMA(DMA);

return ret_val;
}


/**
 * @ brief Receive data using DMA
 * @ param USART Configurations @ref USART_t
 * @ param DMA Configurations @ref USART_t
 * @ param pointer to data
 * @ return function status
 * @ E_OK  function was completed successfully
 * @ E_NOK function was completed unsuccessfully
 * */
uint8_t USART_Receive_Data_DMA(USART_t* USART,DMA_t* DMA,char* data,uint16_t len)
{
uint8_t ret_val = E_NOK;
DMA_DeInit(DMA);
DMA_Init(DMA);
DMA->number_of_data_to_trasfer = len;
set_number_of_data_to_transfer(DMA,len);
Set_destination_aaddress(DMA,(uint32_t)&(USART->Instance->USART_DR));
Set_source_aaddress(DMA,(uint32_t)data);
Enable_USART(USART);
CLEAR_BIT(USART->Instance->USART_SR,TRANSMISSION_COMP_INT_EN_BIT_POS);
start_DMA(DMA);
CLEAR_BIT(USART->Instance->USART_SR,OVERRUN_ERROR_FLAG_BIT_POS);
return ret_val;
}

/* USART1 IRQ Handler*/
void USART1_IRQHandler(void)
{
if((TRUE == READ_BIT(ptr_Instance->USART_CR1,RECEIVE_INT_EN_BIT_POS)) && (TRUE == READ_BIT(ptr_Instance->USART_SR,RECEIVE_DATA_FLAG_BIT_POS)))
{
if(Reception_size > 0)
{
--Reception_size;
Receive_interrupt(ptr_Instance);
if(Reception_size <= 0)
{
Disable_Reception_interrupt(ptr_Instance);
if(USART1_receive_data_Interrupt_Handler)
{
USART1_receive_data_Interrupt_Handler();
}
else
{
/* Nothing */
}
}
else
{
/* Nothing */
}
}
}
else
{
/* Nothing */
}
if((TRUE == READ_BIT(ptr_Instance->USART_CR1,DATA_REG_EMPTY_INT_EN_BIT_POS)) && (TRUE == READ_BIT(ptr_Instance->USART_SR,DATA_REG_EMPTY_FLAG_BIT_POS)))
{
if(Transmission_size > 0)
{
++Transmission_ptr_data;
--Transmission_size;
Transmit_interrupt(ptr_Instance);
}
else
{
while(!(READ_BIT(ptr_Instance->USART_SR,TRANSMISSION_COMP_INT_EN_BIT_POS)));
Disable_transmission_interrupt(ptr_Instance);
if(USART1_Transmit_data_Interrupt_Handler)
{
USART1_Transmit_data_Interrupt_Handler();
}
}
}
else
{
/* Nothing */
}

if((TRUE == READ_BIT(ptr_Instance->USART_CR3,ERROR_INT_EN_BIT_POS)) && ((TRUE == READ_BIT(ptr_Instance->USART_SR,FRAME_ERROR_FLAG_BIT_POS)) \
	|| (TRUE == READ_BIT(ptr_Instance->USART_SR,NOISE_ERROR_FLAG_BIT_POS)) || (TRUE == READ_BIT(ptr_Instance->USART_SR,OVERRUN_ERROR_FLAG_BIT_POS))))
{
CLEAR_BIT(ptr_Instance->USART_SR,FRAME_ERROR_FLAG_BIT_POS);
CLEAR_BIT(ptr_Instance->USART_SR,NOISE_ERROR_FLAG_BIT_POS);
CLEAR_BIT(ptr_Instance->USART_SR,OVERRUN_ERROR_FLAG_BIT_POS);
}
else
{
/* Nothing */
}
}


/* USART2 IRQ Handler*/
void USART2_IRQHandler(void)
{
if((TRUE == READ_BIT(ptr_Instance->USART_CR1,RECEIVE_INT_EN_BIT_POS)) && (TRUE == READ_BIT(ptr_Instance->USART_SR,RECEIVE_DATA_FLAG_BIT_POS)))
{
if(Reception_size > 0)
{
--Reception_size;
Receive_interrupt(ptr_Instance);
if(Reception_size <= 0)
{
Disable_Reception_interrupt(ptr_Instance);
if(USART1_receive_data_Interrupt_Handler)
{
USART1_receive_data_Interrupt_Handler();
}
else
{
/* Nothing */
}
}
else
{
/* Nothing */
}
}
}
else
{
/* Nothing */
}
if((TRUE == READ_BIT(ptr_Instance->USART_CR1,DATA_REG_EMPTY_INT_EN_BIT_POS)) && (TRUE == READ_BIT(ptr_Instance->USART_SR,DATA_REG_EMPTY_FLAG_BIT_POS)))
{
if(Transmission_size > 0)
{
++Transmission_ptr_data;
--Transmission_size;
Transmit_interrupt(ptr_Instance);
}
else
{
while(!(READ_BIT(ptr_Instance->USART_SR,TRANSMISSION_COMP_INT_EN_BIT_POS)));
Disable_transmission_interrupt(ptr_Instance);
if(USART1_Transmit_data_Interrupt_Handler)
{
USART1_Transmit_data_Interrupt_Handler();
}
}
}
else
{
/* Nothing */
}

if((TRUE == READ_BIT(ptr_Instance->USART_CR3,ERROR_INT_EN_BIT_POS)) && ((TRUE == READ_BIT(ptr_Instance->USART_SR,FRAME_ERROR_FLAG_BIT_POS)) \
	|| (TRUE == READ_BIT(ptr_Instance->USART_SR,NOISE_ERROR_FLAG_BIT_POS)) || (TRUE == READ_BIT(ptr_Instance->USART_SR,OVERRUN_ERROR_FLAG_BIT_POS))))
{
CLEAR_BIT(ptr_Instance->USART_SR,FRAME_ERROR_FLAG_BIT_POS);
CLEAR_BIT(ptr_Instance->USART_SR,NOISE_ERROR_FLAG_BIT_POS);
CLEAR_BIT(ptr_Instance->USART_SR,OVERRUN_ERROR_FLAG_BIT_POS);
}
else
{
/* Nothing */
}
}

/* USART2 IRQ Handler*/
void USART3_IRQHandler(void)
{
if((TRUE == READ_BIT(ptr_Instance->USART_CR1,RECEIVE_INT_EN_BIT_POS)) && (TRUE == READ_BIT(ptr_Instance->USART_SR,RECEIVE_DATA_FLAG_BIT_POS)))
{
if(Reception_size > 0)
{
--Reception_size;
Receive_interrupt(ptr_Instance);
if(Reception_size <= 0)
{
Disable_Reception_interrupt(ptr_Instance);
if(USART1_receive_data_Interrupt_Handler)
{
USART1_receive_data_Interrupt_Handler();
}
else
{
/* Nothing */
}
}
else
{
/* Nothing */
}
}
}
else
{
/* Nothing */
}
if((TRUE == READ_BIT(ptr_Instance->USART_CR1,DATA_REG_EMPTY_INT_EN_BIT_POS)) && (TRUE == READ_BIT(ptr_Instance->USART_SR,DATA_REG_EMPTY_FLAG_BIT_POS)))
{
if(Transmission_size > 0)
{
++Transmission_ptr_data;
--Transmission_size;
Transmit_interrupt(ptr_Instance);
}
else
{
while(!(READ_BIT(ptr_Instance->USART_SR,TRANSMISSION_COMP_INT_EN_BIT_POS)));
Disable_transmission_interrupt(ptr_Instance);
if(USART1_Transmit_data_Interrupt_Handler)
{
USART1_Transmit_data_Interrupt_Handler();
}
}
}
else
{
/* Nothing */
}

if((TRUE == READ_BIT(ptr_Instance->USART_CR3,ERROR_INT_EN_BIT_POS)) && ((TRUE == READ_BIT(ptr_Instance->USART_SR,FRAME_ERROR_FLAG_BIT_POS)) \
	|| (TRUE == READ_BIT(ptr_Instance->USART_SR,NOISE_ERROR_FLAG_BIT_POS)) || (TRUE == READ_BIT(ptr_Instance->USART_SR,OVERRUN_ERROR_FLAG_BIT_POS))))
{
CLEAR_BIT(ptr_Instance->USART_SR,FRAME_ERROR_FLAG_BIT_POS);
CLEAR_BIT(ptr_Instance->USART_SR,NOISE_ERROR_FLAG_BIT_POS);
CLEAR_BIT(ptr_Instance->USART_SR,OVERRUN_ERROR_FLAG_BIT_POS);
}
else
{
/* Nothing */
}
}
