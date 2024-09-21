/* 
 * File:   ecu_lcd.h
 * Author: Amr Ali
 *
 * Created on March 17, 2024, 12:43 AM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/*----------------Includes----------------*/
#include "../../MCAL/GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"

/*----------------Macros----------------*/
#define Function_Set_8_Bit_Multi_Lines         0x38
#define Function_Set_4_Bit_Multi_Lines         0x28
#define Display_off_Cursor_off_Blinking_off    0x08
#define Display_on_Cursor_off_Blinking_off     0x0C
#define Display_Clear                          0x01
#define Increment_Address_Shift_off            0x06
#define ROW1  1
#define ROW2  2
#define ROW3  3
#define ROW4  4

/*----------------Macro_Functions----------------*/

/*----------------User_defined_data_types----------------*/
typedef struct{
Pin_Cofnig_t RS_Pin;
Pin_Cofnig_t EN_Pin;
Pin_Cofnig_t LCD_Pins[8];
}LCD_8_BIT_t;

typedef struct{
Pin_Cofnig_t RS_Pin;
Pin_Cofnig_t EN_Pin;
Pin_Cofnig_t LCD_Pins[4];    
}LCD_4_BIT_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t LCD_8_Bit_initialization(LCD_8_BIT_t *LCD);       
STD_Return_t LCD_8_Bit_Send_Command(LCD_8_BIT_t *LCD,uint8 Command);  
STD_Return_t LCD_8_Bit_Send_Char_Data(LCD_8_BIT_t *LCD,uint8 Data);  
STD_Return_t LCD_8_Bit_Send_Char_Data_Pos(LCD_8_BIT_t *LCD,uint8 Data,uint8 Row,uint8 Column); 
STD_Return_t LCD_8_Bit_Send_String(LCD_8_BIT_t *LCD,uint8 *string);  
STD_Return_t LCD_8_Bit_Send_String_Pos(LCD_8_BIT_t *LCD,uint8 *string,uint8 Row,uint8 Column); 
STD_Return_t LCD_8_Bit_Send_Custom_Char(LCD_8_BIT_t *LCD,uint8 *Custom_Char,uint8 mem_pos,uint8 Row,uint8 Column);

STD_Return_t LCD_4_Bit_initialization(LCD_4_BIT_t *LCD);       
STD_Return_t LCD_4_Bit_Send_Command(LCD_4_BIT_t *LCD,uint8 Command);  
STD_Return_t LCD_4_Bit_Send_Char_Data(LCD_4_BIT_t *LCD,uint8 Data);  
STD_Return_t LCD_4_Bit_Send_Char_Data_Pos(LCD_4_BIT_t *LCD,uint8 Data,uint8 Row,uint8 Column); 
STD_Return_t LCD_4_Bit_Send_String(LCD_4_BIT_t *LCD,uint8 *string);  
STD_Return_t LCD_4_Bit_Send_String_Pos(LCD_4_BIT_t *LCD,uint8 *string,uint8 Row,uint8 Column); 
STD_Return_t LCD_4_Bit_Send_Custom_Char(LCD_4_BIT_t *LCD,uint8 *Custom_Char,uint8 mem_pos,uint8 Row,uint8 Column);

STD_Return_t Convert_uint8_to_string(uint8 Data,uint8 *String);
STD_Return_t Convert_uint16_to_string(uint16 Data,uint8 *String);
STD_Return_t Convert_uint32_to_string(uint32 Data,uint8 *String);
#endif	/* ECU_LCD_H */

