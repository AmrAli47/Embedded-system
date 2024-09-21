
#include "mcc_generated_files/mcc.h"

i2c_error_t error_value = 0;
DS1307_t DS1307;
        
uint8_t Temperature_Value = 0;
uint8_t First_Value = 0;
uint8_t Second_Value = 0;
void main(void)
{
   
    SYSTEM_Initialize();

    

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    I2C_Write_Byte_to_eeprom(0x57,0x00,0x55);
    __delay_us(500);
    I2C_Write_Byte_to_eeprom(0x50,0xFF,0x55);
    __delay_us(500);
    First_Value = I2C_Read_Byte_from_eeprom(0x57,0x00);
    __delay_us(500);
    Second_Value = I2C_Read_Byte_from_eeprom(0x50,0xFF);
    __delay_us(500);
    while (1)
    {   
    DS1307.Seconds = I2C_D1307_Read_Values(0x68,0x00);
    DS1307.hours   = I2C_D1307_Read_Values(0x68,0x02);
    DS1307.minutes = I2C_D1307_Read_Values(0x68,0x01);
    DS1307.days    = I2C_D1307_Read_Values(0x68,0x04);
    DS1307.months  = I2C_D1307_Read_Values(0x68,0x05);
    DS1307.years   = I2C_D1307_Read_Values(0x68,0x06);    
    EUSART_Write_String("Date : ",6);   
    EUSART_Write((DS1307.Seconds >> 4)+48);
    EUSART_Write((DS1307.Seconds & 0X0F)+48);
    EUSART_Write_String(" - ",3);  
    EUSART_Write((DS1307.minutes >> 4)+48);
    EUSART_Write((DS1307.minutes & 0X0F)+48);
    EUSART_Write_String(" - ",3);   
    EUSART_Write((DS1307.hours >> 4)+48);
    EUSART_Write((DS1307.hours & 0X0F)+48);
    EUSART_Write_String(" - ",3);   
    EUSART_Write((DS1307.days >> 4)+48);
    EUSART_Write((DS1307.days & 0X0F)+48);
    EUSART_Write_String(" - ",3);    
    EUSART_Write((DS1307.months >> 4)+48);
    EUSART_Write((DS1307.months & 0X0F)+48);
    EUSART_Write_String(" - ",3);   
    EUSART_Write((DS1307.years >> 4)+48);
    EUSART_Write((DS1307.years & 0X0F)+48);
    EUSART_Write_String("\r",1); 
    Temperature_Value = I2C_Read_Temp_Value(0x48,0x00); 
    I2C_Write1ByteRegister(0x21,0x00,Temperature_Value); 
    }
}
