/* 
 * File:   ecu_relay.h
 * Author: Amr Ali
 *
 * Created on March 16, 2024, 3:38 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*----------------Includes----------------*/
#include "../../MCAL/GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
/*----------------Macros----------------*/

/*----------------Macro_Functions----------------*/

/*----------------User_defined_data_types----------------*/


typedef enum{
    Relay_Activated,
    Relay_Deactivated
}Relay_status_t;

typedef struct{
    uint8 Relay_status_t  :1;
    Pin_Cofnig_t Relay_Pin;  
}Relay_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t Relay_initialize(Relay_t *Relay);
STD_Return_t Relay_Turn_on(Relay_t *Relay);
STD_Return_t Relay_Turn_off(Relay_t *Relay);



#endif	/* ECU_RELAY_H */

