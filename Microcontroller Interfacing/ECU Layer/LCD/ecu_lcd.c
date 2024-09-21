/* 
 * File:   ecu_lcd.c
 * Author: Amr Ali
 *
 * Created on March 17, 2024, 12:43 AM
 */
#include "ecu_lcd.h"
static STD_Return_t Send_Enable_8_Bit(LCD_8_BIT_t *LCD);
static STD_Return_t Send_Enable_4_Bit(LCD_4_BIT_t *LCD);
static STD_Return_t Set_Cursor_8_Bit(LCD_8_BIT_t *LCD,uint8 Row,uint8 Column);
static STD_Return_t Set_Cursor_4_Bit(LCD_4_BIT_t *LCD,uint8 Row,uint8 Column);
static STD_Return_t Send_4_Bit(LCD_4_BIT_t *LCD,uint8 data_command);

/**
 * @brief initialize LCD pins
 * @param reference LCD configurations @ref LCD_8_BIT_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */

STD_Return_t LCD_8_Bit_initialization(LCD_8_BIT_t *LCD)
{
STD_Return_t ret = R_NOK;
uint8 i = 0;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = pin_initialize(&(LCD->EN_Pin));
ret = pin_initialize(&(LCD->RS_Pin));
for(i=0;i<8;i++)
{
ret = pin_initialize(&(LCD->LCD_Pins[i]));    
}
__delay_ms(20);
ret = LCD_8_Bit_Send_Command(LCD,Function_Set_8_Bit_Multi_Lines);
__delay_ms(5);
ret = LCD_8_Bit_Send_Command(LCD,Function_Set_8_Bit_Multi_Lines);
__delay_us(150);
ret = LCD_8_Bit_Send_Command(LCD,Function_Set_8_Bit_Multi_Lines);

ret = LCD_8_Bit_Send_Command(LCD,Function_Set_8_Bit_Multi_Lines);
ret = LCD_8_Bit_Send_Command(LCD,Display_off_Cursor_off_Blinking_off);
ret = LCD_8_Bit_Send_Command(LCD,Display_Clear);
ret = LCD_8_Bit_Send_Command(LCD,Increment_Address_Shift_off);
ret = LCD_8_Bit_Send_Command(LCD,Display_on_Cursor_off_Blinking_off);
ret = R_OK;
}
return ret;
}

