/* 
 * File:   GPIO.h
 * Author: Amr Ali
 * @brief General Purpose input output driver  
 */

#ifndef _GPIO_H_
#define _GPIO_H_


/*************Includes****************/
#include <stdint.h>
#include "C:\Users\Kimo Store\STM32CubeIDE\workspace_1.13.0\Project_Two\common_cfg.h"
/*************Macro declarations****************/
#define GPIO_CLOCK_ADD                  *((uint32_t *)0x40021018)
#define GPIO_CLOCK_BIT_POS				2
#define GPIO_PORTA_BASE_ADDRESS         0x40010800
#define GPIO_PORTA                      ((GPIO_register_t *)GPIO_PORTA_BASE_ADDRESS)
#define GPIO_PORTB_BASE_ADDRESS         0x40010C00
#define GPIO_PORTB                      ((GPIO_register_t *)GPIO_PORTB_BASE_ADDRESS)
#define GPIO_PORTC_BASE_ADDRESS         0x40011000
#define GPIO_PORTC                      ((GPIO_register_t *)GPIO_PORTC_BASE_ADDRESS)
#define GPIO_PORTD_BASE_ADDRESS         0x40011400
#define GPIO_PORTD                      ((GPIO_register_t *)GPIO_PORTD_BASE_ADDRESS)
#define GPIO_PORTE_BASE_ADDRESS         0x40011800
#define GPIO_PORTE                      ((GPIO_register_t *)GPIO_PORTE_BASE_ADDRESS)
#define GPIO_PORTF_BASE_ADDRESS         0x40011C00
#define GPIO_PORTF                      ((GPIO_register_t *)GPIO_PORTF_BASE_ADDRESS)
#define GPIO_PORTG_BASE_ADDRESS         0x40012000
#define GPIO_PORTG                      ((GPIO_register_t *)GPIO_PORTG_BASE_ADDRESS)
#define PIN_CLEAR                       0x0000000F

/*************Data Types Declarations****************/
typedef enum
{
Input_mode, // (reset state)
Output_mode_max_speed_10_MHz,
Output_mode_max_speed_2_MHz,
Output_mode_max_speed_50_MHz
}Pin_mode_t;

typedef enum
{
General_purpose_output_push_pull,
General_purpose_output_Open_drain,
Alternate_function_output_Push_pull,
Alternate_function_output_Open_drain
}Pin_output_mode_t;

typedef enum
{
Analog_mode,
Floating_mode, // (reset state)
Input_with_pull_up_pull_down
}Pin_input_mode_t;


typedef enum
{
Port_A,
Port_B,
Port_C,
Port_D,
Port_E,
Port_F,
Port_G
}Port_t;

typedef enum
{
Pin0,
Pin1,
Pin2,
Pin3,
Pin4,
Pin5,
Pin6,
Pin7,
Pin8,
Pin9,
Pin10,
Pin11,
Pin12,
Pin13,
Pin14,
Pin15
}Pin_t;


typedef enum
{
Pin_Reset,
Pin_Set
}Pin_state,t;

typedef struct
{
volatile uint32_t GPIOx_CRL;
volatile uint32_t GPIOx_CRH;
volatile uint32_t GPIOx_IDR;
volatile uint32_t GPIOx_ODR;
volatile uint32_t GPIOx_BSRR;
volatile uint32_t GPIOx_BRR;
volatile uint32_t GPIOx_LCKR;
}GPIO_register_t;

typedef struct
{
Port_t Port_Num;
Pin_t Pin_Num;
Pin_mode_t pin_mode;
Pin_input_mode_t pin_input_mode;
Pin_output_mode_t pin_output_mode;
}Pin_config_t;

/*************function prototypes****************/
uint8_t Enable_Port_Clock(Port_t Port);
uint8_t Disable_Port_Clock(Port_t Port);
uint8_t GPIO_config(Pin_config_t* GPIO_Pin);
uint8_t Read_Pin_Status(Port_t Port,Pin_t Pin,uint8_t* state);
uint8_t Write_Pin(Port_t Port,Pin_t Pin,Pin_state state);
uint8_t Toggle_Pin(Port_t Port,Pin_t Pin);


#endif
