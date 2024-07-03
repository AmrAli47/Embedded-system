/* 
 * File:   	USART.h
 * Author: Amr Ali
 * @brief Universal Synchronous Asynchronous Receiver Transmitter driver  
 */

#ifndef _USART_H_
#define _USART_H_




/*************Includes****************/
#include <stdint.h>
#include <math.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
#include "RCC.h"
#include "DMA.h"
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\HAL_Drivers\inc\GPIO.h"
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\core\inc\systick.h"
/*************Macro declarations****************/
#define USART1_BASE_ADDRESS           0x40013800
#define USART_1					      ((USART_Registers_t *)USART1_BASE_ADDRESS)
#define USART2_BASE_ADDRESS           0x40004400
#define USART_2						  ((USART_Registers_t *)USART2_BASE_ADDRESS)
#define USART3_BASE_ADDRESS           0x40004800
#define USART_3					      ((USART_Registers_t *)USART3_BASE_ADDRESS)

#define USART_EN_BIT_POS              			13
#define WORD_LENGTH_BIT_BIT_POS      			12
#define USART1_CLOCK_EN_BIT_POS       			14
#define USART2_CLOCK_EN_BIT_POS      			17
#define USART3_CLOCK_EN_BIT_POS       			18
#define UART4_CLOCK_EN_BIT_POS       			19
#define UART5_CLOCK_EN_BIT_POS       			20
#define USART_STOP_BITS_POS           			12
#define USART_STOP_BITS_MSK		      			0x3000
#define TRANSMITTER_EN_BIT_POS        			3
#define RECEIVER_EN_BIT_POS           			2
#define PARITY_CONTROL_BIT_POS                  10
#define CLOCK_PHASE_BIT_POS                     9
#define CLOCK_POLARITY_BIT_POS                  10
#define CLOCK_EN_BIT_POS                        11
#define LAST_BIT_CLOCK_PULSE_BIT_POS            8
#define PARITY_SELECTION_BIT_POS                9
#define TRANSMISSION_COMP_INT_EN_BIT_POS        6
#define RECEIVER_INTERRUPT_EN_BIT_POS     		4
#define DIVIDE_VAL                              16.0
#define DIV_MANTISSA_BIT_POS                    4
#define ERROR_INT_EN_BIT_POS                    0
#define HALF_DUPLEX_MODE_EN_BIT_POS             3
#define RECEIVER_DMA_EN_BIT_POS                 6
#define TRANSMITTER_DMA_EN_BIT_POS              7
#define DATA_REG_EMPTY_INT_EN_BIT_POS           7
#define DATA_REG_EMPTY_FLAG_BIT_POS             7
#define RTS_EN_BIT_POS                          8
#define CTS_EN_BIT_POS                          9
#define CTS_INT_EN_BIT_POS                      10
#define IDLE_LINE_INT_EN_BIT_POS                4
#define DATA_REG_MASK                           0x000000FF
#define RECEIVE_INT_EN_BIT_POS                  5
#define RECEIVE_DATA_FLAG_BIT_POS               5
#define TRUE                                    1
#define FRAME_ERROR_FLAG_BIT_POS                1
#define NOISE_ERROR_FLAG_BIT_POS                2
#define OVERRUN_ERROR_FLAG_BIT_POS              3

/*************Data Types Declarations****************/
typedef enum
{
USART1,
USART2,
USART3
}USART_Peripherals_t;

typedef enum
{
Busy,
Ready
}state_t;
typedef enum
{
Disable_half_duplex_mode,
Enable_half_duplex_mode
}Half_duplex_mode_t;

typedef enum
{
Disable_DMA_Receiver,
Enable_DMA_Receiver
}Receiver_DMA_t;

typedef enum
{
Disable_DMA_Transmitter,
Enable_DMA_Transmitter
}Transmitter_DMA_t;

typedef enum
{
Disable_RTS,
Enable_RTS
}RTS_Hardware_t;

typedef enum
{
Disable_CTS,
Enable_CTS
}CTS_Hardware_t;

typedef enum
{
Disable_CTS_Interrupt,
Enable_CTS_Interrupt
}CTS_Interrupt_t;

typedef enum
{
Asynchronous,
Synchronous
}USART_mode_t;

typedef enum
{
No_clock_pulse_in_last_bit,
Send_clock_pulse_in_last_bit
}Last_bit_clock_pulse_t;

