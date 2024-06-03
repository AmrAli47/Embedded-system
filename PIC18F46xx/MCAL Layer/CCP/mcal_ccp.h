/* 
 * File:   mcal_ccp.h
 * Author: Amr Ali
 *
 * Created on March 25, 2024, 1:02 AM
 */
 
#ifndef MCAL_CCP_H
#define	MCAL_CCP_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/Interal_Interrupts/mcal_internal_interrupt.h"
#include "mcal_ccp_gen_cfg.h"
/*----------------Macros----------------*/

/*----------------Macro_Functions----------------*/
#define Set_CCP_Module_Mode(config) (CCP1CONbits.CCP1M = config)

#define Set_CCP2_Module_Mode(config) (CCP2CONbits.CCP2M = config)
// Note : Timers should not work in asynchronous counter mode

#define Set_Timer1_Clock_Source_for_Capture_Compare_Modes_CCP_Modules() do{T3CONbits.T3CCP1 = 0;\
                                                                           T3CONbits.T3CCP2 = 0;\
                                                                           }while(0)

#define Set_Timer1_Clock_Source_for_Capture_Compare_Modes_CCP1_Module() do{T3CONbits.T3CCP1 = 1;\
                                                                           T3CONbits.T3CCP2 = 0;\
                                                                           }while(0)

#define Set_Timer3_Clock_Source_for_Capture_Compare_Modes_CCP2_Module() do{T3CONbits.T3CCP1 = 1;\
                                                                           T3CONbits.T3CCP2 = 0;\
                                                                           }while(0)

#define Set_Timer3_Clock_Source_for_Capture_Compare_Modes_CCP_Modules() do{T3CONbits.T3CCP1 = 1;\
                                                                           T3CONbits.T3CCP2 = 1;\
                                                                           }while(0)

/*----------------User_defined_data_types----------------*/

typedef enum{
    Timer1_Capture,
    Timer3_Capture
}Capture_Mode_Timer_t;

typedef enum{
    Timer1_Compare,
    Timer3_Compare
}Compare_Mode_Timer_t;

typedef enum{
CCP_Module_Disable = 0,
CCP_Compare_Mode_Toggle_Bit_on_Match = 2,
CCP_Capture_Mode_every_falling_Edge = 4,
CCP_Capture_Mode_every_Rising_Edge = 5,
CCP_Capture_Mode_every_Four_Rising_Edge = 6,
CCP_Capture_Mode_every_sixteen_Rising_Edge = 7,
CCP_Compare_force_pin_to_be_high_on_match = 8,
CCP_Compare_force_pin_to_be_low_on_match = 9,
CCP_Compare_generate_interrupt_CCP_Pin_same_state = 10,
CCP_Compare_trigger_special_event = 11,
CCP_PWM_Mode = 15   
}CCP_Mode_t;


typedef struct{
    void (* Interrupt_Handler_Capture)(void);
    Capture_Mode_Timer_t Timer_Resource;  
    CCP_Mode_t Mode; 
    Pin_Cofnig_t CCP_Pin;
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
}Capture_Mode_t;

typedef struct{
    void (* Interrupt_Handler_Compare)(void);
    Compare_Mode_Timer_t Timer_Resource;  
    CCP_Mode_t Mode; 
    Pin_Cofnig_t CCP_Pin;
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
}Compare_Mode_t;


typedef struct{
    void (* Interrupt_Handler_PWM1)(void);
    CCP_Mode_t Mode; 
    Pin_Cofnig_t CCP_Pin;
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
}PWM1_Mode_t;

typedef struct{
    void (* Interrupt_Handler_PWM2)(void);
    CCP_Mode_t Mode; 
    Pin_Cofnig_t CCP_Pin;
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
}PWM2_Mode_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t CCP_Module_Interrupt_Init(void);
#if (CCP_Module_Works_in == Capture_Mode)
STD_Return_t Capture_Mode_Init(Capture_Mode_t *Capture);
STD_Return_t Capture_Mode_DeInit(Capture_Mode_t *Capture);
STD_Return_t Capture_Mode_Read_value(uint16 *value);

#endif

#if (CCP_Module_Works_in == Compare_Mode)
STD_Return_t Compare_Mode_Init(Compare_Mode_t *Compare);
STD_Return_t Compare_Mode_DeInit(Compare_Mode_t *Compare);
STD_Return_t Compare_Mode_write_value(uint16 value);
#endif

#if (CCP_Module_Works_in == PWM_Mode)
STD_Return_t PWM1_Mode_Init(PWM1_Mode_t *PWM1);
STD_Return_t PWM2_Mode_Init(PWM2_Mode_t *PWM2);
STD_Return_t PWM1_Mode_DeInit(PWM1_Mode_t *PWM1);
STD_Return_t PWM1_Mode_write_Frequency(uint16 value);
STD_Return_t PWM1_Mode_write_Duty_Cycle(uint16 value);
STD_Return_t PWM2_Mode_write_Duty_Cycle(uint16 value);
#endif




#endif	/* MCAL_CCP_H */

