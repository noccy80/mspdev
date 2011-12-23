//******************************************************************************
//  Description: This program generates two PWM outputs on P1.5/1.6 using
//  Timer0_A3 configured for up/down mode. The value in TA0CCR0, 128, defines the
//  PWM period/2 and the values in TA0CCR1 and TA0CCR2 the PWM duty cycles.
/****************************Timer_A0*********************************************/
/*                                                                               */
/*                                                                               */
/*                                                                               */
/*                        +----L092---+                                          */
/*                        |*1      14 |     -> P1.6 TA0.1 output                 */
/*                        | 2      13 |     -> P1.5 TA0.2 output                 */
/*                        | 3      12 |                                          */
/*                        | 4      11 |                                          */
/*                        | 5      10 |                                          */
/*    1Mhz  CLKIN  ->     | 6       9 |                                          */
/*                        | 7       8 |                                          */
/*                        +-----------+                                          */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/
#include "msp430L092.h"  

void main(void)
{
 
  	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
   // P1.1 = SMCLK -> P1DIR.1 = 1; P1SEL0.1 = 1; P1SEL1.1 = 1;
   // P1.5 = TA0.2 -> P1DIR.5 = 1; P1SEL0.5 = 1; P1SEL1.5 = 1; 500Hz
   // P1.6 = TA0.1 -> P1DIR.6 = 1; P1SEL0.6 = 1; P1SEL1.6 = 0; 50Hz
  
  	P1SEL0 |= BIT1 + BIT5 + BIT6;
  	P1SEL1 |= BIT1 + BIT5;
  	P1DIR  |= BIT1 + BIT5 + BIT6;  
  
   /***************************/
   /* Setup CCS               */
   /* ACLK = CLKIN            */
   /* SMCLK = HFCLK/1  ~1MHz  */
   /***************************/
   	CCSCTL0 = CCSKEY;                       	// Unlock CCS
    while (SFRIFG1 & OFIFG)                 	// Oscillator Flag(s)?
  {
    	CCSCTL7 = 0;                            	// Clear HF & LF OSC fault flags
    	SFRIFG1 = 0;                            	// Clear OFIFG  
  }  
    	CCSCTL4 = SELA_2;       // Select CLKIN as the ACLK source   
    	CCSCTL5 = DIVA_0;       // Set the CLK Dividers to 1
    	CCSCTL0_H |= 0xFF;                      	// Lock CCS
   
    /* Lock by writing to upper byte */
  	TA0CCR0 = 128;                            // PWM Period/2
  	TA0CCTL1 = OUTMOD_6;                      // TA0CCR1 toggle/set
  	TA0CCR1 = 32;                             // TA0CCR1 PWM duty cycle
  	TA0CCTL2 = OUTMOD_6;                      // TA0CCR2 toggle/set
  	TA0CCR2 = 96;                             // TA0CCR2 PWM duty cycle
  	TA0CTL = TASSEL_1 + MC_3;                 // ACLK, up-down mode

  __bis_SR_register(LPM0_bits);             	// Enter LPM0
}

