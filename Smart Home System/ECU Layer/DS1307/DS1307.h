/* 
 * File:   DS1307.h
 * Author: Kimo Store
 *
 * Created on April 3, 2024, 5:16 PM
 */

#ifndef DS1307_H
#define	DS1307_H


/*user defined data types*/

typedef struct{
uint8_t Seconds;    
uint8_t minutes;
uint8_t hours;
uint8_t days;
uint8_t months;
uint8_t years;   
}DS1307_t;


/*Software Interfaces*/
uint8_t  I2C_D1307_Read_Values(uint8_t address, uint8_t reg);


#endif	/* DS1307_H */