/**
 * @brief Send Command to LCD
 * @param reference LCD configurations @ref LCD_8_BIT_t
 * @param Command
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_8_Bit_Send_Command(LCD_8_BIT_t *LCD,uint8 Command) 
{
STD_Return_t ret = R_NOK;
uint8 i = 0;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = pin_write_logic(&(LCD->RS_Pin),Low);
for(i=0;i<8;i++)
{
ret = pin_write_logic(&(LCD->LCD_Pins[i]),((Command>>i)&0x01));
}  
ret = Send_Enable_8_Bit(LCD);
ret = R_OK;
}
return ret;
}       

/**
 * @brief Send character to LCD
 * @param reference LCD configurations @ref LCD_8_BIT_t
 * @param data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_8_Bit_Send_Char_Data(LCD_8_BIT_t *LCD,uint8 Data) 
{
STD_Return_t ret = R_NOK;
uint8 i = 0;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = pin_write_logic(&(LCD->RS_Pin),High);
for(i=0;i<8;i++)
{
ret = pin_write_logic(&(LCD->LCD_Pins[i]),((Data>>i)&0x01));
}  
ret = Send_Enable_8_Bit(LCD);   
ret = R_OK;
}
return ret;
}       
/**
 * @brief Send character to LCD and display it in a specific position
 * @param reference LCD configurations @ref LCD_8_BIT_t
 * @param data
 * @param Row
 * @param Column
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_8_Bit_Send_Char_Data_Pos(LCD_8_BIT_t *LCD,uint8 Data,uint8 Row,uint8 Column)
{
STD_Return_t ret = R_NOK;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = Set_Cursor_8_Bit(LCD,Row,Column);
ret = LCD_8_Bit_Send_Char_Data(LCD,Data);    
ret = R_OK;
}
return ret;
}      

/**
 * @brief Send string to LCD and display it in a specific position
 * @param reference LCD configurations @ref LCD_8_BIT_t
 * @param string
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_8_Bit_Send_String(LCD_8_BIT_t *LCD,uint8 *string)  
{
STD_Return_t ret = R_NOK;
if((NULL == LCD) || (NULL == string))
{
ret = R_NOK;
}
else
{
while(*string)
{
ret = LCD_8_Bit_Send_Char_Data(LCD,*string);
string++;
}   
ret = R_OK;
}
return ret;
}   
/**
 * @brief Send string to LCD and display it in a specific position
 * @param reference LCD configurations @ref LCD_8_BIT_t
 * @param string
 * @param Row
 * @param Column
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_8_Bit_Send_String_Pos(LCD_8_BIT_t *LCD,uint8 *string,uint8 Row,uint8 Column)
{
STD_Return_t ret = R_NOK;
if((NULL == LCD) || (NULL == string))
{
ret = R_NOK;
}
else
{
ret = Set_Cursor_8_Bit(LCD,Row,Column);
ret = LCD_8_Bit_Send_String(LCD,string);    
ret = R_OK;
}
return ret;
}     
/**
 * @brief Send custom character to LCD and display it in a specific position
 * @param reference LCD configurations @ref LCD_8_BIT_t
 * @param custom character
 * @param character position in the memory
 * @param Row
 * @param Column
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_8_Bit_Send_Custom_Char(LCD_8_BIT_t *LCD,uint8 *Custom_Char,uint8 mem_pos,uint8 Row,uint8 Column)
{
STD_Return_t ret = R_NOK;
uint8 i = 0;
if((NULL == LCD) || (NULL == Custom_Char))
{
ret = R_NOK;
}
else
{
ret = LCD_8_Bit_Send_Command(LCD,(0x40+(8*mem_pos)));
for(i=0;i<8;i++)
{
ret = LCD_8_Bit_Send_Char_Data(LCD,Custom_Char[i]);
}  
ret = LCD_8_Bit_Send_Char_Data_Pos(LCD,mem_pos,Row,Column);
ret = R_OK;
}
return ret;
}

/**
 * @brief initialize LCD pins
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_4_Bit_initialization(LCD_4_BIT_t *LCD)   
{
STD_Return_t ret = R_NOK;
uint8 i = 0;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = pin_initialize(&(LCD->EN_Pin));
ret = pin_initialize(&(LCD->RS_Pin));
for(i=0;i<4;i++)
{
ret = pin_initialize(&(LCD->LCD_Pins[i]));
}
__delay_ms(20);
ret = LCD_4_Bit_Send_Command(LCD,Function_Set_8_Bit_Multi_Lines);
__delay_ms(5);
ret = LCD_4_Bit_Send_Command(LCD,Function_Set_8_Bit_Multi_Lines);
__delay_us(150);
ret = LCD_4_Bit_Send_Command(LCD,Function_Set_8_Bit_Multi_Lines);
ret = LCD_4_Bit_Send_Command(LCD,Display_Clear);
ret = LCD_4_Bit_Send_Command(LCD,0x02);
ret = LCD_4_Bit_Send_Command(LCD,Increment_Address_Shift_off);
ret = LCD_4_Bit_Send_Command(LCD,Display_on_Cursor_off_Blinking_off);
ret = LCD_4_Bit_Send_Command(LCD,Function_Set_4_Bit_Multi_Lines);
ret = LCD_4_Bit_Send_Command(LCD,0x80);
ret = R_OK;
}
return ret;
}     

/**
 * @brief Send Command to LCD
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @param Command
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_4_Bit_Send_Command(LCD_4_BIT_t *LCD,uint8 Command) 
{
STD_Return_t ret = R_NOK;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = pin_write_logic(&(LCD->RS_Pin),Low);
ret = Send_4_Bit(LCD,(Command>>4));
ret = Send_Enable_4_Bit(LCD);
ret = Send_4_Bit(LCD,(Command));
ret = Send_Enable_4_Bit(LCD);
ret = R_OK;
}
return ret;
}     

/**
 * @brief Send Command to LCD
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @param Data
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_4_Bit_Send_Char_Data(LCD_4_BIT_t *LCD,uint8 Data) 
{
STD_Return_t ret = R_NOK;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = pin_write_logic(&(LCD->RS_Pin),High);
ret = Send_4_Bit(LCD,(Data>>4));
ret = Send_Enable_4_Bit(LCD);
ret = Send_4_Bit(LCD,(Data));
ret = Send_Enable_4_Bit(LCD);   
ret = R_OK;
}
return ret;
}        

/**
 * @brief Send character to LCD and display it in a specific position
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @param data
 * @param Row
 * @param Column
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_4_Bit_Send_Char_Data_Pos(LCD_4_BIT_t *LCD,uint8 Data,uint8 Row,uint8 Column)
{
STD_Return_t ret = R_NOK;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = Set_Cursor_4_Bit(LCD,Row,Column);
ret = LCD_4_Bit_Send_Char_Data(LCD,Data);    
ret = R_OK;
}
return ret;
}       

/**
 * @brief Send string to LCD and display it in a specific position
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @param string
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_4_Bit_Send_String(LCD_4_BIT_t *LCD,uint8 *string) 
{
STD_Return_t ret = R_NOK;
if((NULL == LCD) || (NULL == string))
{
ret = R_NOK;
}
else
{
while(*string)   
{
ret = LCD_4_Bit_Send_Char_Data(LCD,*string);   
string++;
}
ret = R_OK;
}
return ret;
}        

/**
 * @brief Send string to LCD and display it in a specific position
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @param string
 * @param Row
 * @param Column
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_4_Bit_Send_String_Pos(LCD_4_BIT_t *LCD,uint8 *string,uint8 Row,uint8 Column)
{
STD_Return_t ret = R_NOK;
if((NULL == LCD) || (NULL == string))
{
ret = R_NOK;
}
else
{
ret = Set_Cursor_4_Bit(LCD,Row,Column);
ret = LCD_4_Bit_Send_String(LCD,string);    
ret = R_OK;
}
return ret;
}       

/**
 * @brief Send custom character to LCD and display it in a specific position
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @param custom character
 * @param character position in the memory
 * @param Row
 * @param Column
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t LCD_4_Bit_Send_Custom_Char(LCD_4_BIT_t *LCD,uint8 *Custom_Char,uint8 mem_pos,uint8 Row,uint8 Column)
{
STD_Return_t ret = R_NOK;
uint8 i = 0;
if((NULL == LCD) || (NULL == Custom_Char))
{
ret = R_NOK;
}
else
{
ret = LCD_4_Bit_Send_Command(LCD,(0x40+(8*mem_pos)));
for(i=0;i<8;i++)
{
ret = LCD_4_Bit_Send_Char_Data(LCD,Custom_Char[i]);
}  
ret = LCD_4_Bit_Send_Char_Data_Pos(LCD,mem_pos,Row,Column);   
ret = R_OK;
}
return ret;
}

/**
 * @brief convert unint8 to string
 * @param Data
 * @param string
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Convert_uint8_to_string(uint8 Data,uint8 *String)
{
STD_Return_t ret = R_NOK;
uint8 counter = 0;
uint8 Temp_string[3] = {0};
if(NULL == String)
{
ret = R_NOK;
}
else
{
memset((char *)String,'\0',3);
sprintf(Temp_string,"%i",Data);
while(Temp_string[counter] != '\0')
{
String[counter] = Temp_string[counter];
counter++;
}
ret = R_OK;
}
return ret;
} 
/**
 * @brief convert uint16 to string
 * @param Data
 * @param string
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Convert_uint16_to_string(uint16 Data,uint8 *String)
{
STD_Return_t ret = R_NOK;
uint8 Temp_string[5] = {0};
uint8 counter = 0;
if(NULL == String)
{
ret = R_NOK;
}
else
{
memset((char *)String,'\0',5);
sprintf(Temp_string,"%i",Data);
while(Temp_string[counter] != '\0')
{
String[counter] = Temp_string[counter];
counter++;
}
ret = R_OK;
}
return ret;
}       
/**
 * @brief convert uint32 to string
 * @param Data
 * @param string
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Convert_uint32_to_string(uint32 Data,uint8 *String)
{
STD_Return_t ret = R_NOK;
uint8 counter = 0;
uint8 Temp_string[11] = {0};
if(NULL == String)
{
ret = R_NOK;
}
else
{
memset((char *)String,'\0',11);
sprintf(Temp_string,"%i",Data);
while(Temp_string[counter] != '\0')
{
String[counter] = Temp_string[counter];
counter++;
}
ret = R_OK;
}
return ret;
}
/**
 * @brief send enable signal
 * @param reference LCD configurations @ref LCD_8_BIT_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Send_Enable_8_Bit(LCD_8_BIT_t *LCD)
{
STD_Return_t ret = R_NOK;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = pin_write_logic(&(LCD->EN_Pin),High);
__delay_us(5);
ret = pin_write_logic(&(LCD->EN_Pin),Low);
ret = R_OK;
}
return ret;    
}

/**
 * @brief send enable signal
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Send_Enable_4_Bit(LCD_4_BIT_t *LCD)
{
STD_Return_t ret = R_NOK;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
ret = pin_write_logic(&(LCD->EN_Pin),High);
__delay_us(5);
ret = pin_write_logic(&(LCD->EN_Pin),Low);   
ret = R_OK;
}
return ret;    
}

/**
 * @brief set cursor at specific position
 * @param reference LCD configurations @ref LCD_8_BIT_t
 * @param Row
 * @param Column
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Set_Cursor_8_Bit(LCD_8_BIT_t *LCD,uint8 Row,uint8 Column)
{
STD_Return_t ret = R_NOK;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
Column--;
switch(Row)  
{
case ROW1: LCD_8_Bit_Send_Command(LCD,(0x80+Column)); break;
case ROW2: LCD_8_Bit_Send_Command(LCD,(0xC0+Column)); break;
case ROW3: LCD_8_Bit_Send_Command(LCD,(0x94+Column)); break;
case ROW4: LCD_8_Bit_Send_Command(LCD,(0xD4+Column)); break;
default : ret = R_NOK;
}
ret = R_OK;
}
return ret;     
}

/**
 * @brief set cursor at specific position
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @param Row
 * @param Column
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Set_Cursor_4_Bit(LCD_4_BIT_t *LCD,uint8 Row,uint8 Column)
{
STD_Return_t ret = R_NOK;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
Column--;
switch(Row)  
{
case ROW1: LCD_4_Bit_Send_Command(LCD,(0x80+Column)); break;
case ROW2: LCD_4_Bit_Send_Command(LCD,(0xC0+Column)); break;
case ROW3: LCD_4_Bit_Send_Command(LCD,(0x94+Column)); break;
case ROW4: LCD_4_Bit_Send_Command(LCD,(0xD4+Column)); break;
default : ret = R_NOK;
}
ret = R_OK;
}
return ret;     
}
/**
 * @brief send 4 bits to LCD (use this function only if LCD was in 4 bits mode)
 * @param reference LCD configurations @ref LCD_4_BIT_t
 * @param Row
 * @param Column
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t Send_4_Bit(LCD_4_BIT_t *LCD,uint8 data_command)
{
STD_Return_t ret = R_NOK;
uint8 i = 0;
if(NULL == LCD)
{
ret = R_NOK;
}
else
{
for(i=0;i<4;i++)
{
ret = pin_write_logic(&(LCD->LCD_Pins[i]),((data_command) >> i) & (uint8)0X01);       
}
ret = R_OK;
}
return ret;    
}