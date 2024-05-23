/* 
 * File:   ecu_eeprom.h
 * Author: Amr Ali
 *
 * Created on March 20, 2024, 7:42 PM
 */

#ifndef ECU_EEPROM_H
#define	ECU_EEPROM_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
/*----------------Macros----------------*/


/*----------------Macro_Functions----------------*/
#define Access_Configuration_Bits() (EECON1bits.CFGS = 1)
#define Access_Flash_or_EEPROM()    (EECON1bits.CFGS = 0)

#define Access_Flash_Memory()      (EECON1bits.EEPGD = 1)
#define Access_EEPROM_Memory()     (EECON1bits.EEPGD = 0)

#define Allow_Write_to_Memory()    (EECON1bits.WREN  = 1)
#define Inhibit_Write_to_Memory()  (EECON1bits.WREN  = 0)

#define Initiate_Write_to_Memory() (EECON1bits.WR = 1)

#define Initiate_Read_to_Memory() (EECON1bits.RD = 1)

/*----------------User_defined_data_types----------------*/


/*----------------Software_Interfaces----------------*/
STD_Return_t EEPROM_Write_data(uint16 Address,uint8 Data);
STD_Return_t EEPROM_Read_data(uint16 Address,uint8 *Data);


#endif	/* ECU_EEPROM_H */

