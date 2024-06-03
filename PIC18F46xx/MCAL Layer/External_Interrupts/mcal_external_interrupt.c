/* 
 * File:   external_interrupt.c
 * Author: Amr Ali
 *
 * Created on March 18, 2024, 5:59 PM
 */
#include "mcal_external_interrupt.h"
#include "../../ECU/LED/ecu_led.h"
 
/*---------------------INTx---------------------*/
void (* Interrupt_INT0_Handler)(void) = NULL;
void (* Interrupt_INT1_Handler)(void) = NULL;
void (* Interrupt_INT2_Handler)(void) = NULL;



static STD_Return_t interrupt_INTx_Enable(Interrupt_INTx_t *INTx);
static STD_Return_t interrupt_INTx_Disable(Interrupt_INTx_t *INTx);
static STD_Return_t interrupt_INTx_Edge_Init(Interrupt_INTx_t *INTx);
static STD_Return_t interrupt_INTx_Clear_Flag(Interrupt_INTx_t *INTx);
static STD_Return_t interrupt_INTx_Pin_Initialize(Interrupt_INTx_t *INTx);
static STD_Return_t interrupt_INTx_Set_Handler(Interrupt_INTx_t *INTx);
/*---------------------INTx---------------------*/

/*---------------------RBx---------------------*/
void (* Interrupt_RB4_Handler_Low)(void) = NULL;
void (* Interrupt_RB4_Handler_High)(void) = NULL;
void (* Interrupt_RB5_Handler_Low)(void) = NULL;
void (* Interrupt_RB5_Handler_High)(void) = NULL;
void (* Interrupt_RB6_Handler_Low)(void) = NULL;
void (* Interrupt_RB6_Handler_High)(void) = NULL;
void (* Interrupt_RB7_Handler_Low)(void) = NULL;
void (* Interrupt_RB7_Handler_High)(void) = NULL;



static STD_Return_t interrupt_RBx_Pin_Initialize(Interrupt_RBx_t *RBx);
static STD_Return_t interrupt_RBx_Enable(Interrupt_RBx_t *RBx);
static STD_Return_t interrupt_RBx_Disable(Interrupt_RBx_t *RBx);
static STD_Return_t interrupt_RBx_Clear_Flag(Interrupt_RBx_t *RBx);
static STD_Return_t interrupt_RBx_Set_Handler(Interrupt_RBx_t *RBx);

/*---------------------RBx---------------------*/

