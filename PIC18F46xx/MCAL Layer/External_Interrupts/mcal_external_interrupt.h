/* 
 * File:   external_interrupt.h
 * Author: Amr Ali
 *
 * Created on March 18, 2024, 5:59 PM
 */

#ifndef EXTERNAL_INTERRUPT_H
#define	EXTERNAL_INTERRUPT_H

/*----------------Includes----------------*/
#include "../../device_config.h"
#include "../../compiler.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "mcal_external_interrupt_config.h"
#include "../GPIO/mcal_gpio.h"

/*----------------Macros----------------*/

/*----------------Macro_Functions----------------*/

/*--------------IN0--------------*/
//Enable External Interrupt IN0
#define INT0_Interrupt_Enable()  (INTCONbits.INT0IE = 1)
//Enable External Interrupt IN0
#define INT0_Interrupt_Disable()  (INTCONbits.INT0IE = 0)
//Set IN0 Flag
#define INT0_Set_Flag()          (INTCONbits.INT0IF = 1)
//Clear IN0 Flag
#define INT0_Clear_Flag()        (INTCONbits.INT0IF = 0)
//IN0 Rising Edge
#define INT0_Rising_Edge()       (INTCON2bits.INTEDG0 = 1)
//IN0 Falling Edge
#define INT0_Falling_Edge()      (INTCON2bits.INTEDG0 = 0)


/*--------------IN1--------------*/
//Enable External Interrupt IN1
#define INT1_Interrupt_Enable()  (INTCON3bits.INT1IE = 1)
//Disable External Interrupt IN1
#define INT1_Interrupt_Disable()  (INTCON3bits.INT1IE = 0)
//Set IN1 Flag
#define INT1_Set_Flag()          (INTCON3bits.INT1IF = 1)
//Clear IN1 Flag
#define INT1_Clear_Flag()        (INTCON3bits.INT1IF = 0)
//IN1 Rising Edge
#define INT1_Rising_Edge()       (INTCON2bits.INTEDG1 = 1)
//IN1 Falling Edge
#define INT1_Falling_Edge()      (INTCON2bits.INTEDG1 = 0)
//Set IN1 as High Priority
#define INT1_High_Priority()     (INTCON3bits.INT1IP = 1)
//Set IN1 as Low Priority
#define INT1_Low_Priority()      (INTCON3bits.INT1IP = 0)

/*--------------IN2--------------*/
//Enable External Interrupt IN2
#define INT2_Interrupt_Enable()  (INTCON3bits.INT2IE = 1)
//Disable External Interrupt IN2
#define INT2_Interrupt_Disable()  (INTCON3bits.INT2IE = 0)
//Set IN2 Flag
#define INT2_Set_Flag()          (INTCON3bits.INT2IF = 1)
//Clear IN2 Flag
#define INT2_Clear_Flag()        (INTCON3bits.INT2IF = 0)
//IN2_Rising Edge
#define INT2_Rising_Edge()       (INTCON2bits.INTEDG2 = 1)
//IN2 Falling Edge
#define INT2_Falling_Edge()      (INTCON2bits.INTEDG2 = 0)
//Set IN2 as High Priority
#define INT2_High_Priority()     (INTCON3bits.INT2IP = 1)
//Set IN2 as Low Priority
#define INT2_Low_Priority()      (INTCON3bits.INT2IP = 0)

/*--------------RBx--------------*/
//Enable External Interrupt RBx
#define RBx_Interrupt_Enable()  (INTCONbits.RBIE = 1)
//Disable External Interrupt IN2
#define RBx_Interrupt_Disable()  (INTCONbits.RBIE = 0)
//Set RBx Flag
#define RBx_Set_Flag()          (INTCONbits.RBIF = 1)
//Clear RBx Flag
#define RBx_Clear_Flag()        (INTCONbits.RBIF = 0)
//Set RBx as High Priority
#define RBx_High_Priority()     (INTCON2bits.RBIP = 1)
//Set RBx as Low Priority
#define RBx_Low_Priority()      (INTCON2bits.RBIP = 0)

/*----------------User_defined_data_types----------------*/
typedef enum{
Interrupt_INT0,
Interrupt_INT1,        
Interrupt_INT2    
}Interrupt_INTx_SRC;

typedef enum{
Falling_Edge_interrupt,
Rising_Edge_interrupt       
}Interrupt_INTx_Edge;



typedef struct{
    void (* Interrupt_Handler)(void);
    Interrupt_INTx_SRC     Source;
    #if (Interrupt_Priority_Enable == 1)
    Interrupt_Priority_CFG Priority;
    #endif
    Interrupt_INTx_Edge    Edge;
    Pin_Cofnig_t Interrupt_Pin;
}Interrupt_INTx_t;

typedef struct{
Pin_Cofnig_t Interrupt_Pin;
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
void (* Interrupt_Handler_High)(void);
void (* Interrupt_Handler_Low)(void);
}Interrupt_RBx_t;


/*----------------Software_Interfaces----------------*/
STD_Return_t interrupt_INTx_Init(Interrupt_INTx_t *INTx);
STD_Return_t interrupt_INTx_DeInit(Interrupt_INTx_t *INTx);
STD_Return_t interrupt_RBx_Init(Interrupt_RBx_t *RBx);
STD_Return_t interrupt_RBx_DeInit(Interrupt_RBx_t *RBx);
#endif	/* EXTERNAL_INTERRUPT_H */

