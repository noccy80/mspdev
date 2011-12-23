/* Description: This program demonstrates how to configure ACLK, MCLK, and SMCLK */
/* to use the CLKIN as the clock source.                                         */
/****************************Timer_A0*********************************************/
/*  Requirements: Oscilloscope to measure frequencies                            */
/*                                                                               */
/*                                                                               */
/*                               +----L092---+                                   */
/*                               |*1      14 |                                   */
/*                               | 2      13 |                                   */
/*                               | 3      12 |  -> P1.4 MCLK                     */
/*                               | 4      11 |                                   */
/*                               | 5      10 |                                   */
/*     CLKIN                ->   | 6       9 |                                   */
/*     P1.1 SMCLK           <-   | 7       8 |                                   */
/*                               +-----------+                                   */
/*                                                                               */
/*  D.Dang/D.Archbold/D.Szmulewicz                                               */
/*  Texas Instruments Inc.                                                       */
/*  Built with IAR Version 5.10.4                                                */
/*********************************************************************************/
#include "msp430l092.h"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;

   // Setup Port 1 to output ACLK, SMCLK, and MCLK
   // P1.0 = CLKIN -> P1DIR.0 = 0; P1SEL0.0 = 0; P1SEL1.0 = 0;
   // P1.1 = SMCLK-> P1DIR.1 = 1; P1SEL0.1 = 1; P1SEL1.1 = 1;
   // P1.4 = MCLK -> P1DIR.4 = 1; P1SEL0.4 = 1; P1SEL1.4 = 1;
    
    P1DIR  |=  BIT1 + BIT4;               
    P1SEL0 |=  BIT1 + BIT4;                
    P1SEL1 |=  BIT1 + BIT4;               
	
	/************************/
	/* Setup CCS            */
	/* ACLK = CLKIN/1       */
      /* MCLK =  CLKIN/1      */
      /* SMCLK =  CLKIN/1     */
	/************************/
    CCSCTL0 = CCSKEY;                       // Unlock CCS
 
    while (SFRIFG1 & OFIFG)                 // Oscillator Flag(s)?
  {
    CCSCTL7 = 0;                            // Clear HF & LF OSC fault flags
    SFRIFG1 = 0;                            // Clear OFIFG  
  }
    CCSCTL5 = DIVA_0 + DIVM_0 + DIVS_0;     // Set the Dividers for ACLK, MCLK, and SMCLK to 1
    CCSCTL4 |= SELA_2 + SELM_2 + SELS_2;    // Select CLKIN/XOSC as the source for ACLK, MCLK, and SMCLK                 
    CCSCTL0_H |= 0xFF;                      // Lock CCS
	/* Lock by writing to upper byte */
	
    while(1);

}


 