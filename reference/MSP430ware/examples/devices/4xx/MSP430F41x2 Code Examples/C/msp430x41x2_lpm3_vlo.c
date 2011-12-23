//******************************************************************************
//   MSP430x41x2 Demo - Basic Clock, LPM3 Using WDT ISR, VLO ACLK
//
//   Description: This program operates MSP430 normally in LPM3, pulsing P5.1
//   ~ 3 second intervals. WDT ISR used to wake-up system. All I/O configured
//   as low outputs to eliminate floating inputs. Current consumption does
//   increase when LED is powered on P5.1. Demo for measuring LPM3 current.
//   ACLK = VLO, MCLK = SMCLK = default DCO ~1.045MHz
//
//               MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include "msp430x41x2.h"

volatile unsigned int i;

void main(void)
{
  // interval: [VLO_freq/(32768)] ~ 3 second interval
  WDTCTL = WDT_ADLY_1000;                   // WDT interval timer, ACLK
  FLL_CTL2 |= LF1XT1S_2;                    // LFXT1 = VLOCLK
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P3DIR = 0xFF;                             // All P3.x outputs
  P3OUT = 0;                                // All P3.x reset
  P4DIR = 0xFF;                             // All P4.x outputs
  P4OUT = 0;                                // All P4.x reset
  P5DIR = 0xFF;                             // All P5.x outputs
  P5OUT = 0;                                // All P5.x reset
  P6DIR = 0xFF;                             // All P6.x outputs
  P6OUT = 0;                                // All P6.x reset
  P7DIR = 0xFF;                             // All P7.x outputs
  P7OUT = 0;                                // All P7.x reset
  
  while(1)
  {
    __bis_SR_register(LPM3_bits + GIE);     // Enter LPM3, enable interrupts
    P5OUT |= 0x02;                          // Set P5.1 LED on
    for (i = 20000; i > 0; i--);            // Delay
    P5OUT &= ~0x02;                         // Clear P5.1 LED off
  }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
  __bic_SR_register_on_exit(LPM3_bits);     // Clear LPM3 bits from 0(SR)
}
