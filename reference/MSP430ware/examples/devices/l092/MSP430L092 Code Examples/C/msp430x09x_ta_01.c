/*  Description: Toggle P1.0 using software and Timer0_A0 ISR. Toggles every     */
/*  1000 SMCLK cycles. SMCLK provides clock source for TA0CLK.                   */
/*  During the Timer0_A0 ISR, P1.0 is toggled and 1000 clock cycles are added to */                   
/*  TA0CCR0. Timer0_A0 ISR is triggered every 1000 cycles. CPU is normally off   */ 
/*  and used only during TA ISR.                                                 */
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
  WDTCTL = WDTPW + WDTHOLD;                   // Stop WDT
/*************************/
/* Setup Ports           */
/*************************/
  
  	P1OUT |= BIT0;                          // P1.0 output
  	P1DIR |= BIT0 + BIT1;                           
  	P1SEL0 |=  BIT1 ;                
  	P1SEL1 |=  BIT1 ;    
    
/************************/
/* Setup CCS            */
/* SMCLK = LFCLK        */
/************************/
    	CCSCTL0 = CCSKEY;                       // Unlock CCS
    	CCSCTL5 = 0;                            // Set the Dividers for SMCLK to 1
    	CCSCTL4 |= SELM_1 + SELS_1 + SELA_1;    // Select LFCLK/VLO as the source for ACLK, MCLK, and SMCLK   
    	CCSCTL0_H |= 0xFF;                      // Lock CCS
/* Lock by writing to upper byte */


  
  	TA0CCTL0 = CCIE;                        // TA0CCR0 interrupt enabled
  	TA0CCR0 = 1000;				    // Set value for TA0CCR0
 	TA0CTL = TASSEL_2 + MC_2 + TACLR;       // SMCLK, cont. mode

  __bis_SR_register(LPM0_bits + GIE);         // Enter LPM0 w/ interrupt: CPU, MCLK are disabled
                                              // ACLK is active, SMCLK is active, and HFOSC is on
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{

  	P1OUT ^= BIT0;                          // Toggle P1.0
 
}

