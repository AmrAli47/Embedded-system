/* 
 * File:   mcal_timer2.h
 * Author: Amr Ali
 *
 * Created on March 24, 2024, 10:49 PM
 */

#ifndef MCAL_TIMER2_H
#define	MCAL_TIMER2_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/Interal_Interrupts/mcal_internal_interrupt.h"

/*----------------Macros----------------*/


/*----------------Macro_Functions----------------*/
// Timer2_Module_Enable
#define Timer2_Module_Enable()   (T2CONbits.TMR2ON = 1)
// Timer2_Module_Enable
#define Timer2_Module_Disable()  (T2CONbits.TMR2ON = 0)

// Set Prescaler Value
#define Set_Prescaler_value(value) (T2CONbits.T2CKPS = value)


// Set Postscaler Value
#define Set_Postscaler_value(value) (T2CONbits.TOUTPS = value)


/*----------------User_defined_data_types----------------*/

typedef enum{
    Timer2_Presclaer_value_Div_1,
    Timer2_Presclaer_value_Div_4,
    Timer2_Presclaer_value_Div_16
}Timer2_Prescaler_value_t;

typedef enum{
    Postsclaer_value_Div_1,
    Postsclaer_value_Div_2,
    Postsclaer_value_Div_3,
    Postsclaer_value_Div_4,
    Postsclaer_value_Div_5,
    Postsclaer_value_Div_6,
    Postsclaer_value_Div_7,
    Postsclaer_value_Div_8,
    Postsclaer_value_Div_9,
    Postsclaer_value_Div_10,
    Postsclaer_value_Div_11,
    Postsclaer_value_Div_12,
    Postsclaer_value_Div_13,
    Postsclaer_value_Div_14,
    Postsclaer_value_Div_15,
    Postsclaer_value_Div_16        
}Timer2_Postscaler_value_t;


typedef struct{
#if (Interrupt_Feature_Enable == 1)
    void (* Timer2_Interrupt_Handler)(void);
#endif
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
Timer2_Prescaler_value_t Prescaler_value;
Timer2_Postscaler_value_t Postscaler_value; 
uint8 Preaload_value;    
}Timer2_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t Timer2_Init(Timer2_t *Timer);
STD_Return_t Timer2_DeInit(Timer2_t *Timer);
STD_Return_t Timer2_Write_value(Timer2_t *Timer,uint8 value);
STD_Return_t Timer2_Read_value(Timer2_t *Timer,uint8 *value);


#endif	/* MCAL_TIMER2_H */

