/* 
 * File:   mcal_timer0.h
 * Author: Amr Ali
 *
 * Created on March 24, 2024, 2:59 AM
 */

#ifndef MCAL_TIMER0_H
#define	MCAL_TIMER0_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/Interal_Interrupts/mcal_internal_interrupt.h"

/*----------------Macros----------------*/


/*----------------Macro_Functions----------------*/
// Timer0_Module_Enable
#define Timer0_Module_Enable()  (T0CONbits.TMR0ON = 1)
// Timer0_Module_Enable
#define Timer0_Module_Disable()  (T0CONbits.TMR0ON = 0)

// Timer0 Timer Mode
#define Timer0_Timer_Mode()  (T0CONbits.T0CS = 0)
// Timer0 Counter Mode
#define Timer0_Counter_Mode() (T0CONbits.T0CS = 1)

// Timer0 8 Bit Register
#define Timer0_8_Bit_Register()   (T0CONbits.T08BIT = 1)
// Timer0 16 Bit Register
#define Timer0_16_Bit_Register() (T0CONbits.T08BIT = 0)

// Enable Prescaler Feature
#define Enable_Prescaler_Feature()  (T0CONbits.PSA = 0)
// Disable Prescaler Feature
#define Disable_Prescaler_Feature() (T0CONbits.PSA = 1)

// Set Prescaler Value
#define Set_Prescaler_value(value) (T0CONbits.T0PS = value)

// Timer0 Counter Rising Edge
#define Timer0_Counter_Rising_Edge()  (T0CONbits.T0SE = 0)
// Timer0 Counter Fallig Edge
#define Timer0_Counter_Fallig_Edge()  (T0CONbits.T0SE = 1)



/*----------------User_defined_data_types----------------*/

typedef enum{
    Presclaer_value_Dive_2,
    Presclaer_value_Dive_4,
    Presclaer_value_Dive_8,
    Presclaer_value_Dive_16,
    Presclaer_value_Dive_32,
    Presclaer_value_Dive_64,
    Presclaer_value_Dive_128,
    Presclaer_value_Dive_256
}Prescaler_value_t;

typedef enum{
    Presclaer_Feature_Disable,
    Presclaer_Feature_Enable        
}Prescaler_Feature_t;

typedef enum{
    Timer_Mode,
    Counter_Mode        
}Timer0_Mode_t;

typedef enum{
    Timer0_8_Bit_Mode,
    Timer0_16_Bit_Mode        
}Timer0_Register_size_t;

typedef enum{
    Falling_Edge,
    Rising_Edge        
}Timer0_Counter_Edge_t;

typedef struct{
#if (Interrupt_Feature_Enable == 1)
    void (* Timer0_Interrupt_Handler)(void);
#endif
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
Prescaler_Feature_t Prescaler_Select;
Prescaler_value_t Prescaler_value;
Timer0_Mode_t Timer_Mode;
Timer0_Counter_Edge_t Counter_Edge;
Timer0_Register_size_t Register_Size; 
uint16 Preaload_value;    
}Timer0_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t Timer0_Init(Timer0_t *Timer);
STD_Return_t Timer0_DeInit(Timer0_t *Timer);
STD_Return_t Timer0_Write_value(Timer0_t *Timer,uint16 value);
STD_Return_t Timer0_Read_value(Timer0_t *Timer,uint16 *value);
#endif	/* MCAL_TIMER0_H */

