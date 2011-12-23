//******************************************************************************
//  MSP430L092 Demo - Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
//
//  Description: This program operates MSP430 normally in LPM3, pulsing P1.0
//  WDT ISR used to wake-up system. P1.0 I/O configured
//  as low output to eliminate floating inputs. Current consumption does
//  increase when P1.0 is set. Demo for measuring LPM3 current.
//  ACLK = LFXT1/4 = 32768/4, MCLK = SMCLK = default DCO ~1.2MHz
//  //* External watch crystal on XIN XOUT is required for ACLK *//
//
//           MSP430F21x2
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->Output
//
//  D.Dang/ D.Archbold/ D.Szmulewicz                                           
//  Texas Instruments Inc.                                                 
// Built with IAR Version 5.10.4                                                    
//****************************************************************************
#include "msp430l092.h"

volatile unsigned int i;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;  
    P1DIR |= BIT0;
    CCSCTL0 = CCSKEY;                       // Unlock CCS
	CCSCTL4 |= SELA_1;                      // Select LFCLK/VLO as the ACLK source          
    CCSCTL5 &= ~DIVA_2;                     // Divide fACLK by 4
	CCSCTL0_H |= 0xFF;                      // Lock CCS
	/* Lock by writing to upper byte */
	
	
    WDTCTL = WDT_ADLY_16;                   // WDT SMCLK Delay Interval specify                  
    SFRIE1 |= WDTIE;                        // Enable WDT interrupt
  while(1)
  {
    __bis_SR_register(LPM3_bits + GIE);     // Enter LPM3, enable interrupts
    P1OUT |= 0x01;                          // Set P1.0 
    for (i = 4; i > 0; i--);                // Delay
    P1OUT &= ~0x01;                         // Clear P1.0 
  }
}

#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  __bic_SR_register_on_exit(LPM3_bits);     // Clear LPM3 bits from 0(SR)
}