/**
 * @brief initial external interrupt INx 
 * @param reference to interrupt configuration @Interrupt_INTx_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t interrupt_INTx_Init(Interrupt_INTx_t *INTx)
{
STD_Return_t ret = R_NOK;
if(NULL == INTx)
{
ret = R_NOK;
}
else
{
ret = interrupt_INTx_Disable(INTx);
ret = interrupt_INTx_Clear_Flag(INTx);
ret = interrupt_INTx_Pin_Initialize(INTx);
ret = interrupt_INTx_Set_Handler(INTx);
ret = interrupt_INTx_Edge_Init(INTx);
ret = interrupt_INTx_Enable(INTx);
ret = R_OK;
}
return ret;
}

/**
 * @brief de-initialize external interrupt INx 
 * @param reference to interrupt configuration @Interrupt_INTx_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t interrupt_INTx_DeInit(Interrupt_INTx_t *INTx)
{
STD_Return_t ret = R_NOK;
if(NULL == INTx)
{
ret = R_NOK;
}
else
{
ret = interrupt_INTx_Disable(INTx); 
ret = interrupt_INTx_Clear_Flag(INTx);
ret = R_OK;
}
return ret;    
}
/**
 * @brief initialize external interrupt RBx 
 * @param reference to interrupt configuration @Interrupt_INTx_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t interrupt_RBx_Init(Interrupt_RBx_t *RBx)
{
STD_Return_t ret = R_NOK;
if(NULL == RBx)
{
ret = R_NOK;
}
else
{
ret = interrupt_RBx_Disable(RBx);
ret = interrupt_RBx_Clear_Flag(RBx);
ret = interrupt_RBx_Pin_Initialize(RBx);
ret = interrupt_RBx_Set_Handler(RBx);
ret = interrupt_RBx_Enable(RBx);
ret = R_OK;
}
return ret;    
}
/**
 * @brief de-initialize external interrupt RBx 
 * @param reference to interrupt configuration @Interrupt_INTx_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
STD_Return_t interrupt_RBx_DeInit(Interrupt_RBx_t *RBx)
{
STD_Return_t ret = R_NOK;
if(NULL == RBx)
{
ret = R_NOK;
}
else
{
ret = interrupt_RBx_Disable(RBx);
ret = interrupt_RBx_Clear_Flag(RBx);
ret = R_OK;
}
return ret;    
}

/**
 * @brief Enable external interrupt RBx 
 * @param reference to interrupt configuration @Interrupt_INTx_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t interrupt_INTx_Enable(Interrupt_INTx_t *INTx)
{
STD_Return_t ret = R_NOK;
if(NULL == INTx)
{
ret = R_NOK;
}
else
{
#if (Interrupt_Priority_Enable == 1)
Priority_Feature_Enable();
Global_High_Priority_Interrupt_Enable();
Global_Low_Priority_Interrupt_Enable();
Peripheral_Interrupt_Enable();
switch(INTx->Source)
{
case Interrupt_INT1: 
if(High_Piority == INTx->Priority)
{
INT1_High_Priority();    
}
else if(Low_Priority == INTx->Priority)
{
INT1_Low_Priority();    
}
else {/*Nothing*/}
break;
case Interrupt_INT2: 
if(High_Piority == INTx->Priority)
{
INT2_High_Priority();    
}
else if(Low_Priority == INTx->Priority)
{
INT2_Low_Priority();    
}
else {/*Nothing*/}
break;    
default : ret = R_NOK; 
}
#else
Global_Interrupt_Enable();
Peripheral_Interrupt_Enable();
Priority_Feature_Disable();
switch(INTx->Source)
{
case Interrupt_INT0: INT0_Interrupt_Enable(); break;
case Interrupt_INT1: INT1_Interrupt_Enable(); break;    
case Interrupt_INT2: INT2_Interrupt_Enable(); break;
default : ret = R_NOK;    
}
#endif
ret = R_OK;
}
return ret;     
}
/**
 * @brief Disable external interrupt RBx 
 * @param reference to interrupt configuration @Interrupt_INTx_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t interrupt_INTx_Disable(Interrupt_INTx_t *INTx)
{
STD_Return_t ret = R_NOK;
if(NULL == INTx)
{
ret = R_NOK;
}
else
{
switch(INTx->Source)
{
case Interrupt_INT0: INT0_Interrupt_Disable();   break;
case Interrupt_INT1: INT1_Interrupt_Disable();   break;
case Interrupt_INT2: INT2_Interrupt_Disable();  break;
default : ret = R_NOK; 
}    
ret = R_OK;
}
return ret; 
}
/**
 * @brief configure on which edge (rising or falling) interrupt will be triggered 
 * @param reference to interrupt configuration @Interrupt_INTx_t
  * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t interrupt_INTx_Edge_Init(Interrupt_INTx_t *INTx)
{
STD_Return_t ret = R_NOK;
if(NULL == INTx)
{
ret = R_NOK;
}
else
{
switch(INTx->Source)
{
case Interrupt_INT0: 
if(Rising_Edge_interrupt == INTx->Edge)
{
INT0_Rising_Edge();    
}
else if(Falling_Edge_interrupt == INTx->Edge)
{
INT0_Falling_Edge();
}
else{/*Nothing*/}      
break;
case Interrupt_INT1:
if(Rising_Edge_interrupt == INTx->Edge)
{
INT1_Rising_Edge();    
}
else if(Falling_Edge_interrupt == INTx->Edge)
{
INT1_Falling_Edge();
}
else{/*Nothing*/}     
break;
case Interrupt_INT2:
if(Rising_Edge_interrupt == INTx->Edge)
{
INT2_Rising_Edge();    
}
else if(Falling_Edge_interrupt == INTx->Edge)
{
INT2_Falling_Edge();  
break;
default : ret = R_NOK; 
}    
ret = R_OK;
}
}
return ret; 
}

