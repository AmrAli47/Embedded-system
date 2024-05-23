/* 
 * File:   mcal_adc.c
 * Author: Amr Ali
 *
 * Created on March 21, 2024, 9:47 PM
 */

#include "mcal_adc.h"
   
void (*ADC_Handler)(void) = NULL;

static STD_Return_t ADC_Disable(ADC_t *ADC);
static STD_Return_t ADC_Enable(ADC_t *ADC);
static STD_Return_t ADC_Select_Voltage(ADC_t *ADC);
static STD_Return_t ADC_Select_Acqusition_Time(ADC_t *ADC);
static STD_Return_t ADC_Select_Clock(ADC_t *ADC);
static STD_Return_t ADC_Select_Channel(ADC_Channel_t channel);
static STD_Return_t ADC_Select_Result_Format(ADC_t *ADC);
static STD_Return_t ADC_Set_Interrupt_Handler(ADC_t *ADC);

/**
 * @brief initialize ADC Module
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t ADC_Init(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
ret = ADC_Disable(ADC);
ret = ADC_Select_Voltage(ADC);        
ret = ADC_Select_Acqusition_Time(ADC);        
ret = ADC_Select_Clock(ADC);       
ret = ADC_Select_Result_Format(ADC); 
ret = ADC_Set_Interrupt_Handler(ADC);
ret = ADC_Enable(ADC);        
ret = R_OK;    
}
return ret;
}

/**
 * @brief de-initialize ADC Module
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t ADC_DeInit(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
ADC_Module_Disable();    
#if (Interrupt_Feature_Enable == 1)
ADC_Clear_Flag();
ADC_Interrupt_Disable();
#endif    
ret = R_OK;    
}
return ret;    
}


/**
 * @brief Disable ADC Module
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t ADC_Disable(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
ADC_Module_Disable();
ret = R_OK;    
}
return ret;    
}

/**
 * @brief Enable ADC Module
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t ADC_Enable(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
ADC_Module_Enable();
ret = R_OK;    
}
return ret;    
}


/**
 * @brief select reference voltage
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t ADC_Select_Voltage(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
if(ADC->Voltage_Reference == voltage_Reference_Enable)
{
ADC_Voltage_Reference_Enable();        
}
else if(ADC->Voltage_Reference == voltage_Reference_Disable)
{
ADC_Voltage_Reference_Disable();        
}
else
{
ADC_Voltage_Reference_Disable();    
}
ret = R_OK;    
}
return ret;     
}

/**
 * @brief select Acqusition Time 
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t ADC_Select_Acqusition_Time(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
ADC_Set_Acquisition_Time(ADC->ACQ_Time);
ret = R_OK;    
}
return ret;      
}
/**
 * @brief select ADC Clock 
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t ADC_Select_Clock(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
ADC_Set_Clock(ADC->Clock);
ret = R_OK;    
}
return ret;      
}

/**
 * @brief select result format
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t ADC_Select_Result_Format(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
if(ADC->Result_Format == Left_Justified)
{
ADC_Result_Left_Jusitifed();        
}
else if(ADC->Result_Format == Right_Justified)
{
ADC_Result_Right_Jusitifed();        
}
else
{
ADC_Result_Right_Jusitifed();    
}
ret = R_OK;    
}
return ret;     
}


/**
 * @brief select ADC Channel
 * @param ADC Channel @ref ADC_Channel_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t ADC_Select_Channel(ADC_Channel_t channel)
{
STD_Return_t ret = R_NOK;
switch(channel)
{
case ADC_Channel_0:  SET_BIT(TRISA,_TRISA_RA0_POSN); break;
case ADC_Channel_1:  SET_BIT(TRISA,_TRISA_RA1_POSN); break;
case ADC_Channel_2:  SET_BIT(TRISA,_TRISA_RA2_POSN); break;
case ADC_Channel_3:  SET_BIT(TRISA,_TRISA_RA3_POSN); break;
case ADC_Channel_4:  SET_BIT(TRISA,_TRISA_RA5_POSN); break;
case ADC_Channel_5:  SET_BIT(TRISE,_TRISE_RE0_POSN); break;
case ADC_Channel_6:  SET_BIT(TRISE,_TRISE_RE1_POSN); break;
case ADC_Channel_7:  SET_BIT(TRISE,_TRISE_RE2_POSN); break;
case ADC_Channel_8:  SET_BIT(TRISB,_TRISB_RB2_POSN); break;
case ADC_Channel_9:  SET_BIT(TRISB,_TRISB_RB3_POSN); break;
case ADC_Channel_10: SET_BIT(TRISB,_TRISB_RB1_POSN); break;
case ADC_Channel_11: SET_BIT(TRISB,_TRISB_RB4_POSN); break;
case ADC_Channel_12: SET_BIT(TRISB,_TRISB_RB0_POSN); break;
default : ret = R_NOK;
}
ret = R_OK;
return ret;      
}

/**
 * @brief initialize AD interrupt
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t ADC_Interrupt(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
Peripheral_Interrupt_Enable(); 
ADC_Clear_Flag();   
ADC_Interrupt_Enable();
#if (Interrupt_Priority_Enable == 1)
if(ADC->Priority == High_Piority)
{
ADC_Interrupt_High_Priority();
Global_High_Priority_Interrupt_Enable();
}
else if(ADC->Priority == Low_Priority)
{
ADC_Interrupt_Low_Priority();
Global_Low_Priority_Interrupt_Enable();
}
else{/*Nothing*/}
#else
Global_Interrupt_Enable();
#endif

