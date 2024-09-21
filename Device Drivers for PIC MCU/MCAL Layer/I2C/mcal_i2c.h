/* 
 * File:   mcal_i2c.h
 * Author: Amr Ali
 *
 * Created on March 28, 2024, 12:40 AM
 */

#ifndef MCAL_I2C_H 
#define	MCAL_I2C_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/Interal_Interrupts/mcal_internal_interrupt.h"

/*----------------Macros----------------*/

#define device_address 60

/*----------------Macro_Functions----------------*/
// Enable I2C Module
#define Enable_I2C_Module()  (SSPCON1bits.SSPEN = 1)
// Disable I2C Module
#define Disable_I2C_Module() (SSPCON1bits.SSPEN = 0)

// Set I2C Module Configuration
#define Set_I2C_Module_Configuration(config) (SSPCON1bits.SSPM = config)

// Release clock, This bit uses in slave Mode
#define Disable_Clock_stretching()  (SSPCON1bits.CKP = 1)
// Holds clock low (used to ensure data setup time ) This bit uses in slave Mode
#define Enable_Clock_stretching()   (SSPCON1bits.CKP = 0)

/* Receive overflow indicator bit, new byte is received while SSPBUF register is still holding the previous data,
 * must be cleared in software, this bit is is do not care in transmit mode*/
#define Write_Collision_Detect_Bit() (SSPCON1bits.SSPOV)
// if equals zero that means there is no overflow but if 1 this means there is overflow 
#define Clear_Collision_detect_bit() (SSPCON1bits.SSPOV = 0)

/*Write Collision detect 
 *  In Master Transmit mode: A write to the SSPBUF register was attempted while the I2C conditions were not valid for a
 *  transmission to be started (must be cleared in software)
 * In Slave Transmit mode: The SSPBUF register is written while it is still transmitting the previous word (must be cleared in
 software) */  
#define Write_Collision_Detect_Bit() (SSPCON1bits.WCOL)
// if equals zero that means there is not collision but if 1 this means there is collision (This bit is do not care in receive mode)
#define Clear_Collision_detect_bit() (SSPCON1bits.WCOL = 0)

// Stop Condition Enable bit (Initiates Stop condition on SDA and SCL pins. Automatically cleared by hardware) (This bit uses by master only)
#define Set_Stop_Condition_on_Bus() (SSPCON2bits.PEN = 1)
// Stop condition Idle
#define Stop_Condition_idle()       (SSPCON2bits.PEN = 0)

/* Repeated Start Condition Enable bit (Initiates Repeated Start condition on SDA and SCL pins. Automatically cleared by hardware)
(This bit uses by master only)*/
#define Set_Repeated_Start_Condition_on_Bus() (SSPCON2bits.RSEN = 1)
// Repeated Start condition Idle
#define Repeated_Start_Condition_idle()       (SSPCON2bits.RSEN = 0)

// Enable Interrupt when general call address is received in SSPSR
#define General_Call_Address_Interrupt_Enable()  (SSPCON2bits.GCEN = 1)
// Disable General Call Address Feature
#define General_Call_Address_Interrupt_Disable()  (SSPCON2bits.GCEN = 0)

// Enable Receive Mode (uses for Master Mode only)
#define Enable_Receive_Mode() (SSPCON2bits.RCEN = 1)
// Receive Mode is idle (uses for Master Mode only)
#define Disable_Receive_Mode() (SSPCON2bits.RCEN = 0)

//Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. Automatically cleared by hardware
#define Enable_Acknowledge_Sequence() (SSPCON2bits.ACKEN = 1)
//  Acknowledge Sequence is idle (This bit uses for Master receive mdoe only)
#define Disable_Acknowledge_Sequence() (SSPCON2bits.ACKEN = 0)

/* Acknowledge status bit (Master Transmit Mode only) if one means acknowledge was not received from slave bit 
  if zero means acknowledge received form slave */ 
#define Acknowledge_Status_bit()  (SSPCON2bits.ACKSTAT)

/* Acknowledge data bit (Master Receive Mode only) if one means NotAcknowledge if zero means Acknowledge
 * Value that will be transmitted when the user initiates an Acknowledge sequence at the end of a receive */ 
#define Acknowledge_Status_bit()  (SSPCON2bits.ACKDT)

// Start Condition Enable
/* in Master Mode Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware */
#define Enable_Start_Condition() (SSPCON2bits.SEN = 1)
// Start Condition is idle
#define Disable_Start_Condition() (SSPCON2bits.SEN = 0)

