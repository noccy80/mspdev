/*  Description: Toggle P1.0 using software and Timer0_A0 ISR. Timer0_A is       */
/*  configured for up mode, thus the timer overflows when TA0R counts to         */
/*  TA0CCR0. In this example, TA0CCR0 is loaded with 20000.                      */                   
/*                                                                               */
/****************************Timer_A0*********************************************/
/*                                                                               */
/* Requirements: Download to EEPROM                                              */
/*                                                                               */
/*                               +----L092---+                                   */
/*                               |*1      14 |                                   */
/*                               | 2      13 |                                   */
/*                               | 3      12 |                                   */
/*                               | 4      11 |                                   */
/*                               | 5      10 |                                   */
/*       P1.0 -Toggle Output  <- | 6       9 |                                   */
/*                               | 7       8 |                                   */
/*                               +-----------+                                   */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/

#include "msp430l092.h"  

void main(void)
{
  	WDTCTL = WDTPW + WDTHOLD;                // Stop WDT 

  	P1DIR |= BIT0 + BIT1;                    // P1.0 Output direction   
  	P1SEL0 |=  BIT1 ;                
  	P1SEL1 |=  BIT1 ;    
    
/************************/
/* Setup CCS            */
/* SMCLK = LFCLK        */
/************************/
    	CCSCTL0 = CCSKEY;                       // Unlock CCS
    	CCSCTL5 = 0;                            // Set the Dividers for SMCLK to 1
    	CCSCTL4 |= SELM_1;                      // Select LFCLK/VLO as the source for ACLK, MCLK, and SMCLK   
    	CCSCTL0_H |= 0xFF;                      // Lock CCS
/* Lock by writing to upper byte */
  
  	TA0CCTL0 = CCIE;                        // TA0CCR0 interrupt enabled
  	TA0CCR0 = 20000;				    // Set value for TA0CCR0
 	TA0CTL = TASSEL_2 + MC_1;               // SMCLK, upmode

  __bis_SR_register(LPM0_bits + GIE);         // Enter LPM0 w/ interrupt
}

// Timer0_A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  	P1OUT ^= BIT0;                          // Toggle P1.0
}

