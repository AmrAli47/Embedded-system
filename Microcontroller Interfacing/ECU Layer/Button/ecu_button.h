/* 
 * File:   ecu_button.h
 * Author: Amr Ali
 *
 * Created on March 16, 2024, 1:19 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*----------------Includes----------------*/
#include "../../MCAL/GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
/*----------------Macros----------------*/

/*----------------Macro_Functions----------------*/

/*----------------User_defined_data_types----------------*/
typedef enum{
    Active_Low,
    Active_High
}Button_Active_t;

typedef enum{
    Button_Released,
    Button_Pressed
}Button_status_t;

typedef struct{
    uint8 Button_Active_t :1;
    uint8 Button_status_t :1;
    Pin_Cofnig_t Button_Pin;  
}Button_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t Button_initialize(Button_t *Button);
STD_Return_t get_Button_status(Button_t *Button,Button_status_t *Button_status);




#endif	/* ECU_BUTTON_H */

