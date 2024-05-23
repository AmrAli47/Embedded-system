/* 
 * File:   mcal_eusart.h
 * Author: Amr Ali
 *
 * Created on March 25, 2024, 7:40 PM
 */

#ifndef MCAL_EUSART_H
#define	MCAL_EUSART_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/Interal_Interrupts/mcal_internal_interrupt.h"

/*----------------Macros----------------*/



/*----------------Macro_Functions----------------*/

// Enable UART Module
#define Enable_UART_Module()          (RCSTAbits.SPEN = 1)
// Disable UART Module
#define Disable_UART_Module()         (RCSTAbits.SPEN = 0)

// Select 9 bit Transmission
#define Select_9_Bit_Transmission()   (TXSTAbits.TX9 = 1)
// Select 8 bit Transmission
#define Select_8_Bit_Transmission()   (TXSTAbits.TX9 = 0)

// Select 9 bit Reception
#define Select_9_Bit_Reception()      (RCSTAbits.RX9 = 1)
// Select 8 bit Reception
#define Select_8_Bit_Reception()      (RCSTAbits.RX9 = 0)

// Enable Transmission Mode
#define Enable_Transmission_Mode()    (TXSTAbits.TXEN = 1)
//  Disable Transmission Mode
#define Disable_Transmission_Mode()   (TXSTAbits.TXEN = 0)

// UART Synchronous Mode
#define UART_Synchronous_Mode()       (TXSTAbits.SYNC = 1)
// UART Asynchronous Mode
#define UART_Asynchronous_Mode()      (TXSTAbits.SYNC = 0)

// Read TSR Status (0 means TSR is Full but 1 means TSR is empty)
#define Read_TSR_Status()             (TXSTAbits.TRMT)

// Enable 9th bit of data 
#define Enable_9th_Bit_data()         (TXSTAbits.TX9D = 1)

// High Speed BRGH
#define High_Baud_Rate()              (TXSTAbits.BRGH = 1)
// UART Asynchronous Mode
#define Low_Baud_Rate()               (TXSTAbits.BRGH = 0)

// Select MCU as a Master (for Synchronous Mode only and clock generated from BRG)
#define MCU_Master_Mode()              (TXSTAbits.CSRC = 1)
// Select MCU as a Slave (for Synchronous Mode only and clock generated from external source)
#define MCU_Slave_Mode()               (TXSTAbits.CSRC = 0)

// Send Synchronous Break on next instruction (Cleared by hardware)
#define Send_Synchronous_Break()       (TXSTAbits.SENDB = 1)
// This Pin becomes zero when synchronous break completed
#define Send_Break_Completed()          (TXSTAbits.CSRC)

// Enable Single Receive (Synchronous Mode only) (This bit is cleared after reception is complete)
#define Enable_Single_Receive()    (RCSTAbits.SREN = 1)
//  Disable Single Receive 
#define Disable_Single_Receive()   (RCSTAbits.SREN = 0)

/* Enable Continuous Receiver for Asynchronous Mode But for synchronous Mode Enables continuous receive until enable bit,
CREN, is cleared (CREN overrides SREN)*/
#define Enable_Continuous_Receiver()    (RCSTAbits.CREN = 1)
//  Disable Continuous Receive for synchronous and Asynchronous Mode
#define Disable_Continuous_Receiver()   (RCSTAbits.CREN = 0)

/* Read Framing Error (can be cleared by reading RCREG Register and receiving next valid byte) 
 * (0 means there is no framing error but 1 means there is frame error)*/
#define Read_Framing_Error() (RCSTAbits.FERR)

// Read overrun Error (can be cleared by Clearing CREN bit) (0 means there is no overrun error but 1 means there is overrun error)
#define Read_overrun_Error() (RCSTAbits.OERR)

// Read 9th bit (9th bit can be address or data or parity and if it is parity i should calculate it using firmware)
#define Read_9th_bit_Error() (RCSTAbits.RX9D)

// Address Detection Enable   (enables interrupt and loads the receive buffer when RSR<8> is set) (this bit is ignored if i do not use 9th bit transmit)
#define Enable_Address_detection()     (RCSTAbits.ADDEN = 1)
// Address Detection Disable  (All bytes are received and 9th bit can be used as a parity bit)
#define Disable_Address_detection()    (RCSTAbits.ADDEN = 0)

