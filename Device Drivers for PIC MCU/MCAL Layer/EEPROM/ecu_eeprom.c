/* 
 * File:   ecu_eeprom.c
 * Author: Amr Ali
 *
 * Created on March 20, 2024, 7:42 PM
 */

#include "ecu_eeprom.h"  
/**
 * @brief write data to EEPROM
 * @param location where data will be written in it
 * @param Data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EEPROM_Write_data(uint16 Address,uint8 Data)
{
STD_Return_t ret = R_OK;    
uint8 interrupt_status = 0;
EEADRH = (uint8)((Address>>8)&(0x03));
EEADR = (uint8)((Address)&(0xFF));
EEDATA = Data;
Access_EEPROM_Memory();
Access_Flash_or_EEPROM();
Allow_Write_to_Memory();
Global_Interrupt_Disable();
interrupt_status = INTCONbits.GIE;
EECON2 = 0x55;
EECON2 = 0XAA;
Initiate_Write_to_Memory();
while(EECON1bits.WRERR);
INTCONbits.GIE = interrupt_status;
Inhibit_Write_to_Memory();
return ret ;
}
/**
 * @brief read data from EEPROM
 * @param location where data will be written in it
 * @param Data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t EEPROM_Read_data(uint16 Address,uint8 *Data)
{
STD_Return_t ret = R_NOK;
if(NULL == Data)
{
ret = R_NOK;
}
else
{
EEADRH = (uint8)((Address>>8)&(0x03));
EEADR = (uint8)((Address)&(0xFF));    
Access_EEPROM_Memory();
Access_Flash_or_EEPROM();
Initiate_Read_to_Memory();
*Data = EEDATA;
ret = R_OK;
}
return ret;
}