ret = R_OK;    
}
return ret; 
}


/**
 * @brief read the result (read output digital value)
 * @param reference ADC configurations @ref ADC_t
 * @param conversion result
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t ADC_Get_Conversion_Result(ADC_t *ADC,uint16 *Conversion_Result)
{
STD_Return_t ret = R_NOK;
if((NULL == ADC) || (NULL == Conversion_Result))
{
ret = R_NOK;
}
else
{
if(ADC->Result_Format == Left_Justified)
{
*Conversion_Result = (uint16)(((ADRESH << 8)+(ADRESL)) >> 6);      
}
else if(ADC->Result_Format == Right_Justified)
{
*Conversion_Result = (uint16)((ADRESH << 8)+(ADRESL));    
}
else
{
*Conversion_Result = (uint16)((ADRESH << 8)+(ADRESL)); 
}
ret = R_OK;    
}
return ret;     
}


/**
 * @brief start conversion (Blocking)
 * @param reference ADC configurations @ref ADC_t
 * @param ADC Channel @ref ADC_Channel_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t ADC_Start_Conversion_Blocking(ADC_t *ADC,ADC_Channel_t channel)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
ret = ADC_Select_Channel(channel);
ADC_Select_Ch(channel);
ADC_Start_Conversion();
while(ADCON0bits.GODONE);
ret = R_OK;    
}
return ret;     
}

/**
 * @brief start conversion (unblocking based on interrupt)
 * @param reference ADC configurations @ref ADC_t
 * @param ADC Channel @ref ADC_Channel_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t ADC_Start_Conversion_unblocking(ADC_t *ADC,ADC_Channel_t channel)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
ADC_Clear_Flag(); 
ADC_Select_Ch(channel);
ret = ADC_Select_Channel(channel);
ADC_Start_Conversion();
ret = R_OK;    
}
return ret;     
}

/**
 * @brief set AD interrupt handler
 * @param reference ADC configurations @ref ADC_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t ADC_Set_Interrupt_Handler(ADC_t *ADC)
{
STD_Return_t ret = R_NOK;
if(NULL == ADC)
{
ret = R_NOK;
}
else
{
ADC_Handler = ADC->ADC_Interrupt_Handler;
ret = R_OK;    
}
return ret;    
}

void ADC_ISR(void)
{
ADC_Clear_Flag();    
ADC_Handler();    
}