/**
 * @brief clear interrupt flag
 * @param reference to interrupt configuration @Interrupt_INTx_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t interrupt_INTx_Clear_Flag(Interrupt_INTx_t *INTx)
{
STD_Return_t ret = R_NOK;
if(NULL == INTx)
{
ret = R_NOK;
}
else
{
switch(INTx->Source)
{
case Interrupt_INT0: INT0_Clear_Flag();   break;
case Interrupt_INT1: INT1_Clear_Flag();   break;
case Interrupt_INT2: INT2_Clear_Flag();  break;
default : ret = R_NOK; 
}    
ret = R_OK;
}
return ret;     
}


/**
 * @brief initialize External interrupt INx Pins
 * @param reference to interrupt configuration @Interrupt_INTx_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t interrupt_INTx_Pin_Initialize(Interrupt_INTx_t *INTx)
{
STD_Return_t ret = R_NOK;
if(NULL == INTx)
{
ret = R_NOK;
}
else
{
switch(INTx->Source)
{
case Interrupt_INT0: ret = pin_initialize(&(INTx->Interrupt_Pin));  break;
case Interrupt_INT1: ret = pin_initialize(&(INTx->Interrupt_Pin));  break;
case Interrupt_INT2: ret = pin_initialize(&(INTx->Interrupt_Pin));  break;
default : ret = R_NOK; 
}    
ret = R_OK;
}
return ret;     
}
/**
 * @brief set interrupt handler to execute a callback in application layer when interrupt is triggered
 * @param reference to interrupt configuration @Interrupt_INTx_t
 * @return status of the function 
 * R_OK: function succeeded to perform its action 
 * R_NOK: function failed to perform its action
 */
static STD_Return_t interrupt_INTx_Set_Handler(Interrupt_INTx_t *INTx)
{
STD_Return_t ret = R_NOK;
if(NULL == INTx)
{
ret = R_NOK;
}
else
{
switch(INTx->Source)
{
case Interrupt_INT0:   
Interrupt_INT0_Handler = INTx->Interrupt_Handler;    
break;
case Interrupt_INT1: 
Interrupt_INT1_Handler = INTx->Interrupt_Handler; 
break;
case Interrupt_INT2: 
Interrupt_INT2_Handler = INTx->Interrupt_Handler; 
break;
default : ret = R_NOK; 
}    
ret = R_OK;
}
return ret;
}
/* interrupt service routine for INT0*/
void INT0_ISR(void)
{
INT0_Clear_Flag();
Interrupt_INT0_Handler();
}
/* interrupt service routine for INT1*/
void INT1_ISR(void)
{
INT1_Clear_Flag();
Interrupt_INT1_Handler();
}
/* interrupt service routine for INT1*/
void INT2_ISR(void)
{
INT2_Clear_Flag();
Interrupt_INT2_Handler();
}