// Receive operation status bit (1 means receive operation is idle but 0 means receive operation is active)
#define Receive_operation_status()    (BAUDCONbits.RCIDL)


// 16 Bit Baud rate
#define Baud_Rate_16_Bit()              (BAUDCONbits.BRG16 = 1)
// 8 Bit Baud rate
#define Baud_Rate_8_Bit()               (BAUDCONbits.BRG16 = 0)

// idle state for clock in synchronous mode is high level or for transmit TX in Asynrhonous Mode is low level
#define idle_state_for_clock_or_Transmit()              (BAUDCONbits.TXCKP = 1)
// idle state for clock in synchronous mode is low level or for transmit TX in Asynrhonous Mode is high level
#define idle_state_for_clock_or_Transmit_reversing()     (BAUDCONbits.TXCKP = 0)

// Received data polarity (Asynchronous Mode only)
#define RX_Data_is_inverted()          (BAUDCONbits.RXDTP = 1)
#define RX_Data_is_not_inverted()      (BAUDCONbits.RXDTP = 0)

/* Auto-Baud Acquisition Rollover Status bit (zero means No BRG Rollover has occured)
 one means A BRG rollover has occurred during Auto-Baud Rate Detect mode (must be cleared in software) */
#define Auto_Baud_rate_Acquisition_Rollover_stauts() (BAUDCONbits.ABDOVF)

/* Enable Auto Baud rate detection, Enable baud rate measurement on the next character. Requires reception of a Sync field (55h);
 cleared in hardware upon completion this bit uses for synchronous mode only */
#define Enable_Auto_Baud_Rate_detector()    (BAUDCONbits.ABDEN = 1)
// Disable Auto Baud rate detection
#define Disable_Auto_Baud_Rate_detector()   (BAUDCONbits.ABDEN = 0)

/* Wake up enable this bit uses only for asynchronous mode, EUSART will continue to sample the RX pin ? 
 * interrupt generated on falling edge; bit cleared in hardware on following rising edge */
#define Enable_Wake_UP() (BAUDCONbits.WUE = 1)
// Disable Wake UP (RX pin not monitored or rising edge detected)
#define Disable_Wake_UP() (BAUDCONbits.WUE = 0)
/*----------------User_defined_data_types----------------*/
typedef enum{
    Transmission_Mode,
    Reception_Mode
}MCU_Mode_t;

typedef enum{
    Synchronous_Mode,
    Asynchronous_Mode
}exchanging_Mode_t;

typedef enum{
    data_8_bits,
    data_9_bits
}Data_Field_t;

typedef enum{
    config_8_bit_Asyncrhonous_Low_Speed,
    config_8_bit_Asyncrhonous_High_Speed,
    config_16_bit_Asyncrhonous_Low_Speed,
    config_16_bit_Asyncrhonous_High_Speed,
    config_8_bit_syncrhonous,
    config_16_bit_syncrhonous        
}Baud_Rate_Config_t;


typedef struct{
   void (* EUSART_Transmit_Interrupt_Handler)(void);
   MCU_Mode_t         direction; 
   Baud_Rate_Config_t BaudRate_config;
   uint16             BaudRate_value;
   Data_Field_t       data_field;
   exchanging_Mode_t Synchronization_type;
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif
}EUSART_t;

/*----------------Software_Interfaces----------------*/
STD_Return_t EUSART_Init(EUSART_t *EUSART);
STD_Return_t EUSART_DeInit(EUSART_t *EUSART);
STD_Return_t EUSART_Write_Byte_Blocking(EUSART_t *EUSART,uint8 data);
STD_Return_t EUSART_Write_string_Blocking(EUSART_t *EUSART,uint8 *data,uint8 length);

STD_Return_t EUSART_Write_Byte_unblocking(EUSART_t *EUSART,uint8 data);
STD_Return_t EUSART_Read_Byte_Blocking(EUSART_t *EUSART,uint8 *data);
STD_Return_t EUSART_Read_string_Blocking(EUSART_t *EUSART,uint8 *data,uint8 length);

STD_Return_t EUSART_Read_String_unblocking(EUSART_t *EUSART,uint8 *data);


STD_Return_t EUSART_Read_Byte_unblocking(EUSART_t *EUSART,uint8 *data);
#endif	/* MCAL_EUSART_H */

