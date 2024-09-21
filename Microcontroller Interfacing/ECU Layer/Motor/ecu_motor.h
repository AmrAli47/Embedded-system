/* 
 * File:   ecu_motor.h
 * Author: Amr Ali
 *
 * Created on March 16, 2024, 3:39 PM
 */

#ifndef ECU_MOTOR_H
#define	ECU_MOTOR_H

/*----------------Includes----------------*/
#include "../../MCAL/GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"

/*----------------Macros----------------*/

/*----------------Macro_Functions----------------*/

/*----------------User_defined_data_types----------------*/

typedef struct{
    Pin_Cofnig_t Motor_Pin[2];
}Motor_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t motor_initialize(Motor_t *Motor);
STD_Return_t motor_move_right(Motor_t *Motor);
STD_Return_t motor_move_left(Motor_t *Motor);
STD_Return_t motor_stop(Motor_t *Motor);

#endif	/* ECU_MOTOR_H */

