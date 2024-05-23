/* 
 * File:   mcal_interrupt_manager.c
 * Author: Amr Ali
 *
 * Created on March 18, 2024, 8:04 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_flag = 1,RB5_flag = 1,RB6_flag = 1,RB7_flag = 1;
#if (Interrupt_Priority_Enable == 1)
/* user __interrupt attribute to make compiler save address of this function in high priority vector */
void __interrupt() InterruptManagerHigh(void)
{
if((Interrupt_Enable == INTCONbits.RBIE) && (1 == RB4_flag)&& (Interrupt_occur == INTCONbits.RBIF) && (High == PORTBbits.RB4)) 
{
RB4_flag = 0;
RB4_ISR(0);    
}
else{/*Nothing*/}

if((Interrupt_Enable == INTCONbits.RBIE) && (0 == RB4_flag) && (Interrupt_occur == INTCONbits.RBIF) && (Low == PORTBbits.RB4)) 
{
RB4_flag = 1;
RB4_ISR(1);    
}
else{/*Nothing*/}
}
/* user __interrupt attribute to make compiler save address of this function in low priority vector */
void __interrupt(low_priority) InterruptManagerLow(void)
{

}
#else
/* user __interrupt attribute to make compiler save address of this function in high priority vector */
void __interrupt() InterruptManager(void) 
{
if((Interrupt_Enable == INTCONbits.INT0IE) && (Interrupt_occur == INTCONbits.INT0IF))
{
INT0_ISR();    
}
else{/*Nothing*/}
if((Interrupt_Enable == INTCON3bits.INT1IE) && (Interrupt_occur == INTCON3bits.INT1IF))
{
INT1_ISR();    
}
else{/*Nothing*/}
if((Interrupt_Enable == INTCON3bits.INT2IE) && (Interrupt_occur == INTCON3bits.INT2IF))
{
INT2_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == INTCONbits.RBIE) && (Interrupt_occur == INTCONbits.RBIF) && (Low == PORTBbits.RB4) && (RB4_flag == 0)) 
{
RB4_flag = 1;
RB4_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == INTCONbits.RBIE) && (Interrupt_occur == INTCONbits.RBIF) && (High == PORTBbits.RB4) && (RB4_flag == 1))
{
RB4_flag = 0;
RB4_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == INTCONbits.RBIE) && (Interrupt_occur == INTCONbits.RBIF) && (High == PORTBbits.RB5) && (RB5_flag == 1))
{
RB5_flag = 0;
RB5_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == INTCONbits.RBIE) && (Interrupt_occur == INTCONbits.RBIF) && (Low == PORTBbits.RB5) && (RB5_flag == 0)) 
{
RB5_flag = 1;
RB5_ISR();    
}
else{/*Nothing*/}
if((Interrupt_Enable == INTCONbits.RBIE) && (Interrupt_occur == INTCONbits.RBIF) && (High == PORTBbits.RB6) && (RB6_flag == 1)) 
{
RB6_flag = 0;
RB6_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == INTCONbits.RBIE) && (Interrupt_occur == INTCONbits.RBIF) && (Low == PORTBbits.RB6) && (RB6_flag == 0)) 
{
RB6_flag = 1;
RB6_ISR();    
}
else{/*Nothing*/}


if((Interrupt_Enable == INTCONbits.RBIE) && (Interrupt_occur == INTCONbits.RBIF) && (High == PORTBbits.RB7) && (RB7_flag == 1)) 
{
RB7_flag = 0;
RB7_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == INTCONbits.RBIE) && (Interrupt_occur == INTCONbits.RBIF) && (Low == PORTBbits.RB7) && (RB7_flag == 0)) 
{
RB7_flag = 1;   
RB7_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == PIE1bits.ADIE) && (Interrupt_occur == PIR1bits.ADIF)) 
{
ADC_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == INTCONbits.TMR0IE) && (Interrupt_occur == INTCONbits.TMR0IF)) 
{
Timer0_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == PIE1bits.TMR1IE) && (Interrupt_occur == PIR1bits.TMR1IF)) 
{
Timer1_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == PIE1bits.TMR2IE) && (Interrupt_occur == PIR1bits.TMR2IF)) 
{
Timer2_ISR();    
}
else{/*Nothing*/}

if((Interrupt_Enable == PIE2bits.TMR3IE) && (Interrupt_occur == PIR2bits.TMR3IF)) 
{
Timer3_ISR();    
}
else{/*Nothing*/}

#if (CCP_Module_Works_in == Capture_Mode)

if((Interrupt_Enable == PIE1bits.CCP1IE) && (Interrupt_occur == PIR1bits.CCP1IF)) 
{
Capture_ISR();    
}
else{/*Nothing*/}

#endif

#if (CCP_Module_Works_in == Compare_Mode)

if((Interrupt_Enable == PIE1bits.CCP1IE) && (Interrupt_occur == PIR1bits.CCP1IF)) 
{
Compare_ISR();    
}
else{/*Nothing*/}

#endif

if((Interrupt_Enable == PIE1bits.TXIE) && (Interrupt_occur == PIR1bits.TXIF)) 
{  
EUSART_Tx_ISR(); 
}
else{/*Nothing*/}
if((Interrupt_Enable == PIE1bits.RCIE) && (Interrupt_occur == PIR1bits.RCIF)) 
{  
EUSART_Rx_ISR(); 
}
else{/*Nothing*/}

if((Interrupt_Enable == PIE2bits.BCLIE) && (Interrupt_occur == PIR2bits.BCLIF)) 
{  
Collision_ISR(); 
}
else{/*Nothing*/}

if((Interrupt_Enable == PIE1bits.SSPIE) && (Interrupt_occur == PIR1bits.SSPIF)) 
{  
I2C_ISR(); 
}
else{/*Nothing*/}

}
#endif