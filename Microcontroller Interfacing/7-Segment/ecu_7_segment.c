/* 
 * File:   ecu_7_segment.c
 * Author: Amr Ali
 * 
 * Created on March 16, 2024, 5:55 PM
 */

#include "ecu_7_segment.h"
/**
 * @brief initialize segment pins
 * @param reference to segment configurations @ref segment_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t segment_initialize(segment_t *segment)
{
STD_Return_t ret = R_NOK;
uint8 i = 0;
if(NULL == segment)
{
ret = R_NOK;
}
else
{
for(i=0;i<4;i++)
{
ret = pin_direction_initialize(&(segment->segment_pins[i]));
}
ret = R_OK;    
}
return ret;
}
/**
 * @brief display number on the segment
 * @param reference to segment configurations @ref segment_t
 * @param Number
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t segment_write_number(segment_t *segment,uint8 Number)
{
STD_Return_t ret = R_NOK;
uint8 Mask = 0x01;
uint8 i = 0;
if(NULL == segment)
{
ret = R_NOK;
}
else
{
for(i=0;i<4;i++)
{
ret = pin_write_logic(&(segment->segment_pins[i]),(Number>>i) & Mask);
}    
ret = R_OK;    
}
return ret;    
}
