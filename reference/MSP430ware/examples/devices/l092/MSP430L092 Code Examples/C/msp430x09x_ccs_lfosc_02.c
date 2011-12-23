/* Description: This program demonstrates how to configure ACLK, MCLK, and SMCLK */
/* to use the LF clock source.                                                   */
/****************************Timer_A0*********************************************/
/*  Requirements: Oscilloscope to measure clock frequencies                      */
/*                                                                               */
/*                                                                               */
/*                               +----L092---+                                   */
/*                               |*1      14 |                                   */
/*                               | 2      13 |                                   */
/*                               | 3      12 |  -> P1.4 MCLK~ 17.9kHz            */
/*                               | 4      11 |                                   */
/*                               | 5      10 |                                   */
/*     P1.0 ACLK~ 4.5 kHz   <-   | 6       9 |                                   */
/*     P1.1 SMCLK~ 9kHz     <-   | 7       8 |                                   */
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
	/* ACLK = LFCLK/4       */
      /* MCLK = LFCLK/1       */
      /* SMCLK = LFCLK/2      */
	/************************/
    CCSCTL0 = CCSKEY;                       // Unlock CCS
    CCSCTL5 = DIVA_2 + DIVM_0 + DIVS_1;     // Set the Dividers for ACLK to 4, MCLK to 1, and SMCLK to 2
    CCSCTL4 |= SELA_1 + SELM_1 + SELS_1;    // Select LFCLK/VLO as the source for ACLK, MCLK, and SMCLK                 
    CCSCTL0_H |= 0xFF;                      // Lock CCS
	/* Lock by writing to upper byte */
	
    while(1);

}


 