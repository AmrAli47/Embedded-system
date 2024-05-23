/* 
 * File:   ecu_led.h
 * Author: Amr Ali
 *
 * Created on March 14, 2024, 8:06 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*----------------Includes----------------*/
#include "../../MCAL/GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
/*----------------Macros----------------*/

/*----------------Macro_Functions----------------*/
#define LED_ON  (uint8)1
#define LED_OFF (uint8)0
/*----------------User_defined_data_types----------------*/
typedef enum{
    Led_ON,
    Led_OFF
}Led_state_t;

typedef struct{
    uint8 Led_state :1; //@ref Led_state_t
    Pin_Cofnig_t Led_Pin;
}Led_t;


/*----------------Software_Interfaces----------------*/
STD_Return_t Led_initialize(Led_t *Led);
STD_Return_t Led_Turn_on(Led_t *Led);
STD_Return_t Led_Turn_off(Led_t *Led);
STD_Return_t Led_Toggle(Led_t *Led);



#endif	/* ECU_LED_H */

