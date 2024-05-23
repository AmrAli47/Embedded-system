/* 
 * File:   mcal_internal_interrupt.h
 * Author: Amr Ali
 *
 * Created on March 21, 2024, 11:34 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

#include "../External_Interrupts/mcal_external_interrupt_config.h"

// ADC interrupt Enable
#define ADC_Interrupt_Enable()     (PIE1bits.ADIE = 1)
// ADC interrupt Disable
#define ADC_Interrupt_Disable()    (PIE1bits.ADIE = 0)

// ADC Clear Flag
#define ADC_Clear_Flag()           (PIR1bits.ADIF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set ADC as High Priority
#define ADC_Interrupt_High_Priority()     (IPR1bits.ADIP = 1)
// Set ADC as Low Priority
#define ADC_Interrupt_Low_Priority()       (IPR1bits.ADIP = 0)


#endif



// Timer 0 interrupt Enable
#define Timer0_Interrupt_Enable()     (INTCONbits.TMR0IE = 1)
// Timer 0 interrupt Disable
#define Timer0_Interrupt_Disable()    (INTCONbits.TMR0IE = 0)

// Timer 0 Clear Flag
#define Timer0_Clear_Flag()           (INTCONbits.TMR0IF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set Timer 0 as High Priority
#define Timer0_Interrupt_High_Priority()     (INTCON2bits.TMR0IP = 1)
// Set Timer 0 as Low Priority
#define Timer0_Interrupt_Low_Priority()      (INTCON2bits.TMR0IP = 0)


#endif



// Timer 1 interrupt Enable
#define Timer1_Interrupt_Enable()     (PIE1bits.TMR1IE = 1)
// Timer 1 interrupt Disable
#define Timer1_Interrupt_Disable()    (PIE1bits.TMR1IE = 0)

// Timer 1 Clear Flag
#define Timer1_Clear_Flag()           (PIR1bits.TMR1IF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set Timer 1 as High Priority
#define Timer1_Interrupt_High_Priority()     (IPR1bits.TMR1IP = 1)
// Set Timer 1 as Low Priority
#define Timer1_Interrupt_Low_Priority()      (IPR1bits.TMR1IP = 0)


#endif


// Timer 2 interrupt Enable
#define Timer2_Interrupt_Enable()     (PIE1bits.TMR2IE = 1)
// Timer 2 interrupt Disable
#define Timer2_Interrupt_Disable()    (PIE1bits.TMR2IE = 0)

// Timer 2 Clear Flag
#define Timer2_Clear_Flag()           (PIR1bits.TMR2IF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set Timer 2 as High Priority
#define Timer2_Interrupt_High_Priority()     (IPR1bits.TMR2IP = 1)
// Set Timer 2 as Low Priority
#define Timer2_Interrupt_Low_Priority()      (IPR1bits.TMR2IP = 0)


#endif


// Timer 3 interrupt Enable
#define Timer3_Interrupt_Enable()     (PIE2bits.TMR3IE = 1)
// Timer 3 interrupt Disable
#define Timer3_Interrupt_Disable()    (PIE2bits.TMR3IE = 0)

// Timer 3 Clear Flag
#define Timer3_Clear_Flag()           (PIR2bits.TMR3IF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set Timer 3 as High Priority
#define Timer3_Interrupt_High_Priority()     (IPR2bits.TMR3IP = 1)
// Set Timer 3 as Low Priority
#define Timer3_Interrupt_Low_Priority()      (IPR2bits.TMR3IP = 0)


#endif

// CCP interrupt Enable
#define CCP_Interrupt_Enable()     (PIE1bits.CCP1IE = 1)
// CCP interrupt Disable
#define CCP_Interrupt_Disable()    (PIE1bits.CCP1IE = 0)

// CCP Clear Flag
#define CCP_Clear_Flag()           (PIR1bits.CCP1IF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set CCP as High Priority
#define CCP_Interrupt_High_Priority()     (IPR1bits.CCP1IP = 1)
// Set CCP as Low Priority
#define CCP_Interrupt_Low_Priority()      (IPR1bits.CCP1IP = 0)


#endif


// EUSART Transmit Interrupt Enable
#define EUSART_Transmit_Interrupt_Enable()     (PIE1bits.TXIE = 1)
// EUSART Transmit Interrupt Disable
#define EUSART_Transmit_Interrupt_Disable()    (PIE1bits.TXIE = 0)

// EUSART Clear Flag (this flag is cleared when TXREG is written)
#define EUSART_Transmit_Clear_Flag()           (PIR1bits.TXIF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set EUSART Transmit Interrupt  as High Priority
#define EUSART_Transmit_Interrupt_High_Priority()     (IPR1bits.TXIP = 1)
// Set EUSART Transmit Interrupt  as Low Priority
#define EUSART_Transmit_Interrupt_Low_Priority()      (IPR1bits.TXIP = 0)


#endif

// EUSART Receive Interrupt Enable
#define EUSART_Receive_Interrupt_Enable()     (PIE1bits.RCIE = 1)
// EUSART Receive Interrupt Disable
#define EUSART_Receive_Interrupt_Disable()    (PIE1bits.RCIE = 0)

// EUSART Clear Flag (this flag is cleared when RCREG is read)
#define EUSART_Receive_Clear_Flag()           (PIR1bits.RCIF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set EUSART Receive Interrupt  as High Priority
#define EUSART_Receive_Interrupt_High_Priority()     (IPR1bits.RCIP = 1)
// Set EUSART Receive Interrupt  as Low Priority
#define EUSART_Receive_Interrupt_Low_Priority()      (IPR1bits.RCIP = 0)

#endif


// MSSP Interrupt Enable
#define MSSP_Interrupt_Enable()               (PIE1bits.SSPIE = 1)
// MSSP Interrupt Disable
#define MSSP_Interrupt_Disable()              (PIE1bits.SSPIE = 0)

// MSSP Flag 
#define MSSP_Clear_Flag()                     (PIR1bits.SSPIF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set MSSP Interrupt  as High Priority
#define MSSP_Interrupt_High_Priority()        (IPR1bits.SSPIP = 1)
// Set MSSP Interrupt  as Low Priority
#define MSSP_Interrupt_Low_Priority()         (IPR1bits.SSPIP = 0)

#endif


// Bus Collision Interrupt Enable
#define Bus_Collision_Interrupt_Enable()      (PIE2bits.BCLIE = 1)
// Bus Collision Interrupt Disable
#define Bus_Collision_Interrupt_Disable()     (PIE2bits.BCLIE = 0)

// Bus Collision Flag 
#define Bus_Collision_Clear_Flag()            (PIR2bits.BCLIF = 0)

#if (Interrupt_Priority_Enable == 1)
// Set Bus Collision Interrupt  as High Priority
#define Bus_Collision_Interrupt_High_Priority()        (IPR2bits.BCLIP = 1)
// Set Bus Collision Interrupt  as Low Priority
#define Bus_Collision_Interrupt_Low_Priority()         (IPR2bits.BCLIP = 0)

#endif


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

