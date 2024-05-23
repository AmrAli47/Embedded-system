/* 
 * File:   mcal_timer3.h
 * Author: Amr Ali
 *
 * Created on March 24, 2024, 10:51 PM
 */

#ifndef MCAL_TIMER3_H
#define	MCAL_TIMER3_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/Interal_Interrupts/mcal_internal_interrupt.h"

/*----------------Macros----------------*/


/*----------------Macro_Functions----------------*/
// Timer3_Module_Enable
#define Timer3_Module_Enable()   (T3CONbits.TMR3ON = 1)
// Timer3_Module_Enable
#define Timer3_Module_Disable()  (T3CONbits.TMR3ON = 0)

// Timer3 Timer Mode
#define Timer3_Timer_Mode()  (T3CONbits.TMR3CS = 0)
// Timer3 Counter Mode
#define Timer3_Counter_Mode() (T3CONbits.TMR3CS = 1)

// Timer3 8 Bit Register
#define Timer3_8_Bit_Register()   (T3CONbits.RD16 = 0)
// Timer3 16 Bit Register
#define Timer3_16_Bit_Register() (T3CONbits.RD16 = 1)

// Set Prescaler Value
#define Set_Prescaler_value(value) (T3CONbits.T3CKPS = value)


// Timer3_oscillator_Enable
#define Timer3_Synchronous_Counter()   (T3CONbits.NOT_T3SYNC = 0)
// Timer3_oscillator_Enable
#define Timer3_Asynchronous_Counter()  (T3CONbits.NOT_T3SYNC = 1)




/*----------------User_defined_data_types----------------*/

typedef enum{
    Timer3_Presclaer_value_Div_1,
    Timer3_Presclaer_value_Div_2,
    Timer3_Presclaer_value_Div_4,
    Timer3_Presclaer_value_Div_8
}Timer3_Prescaler_value_t;


typedef enum{
    Timer3_as_a_Timer,
    Timer3_as_a_Counter        
}Timer3_Mode_t;

typedef enum{
    Timer3_8_Bit_Mode,
    Timer3_16_Bit_Mode        
}Timer3_Register_size_t;


typedef enum{
    Timer3_Counter_Synchronous,
    Timer3_Counter_Asynchronous        
}Timer3_Counter_Mode_Type_t;


typedef struct{
#if (Interrupt_Feature_Enable == 1)
    void (* Timer3_Interrupt_Handler)(void);
#endif
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
Timer3_Prescaler_value_t Prescaler_value;
Timer3_Mode_t Timer_Mode;
Timer3_Register_size_t Register_Size; 
Timer3_Counter_Mode_Type_t Counter_Mode;
uint16 Preaload_value;    
}Timer3_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t Timer3_Init(Timer3_t *Timer);
STD_Return_t Timer3_DeInit(Timer3_t *Timer);
STD_Return_t Timer3_Write_value(Timer3_t *Timer,uint16 value);
STD_Return_t Timer3_Read_value(Timer3_t *Timer,uint16 *value);

#endif	/* MCAL_TIMER3_H */

