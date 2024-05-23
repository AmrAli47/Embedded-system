/* 
 * File:   mcal_timer1.h
 * Author: Amr Ali
 *
 * Created on March 24, 2024, 5:56 AM
 */

#ifndef MCAL_TIMER1_H
#define	MCAL_TIMER1_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/Interal_Interrupts/mcal_internal_interrupt.h"

/*----------------Macros----------------*/


/*----------------Macro_Functions----------------*/
// Timer1_Module_Enable
#define Timer1_Module_Enable()   (T1CONbits.TMR1ON = 1)
// Timer1_Module_Enable
#define Timer1_Module_Disable()  (T1CONbits.TMR1ON = 0)

// Timer1 Timer Mode
#define Timer1_Timer_Mode()  (T1CONbits.TMR1CS = 0)
// Timer1 Counter Mode
#define Timer1_Counter_Mode() (T1CONbits.TMR1CS = 1)

// Timer0 8 Bit Register
#define Timer1_8_Bit_Register()   (T1CONbits.RD16 = 0)
// Timer0 16 Bit Register
#define Timer1_16_Bit_Register() (T1CONbits.RD16 = 1)

// Set Prescaler Value
#define Set_Prescaler_value(value) (T1CONbits.T1CKPS = value)

// which oscillator does Timer 1 run from it
#define Timer1_oscillaotr() (T1CONbits.T1RUN)

// Timer1_oscillator_Enable
#define Enable_Timer1_oscillator()   (T1CONbits.T1OSCEN = 1)
// Timer1_oscillator_Enable
#define Disable_Timer1_oscillator()  (T1CONbits.T1OSCEN = 0)

// Timer1_oscillator_Enable
#define Timer1_Synchronous_Counter()   (T1CONbits.NOT_T1SYNC = 0)
// Timer1_oscillator_Enable
#define Timer1_Asynchronous_Counter()  (T1CONbits.NOT_T1SYNC = 1)




/*----------------User_defined_data_types----------------*/

typedef enum{
    Presclaer_value_Div_1,
    Presclaer_value_Div_2,
    Presclaer_value_Div_4,
    Presclaer_value_Div_8
}Timer1_Prescaler_value_t;


typedef enum{
    Timer1_as_a_Timer,
    Timer1_as_a_Counter        
}Timer1_Mode_t;

typedef enum{
    Timer1_8_Bit_Mode,
    Timer1_16_Bit_Mode        
}Timer1_Register_size_t;

typedef enum{
    Timer1_oscillator_Enable,
    Timer1_oscillator_Disable        
}Timer1_oscillator_t;

typedef enum{
    Counter_Synchronous,
    Counter_Asynchronous        
}Timer1_Counter_Mode_Type_t;


typedef struct{
#if (Interrupt_Feature_Enable == 1)
    void (* Timer1_Interrupt_Handler)(void);
#endif
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
Timer1_Prescaler_value_t Prescaler_value;
Timer1_Mode_t Timer_Mode;
Timer1_Register_size_t Register_Size; 
Timer1_oscillator_t Timer1_oscillaotr;
Timer1_Counter_Mode_Type_t Counter_Mode;
uint16 Preaload_value;    
}Timer1_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t Timer1_Init(Timer1_t *Timer);
STD_Return_t Timer1_DeInit(Timer1_t *Timer);
STD_Return_t Timer1_Write_value(Timer1_t *Timer,uint16 value);
STD_Return_t Timer1_Read_value(Timer1_t *Timer,uint16 *value);

#endif	/* MCAL_TIMER1_H */

