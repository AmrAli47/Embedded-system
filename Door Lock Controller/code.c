/* 
 * File:   Application.c
 * Author: Amr Ali
 *
 * Created on March 22, 2024, 12:33 AM
 */

#include "Application.h"
STD_Return_t ret = R_NOK;
LCD_4_BIT_t LCD = {
.RS_Pin.Port_Number = Port_C,.RS_Pin.Pin_Number = Pin0,.RS_Pin.direction = Output,.RS_Pin.logic = Low,  
.EN_Pin.Port_Number = Port_C,.EN_Pin.Pin_Number = Pin1,.EN_Pin.direction = Output,.EN_Pin.logic = Low,  
.LCD_Pins[0].Port_Number = Port_C,.LCD_Pins[0].Pin_Number = Pin2,.LCD_Pins[0].direction = Output,.LCD_Pins[0].logic = Low,  
.LCD_Pins[1].Port_Number = Port_C,.LCD_Pins[1].Pin_Number = Pin3,.LCD_Pins[1].direction = Output,.LCD_Pins[1].logic = Low,  
.LCD_Pins[2].Port_Number = Port_C,.LCD_Pins[2].Pin_Number = Pin4,.LCD_Pins[2].direction = Output,.LCD_Pins[2].logic = Low,  
.LCD_Pins[3].Port_Number = Port_C,.LCD_Pins[3].Pin_Number = Pin5,.LCD_Pins[3].direction = Output,.LCD_Pins[3].logic = Low  };
keypad_t Keypad = {
.keypad_rows_pins[0].Port_Number = Port_C,.keypad_rows_pins[0].Pin_Number = Pin6,.keypad_rows_pins[0].direction = Output,.keypad_rows_pins[0].logic = Low,  
.keypad_rows_pins[1].Port_Number = Port_C,.keypad_rows_pins[1].Pin_Number = Pin7,.keypad_rows_pins[1].direction = Output,.keypad_rows_pins[1].logic = Low,
.keypad_rows_pins[2].Port_Number = Port_D,.keypad_rows_pins[2].Pin_Number = Pin0,.keypad_rows_pins[2].direction = Output,.keypad_rows_pins[2].logic = Low,
.keypad_rows_pins[3].Port_Number = Port_D,.keypad_rows_pins[3].Pin_Number = Pin1,.keypad_rows_pins[3].direction = Output,.keypad_rows_pins[3].logic = Low,
.keypad_columns_pins[0].Port_Number = Port_D,.keypad_columns_pins[0].Pin_Number = Pin2,.keypad_columns_pins[0].direction = Input,.keypad_columns_pins[0].logic = Low,
.keypad_columns_pins[1].Port_Number = Port_D,.keypad_columns_pins[1].Pin_Number = Pin3,.keypad_columns_pins[1].direction = Input,.keypad_columns_pins[1].logic = Low,
.keypad_columns_pins[2].Port_Number = Port_D,.keypad_columns_pins[2].Pin_Number = Pin4,.keypad_columns_pins[2].direction = Input,.keypad_columns_pins[2].logic = Low,
.keypad_columns_pins[3].Port_Number = Port_D,.keypad_columns_pins[3].Pin_Number = Pin5,.keypad_columns_pins[3].direction = Input,.keypad_columns_pins[3].logic = Low,
};
Motor_t Motor = {
.Motor_Pin[0].Port_Number = Port_D,.Motor_Pin[0].Pin_Number = Pin6,.Motor_Pin[0].direction = Output,.Motor_Pin[0].logic = Low,
.Motor_Pin[1].Port_Number = Port_D,.Motor_Pin[1].Pin_Number = Pin7,.Motor_Pin[1].direction = Output,.Motor_Pin[1].logic = Low,
};
int real_password[4] = {2,4,6,8};
int input_password[4] = {0};
int values[9] = {1,2,3,4,5,6,7,8,9};
int not_equal = 0;
int value = 50;
int i,j,u = 0;
int n = 1;
int k = 7;
int main() {
ret = Keypad_initialize(&Keypad);
ret |= LCD_4_Bit_initialization(&LCD);
ret |= LCD_4_Bit_Send_String_Pos(&LCD,"Enter The Password",1,1);
ret |= motor_initialize(&Motor);
while(1)
{
while(i < 4)
{
ret |= Get_Keypad_value(&Keypad,&value);  
for(u=0;u<9;u++)
{
if(value == values[u]) 
{
input_password[i] = value;
ret |= LCD_4_Bit_Send_String_Pos(&LCD,"*",2,k); 
__delay_ms(250);
i++;
k++;
value = 50;
}
else
{
continue;
}
}
u = 0;
}
ret |= Get_Keypad_value(&Keypad,&value);  
if(value == '=')
{
for(j=0;j<4;j++)
{
if(real_password[j] == input_password[j])
{
continue;   
}
else
{
not_equal++;
}
} 
if(not_equal !=0)
{
ret |= LCD_4_Bit_Send_Command(&LCD,Display_Clear);
ret |= LCD_4_Bit_Send_String_Pos(&LCD,"wrong password",1,6);
ret |= LCD_4_Bit_Send_String_Pos(&LCD,"try again",2,6);
not_equal = 0;
i = 0;
__delay_ms(1000);
ret |= LCD_4_Bit_Send_Command(&LCD,Display_Clear);
ret |= LCD_4_Bit_Send_String_Pos(&LCD,"Enter The Password",1,1);
k = 7;
} 
else if(not_equal == 0)
{
if(n == 1)
{
ret |= LCD_4_Bit_Send_Command(&LCD,Display_Clear);   
ret |= LCD_4_Bit_Send_String_Pos(&LCD,"correct password",1,3);
ret |= motor_move_right(&Motor);
n = 0;
}
}
}
}
}