static STD_Return_t interrupt_RBx_Pin_Initialize(Interrupt_RBx_t *RBx)
{
STD_Return_t ret = R_NOK;
if(NULL == RBx)
{
ret = R_NOK;
}
else
{
switch(RBx->Interrupt_Pin.Pin_Number)
{
case Pin4: ret = pin_initialize(&(RBx->Interrupt_Pin)); break;
case Pin5: ret = pin_initialize(&(RBx->Interrupt_Pin)); break;
case Pin6: ret = pin_initialize(&(RBx->Interrupt_Pin)); break;
case Pin7: ret = pin_initialize(&(RBx->Interrupt_Pin)); break;
default : ret = R_NOK;    
}
ret = R_OK;
}
return ret;     
}
static STD_Return_t interrupt_RBx_Enable(Interrupt_RBx_t *RBx)
{
STD_Return_t ret = R_NOK;
if(NULL == RBx)
{
ret = R_NOK;
}
else
{
Peripheral_Interrupt_Enable();
RBx_Interrupt_Enable();
#if (Interrupt_Priority_Enable == 1)
if(High_Piority == RBx->Priority)
{
Global_High_Priority_Interrupt_Enable();
RBx_High_Priority();
}
else if(Low_Priority == RBx->Priority)
{
Global_Low_Priority_Interrupt_Enable(); 
RBx_Low_Priority();
}
else{/*Nothing*/}
#else
Global_Interrupt_Enable(); 
Priority_Feature_Disable();
#endif
ret = R_OK;
}
return ret;    
}
static STD_Return_t interrupt_RBx_Disable(Interrupt_RBx_t *RBx)
{
STD_Return_t ret = R_NOK;
if(NULL == RBx)
{
ret = R_NOK;
}
else
{
RBx_Interrupt_Disable();
ret = R_OK;
}
return ret;     
}

static STD_Return_t interrupt_RBx_Clear_Flag(Interrupt_RBx_t *RBx)
{
STD_Return_t ret = R_NOK;
if(NULL == RBx)
{
ret = R_NOK;
}
else
{
RBx_Clear_Flag();
ret = R_OK;
}
return ret;    
}


static STD_Return_t interrupt_RBx_Set_Handler(Interrupt_RBx_t *RBx)
{
STD_Return_t ret = R_NOK;
if(NULL == RBx)
{
ret = R_NOK;
}
else
{
switch(RBx->Interrupt_Pin.Pin_Number)
{
case Pin4: 
Interrupt_RB4_Handler_Low = RBx->Interrupt_Handler_Low;
Interrupt_RB4_Handler_High = RBx->Interrupt_Handler_High;
break;
case Pin5:
Interrupt_RB5_Handler_Low = RBx->Interrupt_Handler_Low;
Interrupt_RB5_Handler_High = RBx->Interrupt_Handler_High;
break;
case Pin6:  
Interrupt_RB6_Handler_Low = RBx->Interrupt_Handler_Low;
Interrupt_RB6_Handler_High = RBx->Interrupt_Handler_High;
break;
case Pin7: 
Interrupt_RB7_Handler_Low = RBx->Interrupt_Handler_Low;
Interrupt_RB7_Handler_High = RBx->Interrupt_Handler_High;
break;
default : ret = R_NOK;    
}
ret = R_OK;
}
return ret;     
}

void RB4_ISR()
{  
RBx_Clear_Flag();
if((Low == PORTBbits.RB4))
{
Interrupt_RB4_Handler_High();     
}
else if((High == PORTBbits.RB4))
{
Interrupt_RB4_Handler_Low();      
}
else{/*Nothing*/}  
}

void RB5_ISR()
{ 
RBx_Clear_Flag();
if((Low == PORTBbits.RB5))
{
Interrupt_RB5_Handler_High();     
}
else if((High == PORTBbits.RB5))
{
Interrupt_RB5_Handler_Low();      
}
else{/*Nothing*/}  
}

void RB6_ISR()
{ 
RBx_Clear_Flag();
if((Low == PORTBbits.RB6))
{
Interrupt_RB6_Handler_High();     
}
else if((High == PORTBbits.RB6))
{
Interrupt_RB6_Handler_Low();      
}
else{/*Nothing*/} 
}

void RB7_ISR()
{
RBx_Clear_Flag(); 
if((Low == PORTBbits.RB7))
{
Interrupt_RB7_Handler_High();     
}
else if((High == PORTBbits.RB7))
{
Interrupt_RB7_Handler_Low();      
}
else{/*Nothing*/} 
}
