#ifndef _NVIC_H_
#define _NVIC_H_

/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
/*************Macro declarations****************/
#define NVIC_BASE_ADDRESS 	(0xE000E100UL)
#define NVIC             	((NVIC_Type *)(NVIC_BASE_ADDRESS))

#define SCB_BASE_ADDRESS 	(0xE000ED00UL)
#define SCB             	((SCB_Type *)(SCB_BASE_ADDRESS))

#define SCB_AIRCR_VECTKEY_POS   16U
#define SCB_AIRCR_VECTKEY_MASK  (0XFFFFUL << SCB_AIRCR_VECTKEY_POS)

#define SCB_PRIORITY_GROUP_POS   8U
#define SCB_PRIORITY_GROUP_MASK  (0X7UL << SCB_PRIORITY_GROUP_POS)

#define VECTKEY_VALUE 0x05FA
#define SET_VECTKEY_VALUE (VECTKEY_VALUE << SCB_AIRCR_VECTKEY_POS)

#define BIT_SHIFT(IRQ) ((((uint32_t)IRQ) & ((uint32_t)0x03UL)) * 8UL)

#define PRIORITY_LEVEL_MSK 4U





/*************Data Types Declarations****************/
/* NVIC Data type*/
typedef struct{
volatile uint32_t ISER[8U];
uint32_t Reserved0[24U];
volatile uint32_t ICER[8U];
uint32_t Reserved1[24U];
volatile uint32_t ISPR[8U];
uint32_t Reserved2[24U];
volatile uint32_t ICPR[8U];
uint32_t Reserved3[24U];
volatile uint32_t IABR[8U];
uint32_t Reserved4[56U];
volatile uint32_t IPR[60U];
uint32_t Reserved5[643U];
volatile uint32_t STIR;
}NVIC_Type;


typedef struct
{
volatile uint32_t	CPUID;
volatile uint32_t	ICSR;
volatile uint32_t	VTOR;
volatile uint32_t	AIRCR;
volatile uint32_t	SCR;
volatile uint32_t	CCR;
volatile uint32_t	SHPR[3U];
volatile uint32_t	SHCRS;
}SCB_Type;

typedef enum
{
group_16_sub_1  = 3,
group_8_sub_2   = 4,
group_4_sub_4   = 5,
group_2_sub_8   = 6,
group_1_sub_16  = 7,
}Priority_Grouping_t;

typedef enum {
Non_Maskable_Interrupt_IRQ 	  = -14,
Hard_Fault_Interrupt_IRQ 	  = -13,
Mem_Manage_Interrupt_IRQ 	  = -12,
Bus_Fault_Interrupt_IRQ 	  = -11,
Usage_Fault_Interrupt_IRQ  	  = -10,
SV_Call_Interrupt_IRQ		  = -5,
Debug_Monitor_Interrupt_IRQ   = -4,
Pend_SV_Interrupt_IRQ 		  = -2,
SysTick_Interrupt_IRQ 		  = -1,
WWDG_Interrupt_IRQ 			  = 0,
PVD_Interrupt_IRQ  			  = 1,
TAMPER_Interrupt_IRQ 		  = 2,
RTC_Interrupt_IRQ 			  = 3,
FLASH_Interrupt_IRQ 		  = 4,
RCC_Interrupt_IRQ 			  = 5,
EXTI0_Interrupt_IRQ 		  = 6,
EXTI1_Interrupt_IRQ			  = 7,
EXTI2_Interrupt_IRQ 		  = 8,
EXTI3_Interrupt_IRQ 		  = 9,
EXTI4_Interrupt_IRQ 		  = 10,
DMA1_Channel1_Interrupt_IRQ   = 11,
DMA1_Channel2_Interrupt_IRQ   = 12,
DMA1_Channel3_Interrupt_IRQ   = 13,
DMA1_Channel4_Interrupt_IRQ   = 14,
DMA1_Channel5_Interrupt_IRQ   = 15,
DMA1_Channel6_Interrupt_IRQ   = 16,
DMA1_Channel7_Interrupt_IRQ   = 17,
ADC1_2_Interrupt_IRQ 		  = 18,
USB_HP_CAN_TX_Interrupt_IRQ   = 19,
USB_LP_CAN_RX0_Interrupt_IRQ  = 20,
CAN_RX1_Interrupt_IRQ 		  = 21,
CAN_SCE_Interrupt_IRQ 		  = 22,
EXTI9_5_Interrupt_IRQ 		  = 23,
TIM1_BRK_Interrupt_IRQ 		  = 24,
TIM1_UP_Interrupt_IRQ 		  = 25,
TIM1_TRG_COM_Interrupt_IRQ    = 26,
TIM1_CC_Interrupt_IRQ  		  = 27,
TIM2_Interrupt_IRQ  		  = 28,
TIM3_Interrupt_IRQ            = 29,
TIM4_Interrupt_IRQ  		  = 30,
I2C1_EV_Interrupt_IRQ  		  = 31,
I2C1_ER_Interrupt_IRQ         = 32,
I2C2_EV_Interrupt_IRQ         = 33,
I2C2_ER_Interrupt_IRQ 		  = 34,
SPI1_Interrupt_IRQ            = 35,
SPI2_Interrupt_IRQ            = 36,
USART1_Interrupt_IRQ 		  = 37,
USART2_Interrupt_IRQ 		  = 38,
USART3_Interrupt_IRQ 		  = 39,
EXTI15_10_Interrupt_IRQ 	  = 40,
RTCAlarm_Interrupt_IRQ 		  = 41,
USBWakeup_Interrupt_IRQ       = 42,
TIM8_BRK_Interrupt_IRQ 		  = 43,
TIM8_UP_Interrupt_IRQ 		  = 44,
TIM8_TRG_COM_Interrupt_IRQ 	  = 45,
TIM8_CC_Interrupt_IRQ 		  = 46,
ADC3_Interrupt_IRQ 		      = 47,
FSMC_Interrupt_IRQ   		  = 48,
SDIO_Interrupt_IRQ  		  = 49,
TIM5_Interrupt_IRQ  		  = 50,
SPI3_Interrupt_IRQ            = 51,
UART4_Interrupt_IRQ  		  = 52,
UART5_Interrupt_IRQ  		  = 53,
TIM6_Interrupt_IRQ            = 54,
TIM7_Interrupt_IRQ            = 55,
DMA2_Channel1_Interrupt_IRQ   = 56,
DMA2_Channel2_Interrupt_IRQ   = 57,
DMA2_Channel3_Interrupt_IRQ   = 58,
DMA2_Channel4_5_Interrupt_IRQ = 59,
}NVIC_IRQ_t;





/*************Data Types Declarations****************/
uint8_t NVIC_Enabel_IRQ(NVIC_IRQ_t IRQ);
uint8_t NVIC_Disable_IRQ(NVIC_IRQ_t IRQ);
uint8_t NVIC_Set_Pending_State_IRQ(NVIC_IRQ_t IRQ);
uint8_t NVIC_Clear_Pending_State_IRQ(NVIC_IRQ_t IRQ);
uint8_t NVIC_Get_Active_State_IRQ(NVIC_IRQ_t IRQ,uint8_t *state);
uint8_t NVIC_Set_Priority_group(Priority_Grouping_t PriorityGroup);
uint8_t NVIC_Config_Prioirty_IRQ(NVIC_IRQ_t IRQ,uint32_t Priority);
#endif
