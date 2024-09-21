/* 
 * File:   ecu_motor.c
 * Author: Amr Ali
 *
 * Created on March 16, 2024, 3:39 PM
 */
#include "ecu_motor.h"
/**
 * @brief initialize motor pins
 * @param reference to motor configurations @ref Motor_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t motor_initialize(Motor_t *Motor)
{
STD_Return_t ret = R_NOK;
if(NULL == Motor)   
{
ret = R_NOK;    
}
else
{
ret = pin_initialize(&(Motor->Motor_Pin[0]));
ret = pin_initialize(&(Motor->Motor_Pin[1]));
ret = R_OK;    
}
return ret;
}     

/**
 * @brief move motor in right direction
 * @param reference to motor configurations @ref Motor_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t motor_move_right(Motor_t *Motor)
{
STD_Return_t ret = R_NOK;
if(NULL == Motor)   
{
ret = R_NOK;    
}
else
{
ret = pin_write_logic(&(Motor->Motor_Pin[0]),High);
ret = pin_write_logic(&(Motor->Motor_Pin[1]),Low);
ret = R_OK;    
}
return ret;    
}      

/**
 * @brief move motor in left direction
 * @param reference to motor configurations @ref Motor_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t motor_move_left(Motor_t *Motor)
{
STD_Return_t ret = R_NOK;
if(NULL == Motor)   
{
ret = R_NOK;    
}
else
{
ret = pin_write_logic(&(Motor->Motor_Pin[0]),Low);
ret = pin_write_logic(&(Motor->Motor_Pin[1]),High);
ret = R_OK;    
}
return ret;    
} 
/**
 * @brief stop motor
 * @param reference to motor configurations @ref Motor_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t motor_stop(Motor_t *Motor)
{
STD_Return_t ret = R_NOK;
if(NULL == Motor)   
{
ret = R_NOK;    
}
else
{
ret = pin_write_logic(&(Motor->Motor_Pin[0]),Low);
ret = pin_write_logic(&(Motor->Motor_Pin[1]),Low);
ret = R_OK;    
}
return ret;    
} 