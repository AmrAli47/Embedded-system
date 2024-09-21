/* 
 * File:   mcal_gpio.h
 * Author: Amr Ali
 *
 * Created on March 14, 2024, 8:07 PM
 */
 
#ifndef MCAL_GPIO_H
#define	MCAL_GPIO_H

/*----------------Includes----------------*/
#include "../proc/pic18f4620.h"
#include "../../device_config.h"

/*----------------Macros----------------*/
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
#define BIT_MASK (uint8)1
#define PORT_MASK 0XFF
/*----------------Macro_Functions----------------*/
#define SET_BIT(REG,BIT_POS)    (REG |= (BIT_MASK<<BIT_POS))
#define CLEAR_BIT(REG,BIT_POS)  (REG &= ~(BIT_MASK<<BIT_POS))
#define TOGGLE_BIT(REG,BIT_POS) (REG ^= (BIT_MASK<<BIT_POS))
#define READ_BIT(REG,BIT_POS)   (BIT_MASK & (REG>>BIT_POS))

/*----------------User_defined_data_types----------------*/
typedef enum{
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7  
}Pin_Number_t;

typedef enum{
    Port_A,
    Port_B,
    Port_C,
    Port_D,
    Port_E
}Port_Number_t;

typedef enum{
    Output,
    Input
}Direction_t;

typedef enum{
    Low,
    High
}logic_t;

typedef enum{
    R_NOK,
    R_OK
}STD_Return_t;

typedef struct{
    uint8 Port_Number :3; // @ref Port_Number_t
    uint8 Pin_Number  :3; // @ref Pin_Number_t
    uint8 direction   :1; // @ref Direction_t
    uint8 logic       :1; // @ref logic_t
}Pin_Cofnig_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t pin_direction_initialize(Pin_Cofnig_t *pin_config);
STD_Return_t get_pin_direction_initialize(Pin_Cofnig_t *pin_config,Direction_t *direction_status);
STD_Return_t pin_write_logic(Pin_Cofnig_t *pin_config,logic_t logic);
STD_Return_t get_pin_logic(Pin_Cofnig_t *pin_config,logic_t *logic_status);
STD_Return_t pin_toggle_logic(Pin_Cofnig_t *pin_config);
STD_Return_t pin_initialize(Pin_Cofnig_t *pin_config);


STD_Return_t port_direction_initialize(Port_Number_t port,uint8 direction);
STD_Return_t get_port_direction(Port_Number_t port,uint8 *direction);
STD_Return_t port_write_logic(Port_Number_t port,uint8 logic);
STD_Return_t get_port_logic(Port_Number_t port,uint8 *logic);
STD_Return_t port_toggle_logic(Port_Number_t port);

#endif	/* MCAL_GPIO_H */

