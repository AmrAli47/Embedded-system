/* 
 * File:   mcal_ccp.c
 * Author: Amr Ali
 *
 * Created on March 25, 2024, 1:02 AM
 */
#include "mcal_ccp.h"

#if (CCP_Module_Works_in == Capture_Mode)
static void (* Capture_Interrupt_Handler)(void) = NULL;
/**
 * @brief initialize CPP Module to work in Capture Mode
 * @param reference Capture Mode configurations @ref Capture_Mode_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Capture_Mode_Init(Capture_Mode_t *Capture)
{
STD_Return_t ret = R_NOK;
if(NULL == Capture)
{
ret = R_NOK;    
}
else
{
Set_CCP_Module_Mode(CCP_Module_Disable);
Set_CCP_Module_Mode(Capture->Mode);
switch(Capture->Timer_Resource)
{
case Timer1_Capture: Set_Timer1_Clock_Source_for_Capture_Compare_Modes_CCP1_Module(); break;
case Timer3_Capture: Set_Timer3_Clock_Source_for_Capture_Compare_Modes_CCP_Modules(); break;
default: ret = R_NOK;
}
Capture_Interrupt_Handler = Capture->Interrupt_Handler_Capture;
CCP_Module_Interrupt_Init();
SET_BIT(TRISC,_TRISC_RC2_POSN);
Set_CCP_Module_Mode(Capture->Mode);
ret = R_OK;    
}
return ret;
}
/**
 * @brief de-initialize CPP Module
 * @param reference Capture Mode configurations @ref Capture_Mode_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Capture_Mode_DeInit(Capture_Mode_t *Capture)
{
STD_Return_t ret = R_NOK;
if(NULL == Capture)
{
ret = R_NOK;    
}
else
{
CCP_Clear_Flag();
CCP_Interrupt_Disable();
ret = R_OK;    
}
return ret;    
}

/**
 * @brief Read Capture Mode Registers
 * @param value
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Capture_Mode_Read_value(uint16 *value)
{
STD_Return_t ret = R_NOK;
uint8 l_high_value = 0,l_low_value = 0;
if(NULL == value)
{
ret = R_NOK;    
}
else
{
l_low_value  = CCPR1L;
l_high_value = CCPR1H;
*value = (uint16)((l_high_value << 8) + l_low_value);
ret = R_OK;    
}
return ret;     
}
/* capture Mode interrupt service Routine */
void Capture_ISR()
{
CCP_Clear_Flag();
if(Capture_Interrupt_Handler)
{
Capture_Interrupt_Handler();    
}
}

#endif


#if (CCP_Module_Works_in == Compare_Mode)
static void (* Compare_Interrupt_Handler)(void) = NULL;
/**
 * @brief initialize CPP Module in Compare Mode
 * @param reference Compare Mode configurations @ref Compare_Mode_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Compare_Mode_Init(Compare_Mode_t *Compare)
{
STD_Return_t ret = R_NOK;
if(NULL == Compare)
{
ret = R_NOK;    
}
else
{
Set_CCP_Module_Mode(CCP_Module_Disable);
Set_CCP_Module_Mode(Compare->Mode);
switch(Compare->Timer_Resource)
{
case Timer1_Compare: Set_Timer1_Clock_Source_for_Capture_Compare_Modes_CCP1_Module(); break;
case Timer3_Compare: Set_Timer3_Clock_Source_for_Capture_Compare_Modes_CCP_Modules(); break;
default: ret = R_NOK;
}

Compare_Interrupt_Handler = Compare->Interrupt_Handler_Compare;
CCP_Module_Interrupt_Init();
ret = pin_initialize(&(Compare->CCP_Pin));
Set_CCP_Module_Mode(Compare->Mode);
ret = R_OK;    
}
return ret;
}
/**
 * @brief de-initialize CPP Module
 * @param reference Compare Mode configurations @ref Compare_Mode_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Capture_Mode_DeInit(Compare_Mode_t *Compare)
{
STD_Return_t ret = R_NOK;
if(NULL == Compare)
{
ret = R_NOK;    
}
else
{
CCP_Clear_Flag();
CCP_Interrupt_Disable();
ret = R_OK;    
}
return ret;    
}

/**
 * @brief write value to Compare Mode Register
 * @param value
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t Compare_Mode_write_value(uint16 value)
{
STD_Return_t ret = R_NOK;
if(NULL == value)
{
ret = R_NOK;    
}
else
{
CCPR1L = (uint8)(value) ;
CCPR1H = (uint8)((value) >> 8) ;
ret = R_OK;    
}
return ret;     
}
/* compare mode interrupt service routine*/
void Compare_ISR()
{
CCP_Clear_Flag();
if(Compare_Interrupt_Handler)
{
Compare_Interrupt_Handler();    
}
}

