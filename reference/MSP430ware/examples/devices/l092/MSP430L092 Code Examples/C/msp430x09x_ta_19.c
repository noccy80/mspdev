//******************************************************************************
//  Description: This program generates two PWM outputs on P1.5,6 using
//  Timer0_A3 configured for up/down mode. The value in TA0CCR0, 128, defines the
//  PWM period/2 and the values in TA0CCR1 and TA0CCR2 the PWM duty cycles. Using
//  ~1MHz SMCLK as TA0CLK. 
/****************************Timer_A0*********************************************/
/*                                                                               */
/*                                                                               */
/*                                                                               */
/*              +----L092---+                                                    */
/*              |*1      14 |     -> P1.6 TA0.1 output   3.9 kHz                 */
/*              | 2      13 |     -> P1.5 TA0.2 output   3.9 kHz                 */
/*              | 3      12 |                                                    */
/*              | 4      11 |                                                    */
/*              | 5      10 |                                                    */
/*              | 6       9 |                                                    */
/*              | 7       8 |                                                    */
/*              +-----------+                                                    */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/
#include "msp430L092.h"  

void main(void)
{
  	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  	P1SEL0 |= BIT1 + BIT5 + BIT6;
  	P1SEL1 |= BIT1 + BIT5;
  	P1DIR  |= BIT1 + BIT5 + BIT6;  
  
 /***************************/
 /* Setup CCS               */
 /* SMCLK = HFCLK/1  ~1MHz  */
 /***************************/
    	CCSCTL0 = CCSKEY;                       	// Unlock CCS
    while (SFRIFG1 & OFIFG)                 	// Oscillator Flag(s)?
  {
    	CCSCTL7 = 0;                            	// Clear HF & LF OSC fault flags
    	SFRIFG1 = 0;                            	// Clear OFIFG  
  }  
    	CCSCTL4 = SELS_0;             	// Select HFCLK/DCO as the source for SMCLK   
    	CCSCTL5 = DIVS_0;              	// Set the Dividers for SMCLK to 1
    	CCSCTL0_H |= 0xFF;                      	// Lock CCS
 /* Lock by writing to upper byte */
  
  	TA0CCR0 = 128;                            // PWM Period/2
  	TA0CCTL1 = OUTMOD_6;                      // TA0CCR1 toggle/set
  	TA0CCR1 = 32;                             // TA0CCR1 PWM duty cycle
  	TA0CCTL2 = OUTMOD_6;                      // TA0CCR2 toggle/set
  	TA0CCR2 = 96;                             // TA0CCR2 PWM duty cycle
  	TA0CTL = TASSEL_2 + MC_3;                 // SMCLK, up-down mode

  __bis_SR_register(LPM0_bits);             	// Enter LPM0
}

