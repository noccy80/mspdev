/****************************WDT Toggle Port Pin *********************************/
/*Toggle P1.0 using software timed by WDT ISR. LF-OSC ACLK                                     */ 
/*                                                                               */
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
    WDTCTL = WDTPW + WDTHOLD;
    
    P1DIR |= BIT0;                        // Set P1.0 to output direction
    P1OUT |= BIT0;                        // Output high on P1.0

	
	/************************/
	/* Setup CCS            */
	/* SMCLK = HFCLK        */
	/* MCLK = HFCLK/8       */
	/************************/
	CCSCTL0 = CCSKEY;                       // Unlock CCS
	CCSCTL4 |= SELS_0;                      // Select HFCLK / DCO as the SMCLK source          
        CCSCTL5 = DIVS_0;                     // Divide fSMCLK by 1
	CCSCTL0_H |= 0xFF;                      // Lock CCS
	/* Lock by writing to upper byte */
	
	
    WDTCTL = WDT_MDLY_0_5; // WDT SMCLK Delay Interval specify                  
    SFRIE1 |= WDTIE;                      // Enable WDT interrupt

    __bis_SR_register(LPM0_bits + GIE);   // Enter LPM0 w/ interrupts enabled
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= BIT0;                          // Toggle P1.0 using exclusive-OR
}