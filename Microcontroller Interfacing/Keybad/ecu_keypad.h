/* 
 * File:   ecu_keypad.h
 * Author: Amr Ali
 *
 * Created on March 16, 2024, 11:26 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*----------------Includes----------------*/
#include "../../MCAL/GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
/*----------------Macros----------------*/

/*----------------Macro_Functions----------------*/
#define keypad_columns 4
#define keypad_rows 4
/*----------------User_defined_data_types----------------*/
typedef struct{
    Pin_Cofnig_t keypad_rows_pins[keypad_rows];
    Pin_Cofnig_t keypad_columns_pins[keypad_columns]; 
}keypad_t;


/*----------------Software_Interfaces----------------*/
STD_Return_t Keypad_initialize(keypad_t *Keypad);
STD_Return_t Get_Keypad_value(keypad_t *Keypad,uint8 *value);


#endif	/* ECU_KEYPAD_H */

