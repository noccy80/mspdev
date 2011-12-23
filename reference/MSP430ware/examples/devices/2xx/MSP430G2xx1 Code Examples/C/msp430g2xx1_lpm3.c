//******************************************************************************
//  MSP430G2xx1 Demo - Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
//
//  Description: This program operates MSP430 normally in LPM3, pulsing P1.0
//  at 4 second intervals. WDT ISR used to wake-up system. All I/O configured
//  as low outputs to eliminate floating inputs. Current consumption does
//  increase when LED is powered on P1.0. Demo for measuring LPM3 current.
//  ACLK = LFXT1/4 = 32768/4, MCLK = SMCLK = default DCO ~ 800kHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//
//           MSP430G2xx1
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************


#include <msp430g2231.h>

void main(void)
{
  BCSCTL1 |= DIVA_2;                        // ACLK/4
  WDTCTL = WDT_ADLY_1000;                   // WDT 1s/4 interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset

  while(1)
  {
    int i;
    P1OUT |= 0x01;                          // Set P1.0 LED on
    for (i = 5000; i>0; i--);               // Delay
    P1OUT &= ~0x01;                         // Reset P1.0 LED off
    _BIS_SR(LPM3_bits + GIE);               // Enter LPM3
  }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
    _BIC_SR_IRQ(LPM3_bits);                 // Clear LPM3 bits from 0(SR)
}
