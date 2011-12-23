//******************************************************************************
//  Description: Toggle P1.0 using software and Timer0_A1 ISR. Toggles every
//  1000 SMCLK cycles. SMCLK provides clock source for TA0CLK.
//  During the Timer0_A1 ISR, P1.0 is toggled and 1000 clock cycles are added to
//  TA0CCR0. Timer0_A1 ISR is triggered every 1000 cycles. CPU is normally off and
//  used only during Timer0_A1 ISR. Proper use of the TA0IV interrupt vector generator
//  is demonstrated.
/****************************Timer_A0*********************************************/
/*                                                                               */
/*                                                                               */
/*                                                                               */
/*                               +----L092---+                                   */
/*                               |*1      14 |                                   */
/*                               | 2      13 |                                   */
/*                               | 3      12 |                                   */
/*                               | 4      11 |                                   */
/*                               | 5      10 |                                   */
/*     P1.0 -Toggle Output  <-   | 6       9 |                                   */
/*     P1.1 SMCLK~ 1Mhz     <-   | 7       8 |                                   */
/*                               +-----------+                                   */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/

#include "msp430l092.h"  

void main(void)
{
  	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  	P1DIR |= BIT0 + BIT1;                     // P1.0 output direction       
  	P1SEL0 |=  BIT1 ;                
  	P1SEL1 |=  BIT1 ;    
    
/***************************/
/* Setup CCS               */
/* SMCLK = HFCLK           */
/***************************/
    	CCSCTL0 = CCSKEY;                       	// Unlock CCS
    while (SFRIFG1 & OFIFG)                 	// Oscillator Flag(s)?
  {
    	CCSCTL7 = 0;                            	// Clear HF & LF OSC fault flags
    	SFRIFG1 = 0;                            	// Clear OFIFG  
  }  
    	CCSCTL4 = SELS_0;                      	// Select HFCLK/DCO as the source for SMCLK   
    	CCSCTL5 = DIVS_0;                      	// Set the Dividers for SMCLK to 1
    	CCSCTL0_H |= 0xFF;                     	// Lock CCS
/* Lock by writing to upper byte */
  
  
  	TA0CCTL1 = CCIE;                          // TA0CCR1 interrupt enabled
  	TA0CCR1 = 1000;					// Set value for TA0CCR1
  	TA0CTL = TASSEL_2 + MC_2;                 // SMCLK, Contmode

  __bis_SR_register(LPM0_bits + GIE);       	// Enter LPM0 w/ interrupt
}

// Timer0_A1 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt  void Timer0_A1_ISR(void)
{
  switch (__even_in_range(TA0IV, 14))       	// Efficient switch-implementation
  {
    case  2:                                	// TA0CCR1
      P1OUT ^= BIT0;                        	// Toggle P1.0
      TA0CCR1 += 1000;                        	// Add Offset to TA0CCR1
      break;
    case  4: break;                         	// TACCR2 not used
    case  6: break;                         	// Reserved
    case  8: break;                         	// Reserved
    case 10: break;                         	// Reserved   
    case 12: break;                         	// Reserved
    case 14: break;                         	// Overflow not used
  }
}
