/* 
 * File:   mcal_interrupt_manager.h
 * Author: Kimo Store
 *
 * Created on March 18, 2024, 8:04 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H 
#define	MCAL_INTERRUPT_MANAGER_H
#include "mcal_external_interrupt_config.h"
#include "../Interal_Interrupts/mcal_internal_interrupt.h"
#include "../CCP/mcal_ccp_gen_cfg.h"
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR();
void RB5_ISR();
void RB6_ISR();
void RB7_ISR();

void ADC_ISR(void);
void Timer0_ISR(void);
void Timer1_ISR(void);
void Timer2_ISR(void);
void Timer3_ISR(void);
void Capture_ISR(void);
void Compare_ISR(void);

void EUSART_Tx_ISR(void);
void EUSART_Rx_ISR(void);

void Collision_ISR(void); 
void I2C_ISR(void);  
#endif	/* MCAL_INTERRUPT_MANAGER_H */

