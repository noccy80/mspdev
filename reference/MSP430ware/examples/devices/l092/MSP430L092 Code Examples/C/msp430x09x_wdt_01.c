/****************************WDT Toggle Port Pin *********************************/
/*Toggle P1.0 using software timed by WDT ISR                                    */ 
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
	/* ACLK = VLO  ~20kHz   */
	/************************/
	CCSCTL0 = CCSKEY;                 // Unlock CCS
	CCSCTL4 |= SELA_1;                // Select LFCLK/VLO as the ACLK source          
        CCSCTL5 = DIVA_0;             // Divide fACLK by 1 ~20Khz
	CCSCTL0_H |= 0xFF;                // Lock CCS
	/* Lock by writing to upper byte */
	
	
    WDTCTL = WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1;  // WDT ACLK Delay Interval specify                  
    SFRIE1 |= WDTIE;                      // Enable WDT interrupt

    __bis_SR_register(LPM0_bits + GIE);   // Enter LPM0 w/ interrupts enabled
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= BIT0;                          // Toggle P1.0 using exclusive-OR
}
 