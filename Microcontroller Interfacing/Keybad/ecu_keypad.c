/* 
 * File:   ecu_keypad.c
 * Author: Amr Ali
 *
 * Created on March 16, 2024, 11:26 PM
 */
#include "ecu_keypad.h"
/* keypad button values */
uint8 array[keypad_rows][keypad_columns] = {{7,8,9,'/'},{4,5,6,'*'},{1,2,3,'-'},{'z',0,'=','+'}};
/**
 * @brief initialize keypad pins
 * @param reference to Keypad configuration @ref keypad_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Keypad_initialize(keypad_t *Keypad)
{
STD_Return_t ret = R_NOK;
uint8 i = 0;
if(NULL == Keypad)
{
ret = R_NOK;    
}
else
{
for(i=0;i<keypad_columns;i++)
{
ret = pin_initialize(&(Keypad->keypad_columns_pins[i]));    
}   
for(i=0;i<keypad_rows;i++)
{
ret = pin_initialize(&(Keypad->keypad_rows_pins[i]));    
}
ret = R_OK;    
}
return ret;
}     
/**
 * @brief read keypad value
 * @param reference to Keypad configuration @ref keypad_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Get_Keypad_value(keypad_t *Keypad,uint8 *value)
{
STD_Return_t ret = R_NOK;
uint8 i = 0 , j = 0,k=0;
uint8 state = 0;
if(NULL == Keypad)
{
ret = R_NOK;    
}
else
{
for(i=0;i<keypad_rows;i++)  
{
for(k=0;k<keypad_rows;k++)  
{
ret = pin_write_logic(&(Keypad->keypad_rows_pins[k]),Low);   
}
ret = pin_write_logic(&(Keypad->keypad_rows_pins[i]),High);    
for(j=0;j<keypad_columns;j++)  
{
ret = get_pin_logic(&(Keypad->keypad_columns_pins[j]),&state);  
if(High == state)
{
*value = array[i][j];   
}
else{/*Nothing*/}
} 
}
ret = R_OK;    
}
return ret;    
}