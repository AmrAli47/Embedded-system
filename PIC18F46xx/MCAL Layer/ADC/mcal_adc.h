/* 
 * File:   mcal_adc.h
 * Author: Amr Ali
 *
 * Created on March 21, 2024, 9:47 PM
 */

#ifndef MCAL_ADC_H
#define	MCAL_ADC_H

/*----------------Includes----------------*/
#include "../GPIO/mcal_gpio.h"
#include "../../MCAL/mcal_std_libraries.h"
#include "../External_Interrupts/mcal_external_interrupt_config.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL/Interal_Interrupts/mcal_internal_interrupt.h"

/*----------------Macros----------------*/
#define AN0_Functionality         0x0E
#define AN1_Functionality         0x0D
#define AN2_Functionality         0x0C
#define AN3_Functionality         0x0B
#define AN4_Functionality         0x0A
#define AN5_Functionality         0x09
#define AN6_Functionality         0x08
#define AN7_Functionality         0x07
#define AN8_Functionality         0x06
#define AN9_Functionality         0x05
#define AN10_Functionality        0x04
#define AN11_Functionality        0x03
#define AN12_Functionality        0x02
#define All_Analog_Functionality  0x00
#define All_Digital_Functionality 0x0F

/*----------------Macro_Functions----------------*/
// ADC Module Enable
#define ADC_Module_Enable()             (ADCON0bits.ADON = 1)
// ADC Module Disable
#define ADC_Module_Disable()            (ADCON0bits.ADON = 0)

// ADC Start Conversion
#define ADC_Start_Conversion()          (ADCON0bits.GODONE = 1)
// ADC Read Conversion Status
#define ADC_Read_Conversion_Status()    (ADCON0bits.GODONE)

// ADC Voltage Reference Enable
#define ADC_Voltage_Reference_Enable()    do{ADCON1bits.PCFG1 = 1;\
                                             ADCON1bits.PCFG0 = 1;\
                                             }while(0)
// ADC Voltage Reference Disable
#define ADC_Voltage_Reference_Disable()     do{ADCON1bits.PCFG1 = 0;\
                                               ADCON1bits.PCFG0 = 0;\
                                              }while(0)


// Result Format Left Justified
#define ADC_Result_Left_Jusitifed()           (ADCON2bits.ADFM = 0)
// Result Format Right Justified
#define ADC_Result_Right_Jusitifed()          (ADCON2bits.ADFM = 1)

// ADC Set Acquisition Time
#define ADC_Set_Acquisition_Time(Config)      (ADCON2bits.ACQT = Config)

// ADC Set Clock
#define ADC_Set_Clock(Clock)                  (ADCON2bits.ADCS = Clock)

// ADC Port Config
#define ADC_Port_Config(Config)               (ADCON1bits.PCFG = Config)

// ADC Select Channel
#define ADC_Select_Ch(ch)               (ADCON0bits.CHS = ch)

/*----------------User_defined_data_types----------------*/
typedef enum{
    ADC_Channel_0,
    ADC_Channel_1,
    ADC_Channel_2,        
    ADC_Channel_3,        
    ADC_Channel_4,
    ADC_Channel_5,
    ADC_Channel_6,        
    ADC_Channel_7,             
    ADC_Channel_8,
    ADC_Channel_9,
    ADC_Channel_10,        
    ADC_Channel_11,            
    ADC_Channel_12        
}ADC_Channel_t;

typedef enum{
    Left_Justified,
    Right_Justified       
}Result_Format_t;

typedef enum{
    Acquisition_Time_0_TAD,
    Acquisition_Time_2_TAD,
    Acquisition_Time_4_TAD,        
    Acquisition_Time_6_TAD,        
    Acquisition_Time_8_TAD,
    Acquisition_Time_12_TAD,
    Acquisition_Time_16_TAD,
    Acquisition_Time_20_TAD      
}ADC_Acquisition_Time_t;

typedef enum{
    ADC_Clock_FOSC_DIV_2,
    ADC_Clock_FOSC_DIV_8,
    ADC_Clock_FOSC_DIV_32,        
    ADC_Clock_FOSC_DIV_FRC,        
    ADC_Clock_FOSC_DIV_4,
    ADC_Clock_FOSC_DIV_16,
    ADC_Clock_FOSC_DIV_64     
}ADC_Clock_t;

typedef enum{
    voltage_Reference_Disable,
    voltage_Reference_Enable        
}Voltage_Reference_t;


typedef struct{
#if (Interrupt_Feature_Enable == 1)
void (* ADC_Interrupt_Handler)(void);
#endif
Result_Format_t Result_Format; 
ADC_Clock_t Clock;
ADC_Acquisition_Time_t ACQ_Time;
ADC_Channel_t Channel;
Voltage_Reference_t Voltage_Reference;
#if (Interrupt_Priority_Enable == 1)
Interrupt_Priority_CFG Priority;
#endif   
}ADC_t;


/*----------------Software_Interfaces----------------*/
STD_Return_t ADC_Init(ADC_t *ADC);
STD_Return_t ADC_DeInit(ADC_t *ADC);
STD_Return_t ADC_Interrupt(ADC_t *ADC);
STD_Return_t ADC_Start_Conversion_Blocking(ADC_t *ADC,ADC_Channel_t channel);
STD_Return_t ADC_Start_Conversion_unblocking(ADC_t *ADC,ADC_Channel_t channel);
STD_Return_t ADC_Get_Conversion_Result(ADC_t *ADC,uint16 *Conversion_Result);




#endif	/* MCAL_ADC_H */

