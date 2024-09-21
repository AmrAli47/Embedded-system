/* 
 * File:   eeprom.h
 * Author: Kimo Store
 *
 * Created on April 3, 2024, 7:38 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H


typedef unsigned char uint8_t;



/*Software Interfaces*/
void  I2C_Write_Byte_to_eeprom(uint8_t device_address, uint8_t Byte_address, uint8_t data);
uint8_t  I2C_Read_Byte_from_eeprom(uint8_t device_address, uint8_t Byte_address);



#endif	/* EEPROM_H */

