/* Description: This program demonstrates how to configure ACLK, MCLK, and SMCLK */
/* to use the HF clock source.                                                   */
/****************************Timer_A0*********************************************/
/*  Requirements: Oscilloscope                                                   */
/*                                                                               */
/*                                                                               */
/*                               +----L092---+                                   */
/*                               |*1      14 |                                   */
/*                               | 2      13 |                                   */
/*                               | 3      12 |  -> P1.4 MCLK ~250kHz             */
/*                               | 4      11 |                                   */
/*                               | 5      10 |                                   */
/*     P1.0 ACLK ~62.5kHz <-     | 6       9 |                                   */
/*     P1.1 SMCLK ~1MHz   <-     | 7       8 |                                   */
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
   // P1.0 = ACLK -> P1DIR.0 = 1; P1SEL0.0 = 1; P1SEL1.0 = 1;
   // P1.1 = SMCLK-> P1DIR.1 = 1; P1SEL0.1 = 1; P1SEL1.1 = 1;
   // P1.4 = MCLK -> P1DIR.4 = 1; P1SEL0.4 = 1; P1SEL1.4 = 1;
    
    P1DIR  |= BIT0 + BIT1 + BIT4;               
    P1SEL0 |= BIT0 + BIT1 + BIT4;                
    P1SEL1 |= BIT0 + BIT1 + BIT4;               
	
	/************************/
	/* Setup CCS            */
	/* ACLK = HFCLK/16      */
      /* MCLK = HFCLK/4       */
      /* SMCLK = HFCLK/1      */
	/************************/
    
    CCSCTL0 = CCSKEY;                       // Unlock CCS  
    
    while (SFRIFG1 & OFIFG)                 // Oscillator Flag(s)?
  {
    CCSCTL7 = 0;                            // Clear HF & LF OSC fault flags
    SFRIFG1 = 0;                            // Clear OFIFG  
  }
  
    CCSCTL4 = SELA_0 + SELM_0 + SELS_0;    // Select HFCLK/DCO as the source for ACLK, MCLK, and SMCLK  
    CCSCTL5 = DIVA_4 + DIVM_2 + DIVS_0;     // Set the Dividers for ACLK to 16, MCLK to 4, and SMCLK to 1
    CCSCTL0_H |= 0xFF;                      // Lock CCS
	
        /* Lock by writing to upper byte */
	
  while(1);

}


 