#endif







#if (CCP_Module_Works_in == PWM_Mode)
static void (* PWM1_Interrupt_Handler)(void) = NULL;
/**
 * @brief initialize CCP Module to work in PWM Mode
 * @param reference PWM configurations @ref PWM1_Mode_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t PWM1_Mode_Init(PWM1_Mode_t *PWM1)
{
STD_Return_t ret = R_NOK;
if(NULL == PWM1)
{
ret = R_NOK;    
}
else
{
Set_CCP_Module_Mode(CCP_Module_Disable);
Set_CCP_Module_Mode(PWM1->Mode);
PWM1_Interrupt_Handler = PWM1->Interrupt_Handler_PWM1;
CCP_Module_Interrupt_Init();
ret = pin_initialize(&(PWM1->CCP_Pin));
Set_CCP_Module_Mode(PWM1->Mode);
ret = R_OK;    
}
return ret;
}

static void (* PWM2_Interrupt_Handler)(void) = NULL;
STD_Return_t PWM2_Mode_Init(PWM2_Mode_t *PWM2)
{
STD_Return_t ret = R_NOK;
if(NULL == PWM2)
{
ret = R_NOK;    
}
else
{
Set_CCP2_Module_Mode(CCP_Module_Disable);
Set_CCP2_Module_Mode(PWM2->Mode);
PWM2_Interrupt_Handler = PWM2->Interrupt_Handler_PWM2;
ret = pin_initialize(&(PWM2->CCP_Pin));
Set_CCP2_Module_Mode(PWM2->Mode);
ret = R_OK;    
}
return ret;
}


/**
 * @brief de-initialize CPP Module
 * @param reference PWM configurations @ref PWM1_Mode_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t PWM1_Mode_DeInit(PWM1_Mode_t *PWM1)
{
STD_Return_t ret = R_NOK;
if(NULL == PWM1)
{
ret = R_NOK;    
}
else
{
CCP_Clear_Flag();
CCP_Interrupt_Disable();
ret = R_OK;    
}
return ret;    
}

/**
 * @brief select signal frequency
 * @param frequency value
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t PWM1_Mode_write_Frequency(uint16 value)
{
STD_Return_t ret = R_NOK;
if(NULL == value)
{
ret = R_NOK;    
}
else
{
PR2 = value;
ret = R_OK;    
}
return ret;     
}

/**
 * @brief select signal Duty Cycle for PWM1 Mode
 * @param duty cycle value
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t PWM1_Mode_write_Duty_Cycle(uint16 value)
{
STD_Return_t ret = R_NOK;
uint16 l_duty_cycle = 0;
if(NULL == value)
{
ret = R_NOK;    
}
else
{
l_duty_cycle = (uint16)(((float)(100.0-value) / 100.0) * (PR2 + 1.0) * 4.0);
CCP1CONbits.DC1B = (uint8)((value) && 0X0003);    
CCPR1L =  (uint8)(l_duty_cycle >> 2); 
ret = R_OK;    
}
return ret;      
}

/* compare mode interrupt service routine */
void Compare_ISR()
{
CCP_Clear_Flag();
if(PWM1_Interrupt_Handler)
{
PWM1_Interrupt_Handler();    
}
}
/**
 * @brief select signal Duty Cycle for PWM2 Mode
 * @param duty cycle value
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t PWM2_Mode_write_Duty_Cycle(uint16 value)
{
STD_Return_t ret = R_NOK;
if(NULL == value)
{
ret = R_NOK;    
}
else
{
CCPR2L =  (uint8)(value);
CCP2CON = (uint8)(value>>8);    
    
ret = R_OK;    
}
return ret;       
}




#endif
/**
 * @brief initialize CCP Module interrupt
 * @param reference PWM configurations @ref PWM1_Mode_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t CCP_Module_Interrupt_Init(void)
{
STD_Return_t ret = R_NOK;
Peripheral_Interrupt_Enable(); 
CCP_Clear_Flag();   
CCP_Interrupt_Enable();
#if (Interrupt_Priority_Enable == 1)
if(Capture->Priority == High_Piority)
{
CCP_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(Capture->Priority == Low_Priority)
{
CCP_Interrupt_Low_Priority();
Global_Low_Priority_Interrupt_Enable
}
else{/*Nothing*/}
#else
Global_Interrupt_Enable();
#endif

ret = R_OK;    
return ret;   
}