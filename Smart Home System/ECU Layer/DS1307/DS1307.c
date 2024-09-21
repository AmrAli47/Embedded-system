/* 
 * File:   DS1307.h
 * Author: Kimo Store
 *
 * Created on April 3, 2024, 5:16 PM
 */

#include "../../mcc_generated_files/examples/i2c_master_example.h"



static i2c_operations_t rd1RegCompleteHandler(void *ptr);


uint8_t  I2C_D1307_Read_Values(uint8_t address, uint8_t reg)
{
    uint8_t returnValue = 0x00;
    
    while(!I2C_Open(address)); // sit here until we get the bus..
    I2C_SetDataCompleteCallback(rd1RegCompleteHandler,&returnValue);
    I2C_SetBuffer(&reg,1);
    I2C_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C_MasterWrite();
    while(I2C_BUSY == I2C_Close()); // sit here until finished.
    
    return returnValue;    
}



static i2c_operations_t rd1RegCompleteHandler(void *ptr)
{
    I2C_SetBuffer(ptr,1);
    I2C_SetDataCompleteCallback(NULL,NULL);
    return I2C_RESTART_READ;
}