/* 
 * File:   mcal_spi.h
 * Author: Amr Ali
 *
 * Created on March 27, 2024, 11:34 AM
 */

#ifndef MCAL_SPI_H 
#define	MCAL_SPI_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/Interal_Interrupts/mcal_internal_interrupt.h"

/*----------------Macros----------------*/



/*----------------Macro_Functions----------------*/

// data sampled at the end of data output time
#define data_sampled_at_end_of_output_time() (SSPSTATbits.SMP = 1)
// data sampled at the Middle of data output time (This bit must be cleared in slave mode)
#define data_sampled_at_Middle_of_output_time() (SSPSTATbits.SMP = 0)

// Transmit occurs on transition from active to Idle clock state
#define Transmit_occurs_from_active_to_idle() (SSPSTATbits.CKE = 1)
// Transmit occurs on transition from Idle to active clock state
#define Transmit_occurs_from_idle_to_active() (SSPSTATbits.CKE = 0)

/*  Receive complete, SSPBUF is full (This bit is used in receive mode only)
 This bit is 1 when receive complete and buffer is fully but is zero when receive not complete and Buffer is empty*/
#define Read_Receive_Buffer_status() (SSPSTATbits.BF)

//Write Collision detect (collision means write data to SSPxBUF while still transmitting previous word) Note this bit must be cleared in software
#define Write_Collision_Detect_Bit() (SSPCON1bits.WCOL)
// if equals zero that means there is not collision but if 1 this means there is collision 
#define Clear_Collision_detect_bit() (SSPCON1bits.WCOL = 0)

// Enable MSSP Module
#define Enable_MSSP_Module()  (SSPCON1bits.SSPEN = 1)
// Disable MSSP Module
#define Disable_MSSP_Module() (SSPCON1bits.SSPEN = 0)

// Idle state for clock is a high level 
#define Clock_idle_state_is_high()  (SSPCON1bits.CKP = 1)
// Idle state for clock is a low level
#define Clock_idle_state_is_low()   (SSPCON1bits.CKP = 0)

// Configure MSSP Module
#define MSSP_Module_Config(config)  (SSPCON1bits.SSPM = config)

/* Receive overflow indicator bit, new byte is received while SSPBUF register is still holding the previous data, overflow occur only in slave
   mode, must be cleared in software*/
#define Write_Collision_Detect_Bit() (SSPCON1bits.SSPOV)
// if equals zero that means there is no overflow but if 1 this means there is overflow 
#define Clear_Collision_detect_bit() (SSPCON1bits.SSPOV = 0)


/*----------------User_defined_data_types----------------*/

typedef enum{
    SPI_Master_mode_Clock_is_Fosc_Div_by_4,
    SPI_Master_mode_Clock_is_Fosc_Div_by_16,
    SPI_Master_mode_Clock_is_Fosc_Div_by_64,
    SPI_Master_mode_Clock_is_TMR2_output_Div_by_2,        
    SPI_Slave_mode_Clock_is_SCK_Pin_SS_Pin_Enabled,
    SPI_Slave_mode_Clock_is_SCK_Pin_SS_Pin_Disabled
}SPI_Module_Configuration_t;

typedef enum{
    Master_Mode,
    Slave_Mode
}MCU_SPI_Mode_t;

typedef enum{
    idle_high,
    idle_low
}Clock_Mode_t;


typedef enum{
    at_the_end,
    at_the_middle
}Sampling_Mode_t;

typedef enum{
    active_to_idle,
    idle_to_active
}Transmitting_Mode_t;


typedef struct{
    void (* Collision_Interrupt_Handler)(void);
    void (* SPI_Read_Handler)(void);
 Transmitting_Mode_t Transmitting_Mode;  
 Sampling_Mode_t Sampling_Mode;  
 Clock_Mode_t clock_status;  
 MCU_SPI_Mode_t Mode;   
 SPI_Module_Configuration_t Module_Configuration;   
 #if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
}SPI_t;


/*----------------Software_Interfaces----------------*/
STD_Return_t SPI_Init(SPI_t *spi);
STD_Return_t SPI_DeInit(SPI_t *spi);
STD_Return_t SPI_Interrupt_Init(SPI_t *spi);

STD_Return_t SPI_write_Byte_Blocking(uint8 data);
STD_Return_t SPI_write_string_Blocking(uint8 *data,uint8 len);
STD_Return_t SPI_write_Byte_unblocking(uint8 data);
STD_Return_t SPI_Read_Byte_unblocking(uint8 *data);


#endif	/* MCAL_SPI_H */