typedef enum
{
Clock_Disable,
Clock_Enable
}Clock_mode_t;

typedef enum
{
idle_state_is_low,
idle_state_is_high
}Clock_Polarity_t;

typedef enum
{
data_capture_edge_in_first_clock_transition,
data_capture_edge_in_second_clock_transition
}Clock_Phase_t;

typedef enum
{
Error_interrupt_disable,
Error_interrupt_Enable
}Error_interrupt_t;

typedef enum
{
idle_line_interrupt_disable,
idle_line_interrupt_Enable
}idle_Line_interrupt_t;

typedef enum
{
Disable_IDLE_Interrupt,
Enable_IDLE_Interrupt
}IDLE_Interrupt_t;

typedef enum
{
Disable_Receiving_Interrupt,
Enable_Receiving_Interrupt
}Receiving_Interrupt_t;

typedef enum
{
Disable_Transmission_Interrupt,
Enable_Transmission_Interrupt
}Transmission_Interrupt_t;

typedef enum
{
Disable_Interurpt_when_data_register_is_empty,
Enable_Interurpt_when_data_register_is_empty
}Data_Register_empty_Interrupt_t;


typedef enum
{
disable_Parity_control,
Enable_Parity_control
}Parity_control_t;

typedef enum
{
Even_parity,
Odd_parity
}Parity_t;

typedef enum
{
stop_bit_len_1 = 0,
stop_bit_len_2 = 2
}stop_bits_t;

typedef enum
{
data_length_len_8,
data_length_len_9
}word_length_t;

typedef enum
{
Disable_Transmitter,
Enable_Transmitter
}Transmitter_mode_t;

typedef enum
{
Disable_Receiver,
Enable_Receiver
}Receiver_mode_t;

typedef struct
{
uint32_t USART_SR;
uint32_t USART_DR;
uint32_t USART_BRR;
uint32_t USART_CR1;
uint32_t USART_CR2;
uint32_t USART_CR3;
uint32_t USART_GTPR;
}USART_Registers_t;


typedef struct
{
void (* Error_Interrupt_Handler)(void);
void (* Transmission_Complete_Interrupt_Handler)(void);
void (* CTS_Interrupt_Handler)(void);
void (* idle_line_Interrupt_Handler)(void);
void (* Receive_data_Interrupt_Handler)(void);
void (* Transmit_data_Interrupt_Handler)(void);
USART_Registers_t*                  Instance;
USART_Peripherals_t					USART_Per;
USART_mode_t         	 			USART_mode;
word_length_t        	 			word_length;
stop_bits_t 		 	 			stop_bits_len;
Transmitter_mode_t   	 			Tansmitter_mode;
Receiver_mode_t      	 			Receiver_mode;
Parity_control_t     	 			Parity_control;
Parity_t			 	 			Parity;
Clock_mode_t        	 			clock_mode;
Clock_Polarity_t	 	 			clock_polarity;
Clock_Phase_t        	 			clock_phase;
Last_bit_clock_pulse_t   			Last_bit_clock_pulse;
uint32_t                			Baud_rate_val;
Error_interrupt_t		 			Error_interrupt;
Half_duplex_mode_t       			Half_duplex_mode;
Receiver_DMA_t			 			Receiver_DMA;
Transmitter_DMA_t		 			Transmitter_DMA;
Data_Register_empty_Interrupt_t     Data_Register_empty_Interrupt;
RTS_Hardware_t                      RTS_Hardware;
CTS_Hardware_t                      CTS_Hardware;
CTS_Interrupt_t					    CTS_Interrupt;
idle_Line_interrupt_t				idle_line_interrupt;
}USART_t;







/*************function prototypes****************/
uint8_t USART_Init(USART_t* USART);
uint8_t USART_DeInit(USART_t* USART);
uint8_t USART_Transmit_Data_Blocking(USART_t* USART,char* data,uint8_t len);
uint8_t USART_Receive_Data_Blocking(USART_t* USART,char* data,uint8_t len);
uint8_t USART_Transmit_Data_Interrupt(USART_t* USART,char* data,uint8_t len);
uint8_t USART_Receive_Data_Interrupt(USART_t* USART,char* data,uint8_t len);
uint8_t USART_Transmit_Data_DMA(USART_t* USART,DMA_t* DMA,char* data,uint16_t len);
uint8_t USART_Receive_Data_DMA(USART_t* USART,DMA_t* DMA,char* data,uint16_t len);
#endif