// Clock Stretching Enable bit 
/* in Slave Mode  Clock stretching is enabled for both slave transmit and slave receive (stretch enabled)*/
#define Enable_Clock_Stretching() (SSPCON2bits.SEN = 1)
// Start Condition is idle
#define Disable_Clock_Stretching() (SSPCON2bits.SEN = 0)

// slew rate standard mode
#define Enable_Slew_Rate_Standard_Mode()  (SSPSTATbits.SMP = 1)
// slew rate High Speed mode
#define Enable_Slew_Rate_High_Speed_Mode()  (SSPSTATbits.SMP = 0)

// SMBus select bits
#define Enable_SMbus_Specific_inputs()   (SSPSTATbits.CKE = 1)
// SMBus select bits
#define Disable_SMbus_Specific_inputs()  (SSPSTATbits.CKE = 0)

// if one means last byte received or transmitted was data but if zero means this byte was address (This bit uses for salve mode only)
#define Data_Address_Status_bit() (SSPSTATbits.D_NOT_A)

// if one means Stop bit has been detected but if zero means Stop bit was not detected
#define Stop_Sequence_indication_bit() (SSPSTATbits.P)

// if one means Start bit has been detected but if zero means Start bit was not detected
#define Stop_Sequence_indication_bit() (SSPSTATbits.S)

/* if one means user needs to update the address in the SSPADD register  but if zero means Address does not need to be updated 
    This bit uses for (10 Bit Slave Mode only */
#define Update_Address_indication_bit() (SSPSTATbits.UA)

/* in Trnasmit Mode (1 means SSPBUF is Full but 0 means SSPBUF is empty) 
 * in receive Mode ( 1 means SSPBUF is full but 0 means SSPBUF is empty (does not include the ACK  and Stop bits) */
#define Buffer_Full_Status_Bit() (SSPSTATbits.BF)

// Read / Write information bit (in Master Mode 1 means Trnasmit is in progress but in slave mode 1 means Read)
#define Read_Operation() (SSPSTATbits.R_NOT_W = 1)
// Read / Write information bit (in Master Mode 0 means Trnasmit is not in progress but in slave mode 0 means Write)
#define Write_Operation() (SSPSTATbits.R_NOT_W = 0)
/*----------------User_defined_data_types----------------*/
typedef enum{
    I2C_Slave_mode_7_bit_address  = 6,
    I2C_Slave_mode_10_bit_address = 7,
    I2C_Master_mode_clock_is_FOSC_Div_4_by_SSPADD_plus_1 = 8,
    I2C_Firmware_Controlled_Master_mode_Slave_idle = 11,
    I2C_Slave_mode_7_bit_address_with_Start_and_Stop_bit_interrupts_enabled = 14,
    I2C_Slave_mode_10_bit_address_with_Start_and_Stop_bit_interrupts_enabled = 15        
}I2C_Module_Configuration_t;

typedef enum{
    General_Call_Enable,
    General_Call_Disable
}General_Call_Address_t;

typedef enum{
    Standard_Mode,
    High_Speed_Mode
}Slew_Rate_Mode_t;

typedef enum{
    I2C_Slave_Mode,
    I2C_Master_Mode
}Module_Mode_t;

typedef struct{
void (* Interrupt_Handler)(void);
Module_Mode_t I2C_Mode;
Slew_Rate_Mode_t Slew_Rate;
General_Call_Address_t General_Call;    
I2C_Module_Configuration_t I2C_Config;    
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
}I2C_t;



/*----------------Software_Interfaces----------------*/
STD_Return_t I2C_Init(I2C_t *I2C);
STD_Return_t I2C_DeInit(I2C_t *I2C);

STD_Return_t I2C_Master_Send_Start_Condition(I2C_t *I2C);
STD_Return_t I2C_Master_Send_Repeated_Start_Condition(I2C_t *I2C);
STD_Return_t I2C_Master_Send_Stop_Condition(I2C_t *I2C);

STD_Return_t I2C_Slave_Read_Byte(I2C_t *I2C,uint8 *data);
STD_Return_t I2C_Slave_Send_Byte(I2C_t *I2C,uint8 data);

STD_Return_t I2C_Master_Read_Byte(I2C_t *I2C,uint8 *data);
STD_Return_t I2C_Master_Send_Byte(I2C_t *I2C,uint8 data);

#endif	/* MCAL_I2C_H */

