/* 
 * File:   ecu_7_segment.h
 * Author: Amr Ali
 *
 * Created on March 16, 2024, 5:55 PM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

/*----------------Includes----------------*/
#include "../../MCAL/GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
/*----------------Macros----------------*/

/*----------------Macro_Functions----------------*/

/*----------------User_defined_data_types----------------*/
typedef struct{
    Pin_Cofnig_t segment_pins[4];
}segment_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t segment_initialize(segment_t *segment);
STD_Return_t segment_write_number(segment_t *segment,uint8 Number);
#endif	/* ECU_7_SEGMENT_H */

