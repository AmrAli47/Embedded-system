/* 
 * File:   Application.c
 * Author: Amr Ali
 *
 * Created on March 22, 2024, 12:33 AM
 */

#include "Application.h"
void ADC_Get_Conversion_Value(void);

Motor_t First_Motor = {
.Motor_Pin[0].Port_Number = Port_C,.Motor_Pin[0].Pin_Number = Pin6,.Motor_Pin[0].direction = Output,.Motor_Pin[0].logic = Low,
.Motor_Pin[1].Port_Number = Port_C,.Motor_Pin[1].Pin_Number = Pin7,.Motor_Pin[1].direction = Output,.Motor_Pin[1].logic = Low};

Motor_t Second_Motor = {
.Motor_Pin[0].Port_Number = Port_D,.Motor_Pin[0].Pin_Number = Pin0,.Motor_Pin[0].direction = Output,.Motor_Pin[0].logic = Low,
.Motor_Pin[1].Port_Number = Port_D,.Motor_Pin[1].Pin_Number = Pin1,.Motor_Pin[1].direction = Output,.Motor_Pin[1].logic = Low};

LCD_4_BIT_t LCD = {
.RS_Pin.Port_Number = Port_C,.RS_Pin.Pin_Number = Pin0,.RS_Pin.direction = Output,.RS_Pin.logic = Low,   
.EN_Pin.Port_Number = Port_C,.EN_Pin.Pin_Number = Pin1,.EN_Pin.direction = Output,.EN_Pin.logic = Low,      
.LCD_Pins[0].Port_Number = Port_C,.LCD_Pins[0].Pin_Number = Pin2,.LCD_Pins[0].direction = Output,.LCD_Pins[0].logic = Low,
.LCD_Pins[1].Port_Number = Port_C,.LCD_Pins[1].Pin_Number = Pin3,.LCD_Pins[1].direction = Output,.LCD_Pins[1].logic = Low,
.LCD_Pins[2].Port_Number = Port_C,.LCD_Pins[2].Pin_Number = Pin4,.LCD_Pins[2].direction = Output,.LCD_Pins[2].logic = Low,
.LCD_Pins[3].Port_Number = Port_C,.LCD_Pins[3].Pin_Number = Pin5,.LCD_Pins[3].direction = Output,.LCD_Pins[3].logic = Low};

ADC_t ADC1 = {
.ACQ_Time = Acquisition_Time_12_TAD,.ADC_Interrupt_Handler = ADC_Get_Conversion_Value,.Channel = ADC_Channel_12,
.Clock = ADC_Clock_FOSC_DIV_4,.Result_Format = Right_Justified,.Voltage_Reference = voltage_Reference_Disable};

ADC_t ADC2 = {
.ACQ_Time = Acquisition_Time_12_TAD,.ADC_Interrupt_Handler = ADC_Get_Conversion_Value,.Channel = ADC_Channel_10,
.Clock = ADC_Clock_FOSC_DIV_4,.Result_Format = Right_Justified,.Voltage_Reference = voltage_Reference_Disable};

STD_Return_t ret_val = R_OK;
uint16 temp_1_value = 0;
uint16 temp_2_value = 0;
uint16 temp_one = 0;
uint16 temp_two = 0;
uint8 temp_1_string[5];
uint8 temp_2_string[5];
uint8 conversion_order = 0;

int main() {
ret_val = motor_initialize(&First_Motor);
ret_val |= motor_initialize(&Second_Motor);
ret_val |= ADC_Interrupt(&ADC1);
ret_val |= LCD_4_Bit_initialization(&LCD);
ret_val |= LCD_4_Bit_Send_String_Pos(&LCD,"Project one",1,5);
ret_val |= ADC_Init(&ADC1);
ret_val |= ADC_Init(&ADC2);
ret_val |= LCD_4_Bit_Send_String_Pos(&LCD,"Temp 1 value :",3,2);
ret_val |= LCD_4_Bit_Send_String_Pos(&LCD,"Temp 2 value :",4,2);
while(1)
{
if(conversion_order == 0)
{
ADC_Start_Conversion_unblocking(&ADC1,ADC_Channel_12);  
}
else if(conversion_order == 1)
{
ADC_Start_Conversion_unblocking(&ADC2,ADC_Channel_10);  
}
temp_one = ((temp_1_value * 4.88) / (10));
temp_two = ((temp_2_value * 4.88) / (10));
Convert_uint16_to_string(temp_one,temp_1_string);
Convert_uint16_to_string(temp_two,temp_2_string);
ret_val |= LCD_4_Bit_Send_String_Pos(&LCD,temp_1_string,3,16);
ret_val |= LCD_4_Bit_Send_String_Pos(&LCD,temp_2_string,4,16);
if(temp_one > 25)
{
ret_val |= motor_move_right(&First_Motor);        
}
else {/* Nothing */}
if(temp_two > 28)
{
ret_val |= motor_move_left(&Second_Motor); 
}
else {/* Nothing */}
if ((temp_one < 25) && (temp_two < 25))
{
ret_val |= motor_stop(&First_Motor); 
ret_val |= motor_stop(&Second_Motor); 
}
else {/* Nothing */}
}
}
void ADC_Get_Conversion_Value(void)
{
if(conversion_order == 0)
{
ret_val |= ADC_Get_Conversion_Result(&ADC1,&temp_1_value); 
conversion_order = 1 ;
}
else if(conversion_order == 1)
{
ret_val |= ADC_Get_Conversion_Result(&ADC2,&temp_2_value); 
conversion_order = 0;
}   
}