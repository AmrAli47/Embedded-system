/* 
 * File:   mcal_external_interrupt_config.h
 * Author: Amr Ali
 *
 * Created on March 18, 2024, 6:00 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_CONFIG_H
#define	MCAL_EXTERNAL_INTERRUPT_CONFIG_H 

/*----------------Includes----------------*/
#include "../../device_config.h"
#include "../../compiler.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../GPIO/mcal_gpio.h"

/*----------------Macros----------------*/
#define Interrupt_Priority_Enable 0
#define Interrupt_Feature_Enable  1
/*----------------Macro_Functions----------------*/

#if (Interrupt_Feature_Enable == 1)
// Enable All Global Interrupts
#define Global_Interrupt_Enable()      (INTCONbits.GIE=1)
//Enable All Peripheral Interrupts
#define Peripheral_Interrupt_Enable()  (INTCONbits.PEIE=1) 


// Disable All Global Interrupts
#define Global_Interrupt_Disable()      (INTCONbits.GIE=0)
//Disable All Peripheral Interrupts
#define Peripheral_Interrupt_Disable()  (INTCONbits.PEIE=0) 

#endif

#if (Interrupt_Priority_Enable == 1)
//Enable Priority Feature
#define Priority_Feature_Enable()                    (RCONbits.IPEN=1)
// Enable All High Priority Interrupts
#define Global_High_Priority_Interrupt_Enable()      (INTCONbits.GIEH=1)
//Enable All Low Priority Interrupts
#define Global_Low_Priority_Interrupt_Enable()      (INTCONbits.GIEL=1) 

#else
//Disable Priority Feature
#define Priority_Feature_Disable()                    (RCONbits.IPEN=0)
// Disable All High Priority Interrupts
#define Global_High_Priority_Interrupt_Disable()      (INTCONbits.GIEH=0)
//Disable All Low Priority Interrupts
#define Global_Low_Priority_Interrupt_Disable()      (INTCONbits.GIEL=0) 

#endif

/*----------------User_defined_data_types----------------*/
typedef enum{
    Low_Priority,
    High_Piority
}Interrupt_Priority_CFG;

typedef enum{
    Interrupt_Not_occur,
    Interrupt_occur
}Interrupt_occur_t;

typedef enum{
    Interrupt_Disable,
    Interrupt_Enable
}Interrupt;



/*----------------Software_Interfaces----------------*/

#endif	/* MCAL_EXTERNAL_INTERRUPT_CONFIG_H */

