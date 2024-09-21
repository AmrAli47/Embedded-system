/* 
 * File:   TC47.h
 * Author: Kimo Store
 *
 * Created on April 3, 2024, 7:20 PM
 */

#ifndef TC47_H
#define	TC47_H

typedef unsigned char uint8_t;


/*Software Interfaces*/
uint8_t  I2C_Read_Temp_Value(uint8_t device_address, uint8_t register_address);

#endif	/* TC47_H */

