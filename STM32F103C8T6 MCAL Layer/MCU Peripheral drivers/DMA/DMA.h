/* 
 * File:   	DMA.h
 * Author: Amr Ali
 * @brief Direct Memory Access driver  
 */

#ifndef _DMA_H_
#define _DMA_H_


/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
#include "RCC.h"
#include <stddef.h>
/*************Macro declarations****************/
#define DMA1_BASE_ADDRESS        	0x40020000
#define DMA1                     	((DMA_registers_t *)DMA1_BASE_ADDRESS)
#define DMA_CLOCK_BIT_POS        	 0U
#define CHANNEL_EN_BIT_POS       	 0U
#define CHANNEL_PRIORITY_MASK    	 0x3000U
#define CHANNEL_PRIORITY_BIT_POS 	 12U
#define DATA_DIRECTION_BIT_POS       4U
#define TRANSFER_ER_INT_BIT_POS   	 3U
#define TRANSFER_HLF_TR_INT_BIT_POS  2U
#define TRANSFER_COM_TR_INT_BIT_POS  1U
#define GLOBAL_INT_CLEAR_BIT_POS     0U
#define COMP_TRANSFER_FLAG_BIT_POS   1U
#define HALF_TRANSFER_FLAG_BIT_POS   2U
#define ERROR_TRANSFER_FLAG_BIT_POS  3U
#define MEM_TO_MEM_MODE_BIT_POS      14U
#define CIRCULAR_MODE_BIT_POS        5U
#define MEM_SIZE_BITS_POS            10U
#define MEM_SIZE_BITS_MASK           0xC00
#define PERIPHERAL_SIZE_BITS_POS     8U
#define PERIPHERAL_SIZEBITS_MASK     0x300
#define PERIPH_INC_MOD_BIT_POS       6U
#define MEM_INC_MOD_BIT_POS          7U
/*************Data Types Declarations****************/
typedef enum
{
Low,
Medium,
High,
Very_high
}channel_priority_t;

typedef enum
{
one_Byte,
half_word,
word
}data_size_t;
typedef enum
{
Read_from_peripheral,
Read_from_memory
}data_direction_t;

typedef enum
{
channel_1,
channel_2,
channel_3,
channel_4,
channel_5,
channel_6,
channel_7
}channel_t;

typedef enum
{
Transfer_error_interrupt_Enable,
Transfer_error_interrupt_Disable,
Half_Transfer_interrupt_Enable,
Half_Transfer_interrupt_Disable,
complete_Transfer_interrupt_Enable,
complete_Transfer_interrupt_Disable
}Interrupt_config_t;

typedef enum
{
Normal_Mode,
Circular_Mode
}mode_type_t;

typedef enum
{
Memory_to_memory_mode_disabled,
Memory_to_memory_mode_enabled
}transfer_type_t;

typedef enum
{
Memory_increment_mode_disabled,
Memory_increment_mode_enabled
}Memory_increment_mode_t;

typedef enum
{
Peripheral_increment_mode_disabled,
Peripheral_increment_mode_enabled
}Peripheral_increment_mode_t;

typedef struct
{
volatile uint32_t DMA_ISR;
volatile uint32_t DMA_IFCR;
volatile uint32_t DMA_CCR1;
volatile uint32_t DMA_CNDTR1;
volatile uint32_t DMA_CPAR1;
volatile uint32_t DMA_CMAR1;
volatile uint32_t Reserved;
volatile uint32_t DMA_CCR2;
volatile uint32_t DMA_CNDTR2;
volatile uint32_t DMA_CPAR2;
volatile uint32_t DMA_CMAR2;
volatile uint32_t Reserved1;
volatile uint32_t DMA_CCR3;
volatile uint32_t DMA_CNDTR3;
volatile uint32_t DMA_CPAR3;
volatile uint32_t DMA_CMAR3;
volatile uint32_t Reserved2;
volatile uint32_t DMA_CCR4;
volatile uint32_t DMA_CNDTR4;
volatile uint32_t DMA_CPAR4;
volatile uint32_t DMA_CMAR4;
volatile uint32_t Reserved3;
volatile uint32_t DMA_CCR5;
volatile uint32_t DMA_CNDTR5;
volatile uint32_t DMA_CPAR5;
volatile uint32_t DMA_CMAR5;
volatile uint32_t Reserved4;
volatile uint32_t DMA_CCR6;
volatile uint32_t DMA_CNDTR6;
volatile uint32_t DMA_CPAR6;
volatile uint32_t DMA_CMAR6;
volatile uint32_t Reserved5;
volatile uint32_t DMA_CCR7;
volatile uint32_t DMA_CNDTR7;
volatile uint32_t DMA_CPAR7;
volatile uint32_t DMA_CMAR7;
}DMA_registers_t;


typedef struct
{
	void (*Error_Transfer_callback)(void);
	void (*Half_Transfer_callback)(void);
	void (*Complete_Transfer_callback)(void);
	channel_t channel;
	channel_priority_t priority;
	data_direction_t direction;
	data_size_t Memory_Size;
	data_size_t Peripheral_Size;
	mode_type_t mode;
	Interrupt_config_t Error_interrupt;
	Interrupt_config_t Half_Transfer_interrupt;
	Interrupt_config_t Complete_Transfer_interrupt;
	uint16_t number_of_data_to_trasfer;
	transfer_type_t transfer_type;
	Peripheral_increment_mode_t  Peripheral_increment_mode;
	Memory_increment_mode_t  	 Memory_increment_mode;
}DMA_t;

/*************function prototypes****************/
uint8_t DMA_Init(DMA_t* DMA);
uint8_t DMA_DeInit(DMA_t* DMA);
uint8_t Set_destination_aaddress(DMA_t* DMA,uint32_t address);
uint8_t Set_source_aaddress(DMA_t* DMA,uint32_t address);
uint8_t start_DMA(DMA_t* DMA);



















#endif
