//******************************************************************************
//   MSP430x26x Demo - Basic Clock, LPM3 Using WDT ISR, VLO ACLK
//
//   Description: This program operates MSP430 normally in LPM3, pulsing P1.0
//   ~ 6 second intervals. WDT ISR used to wake-up system. All I/O configured
//   as low outputs to eliminate floating inputs. Current consumption does
//   increase when LED is powered on P1.0. Demo for measuring LPM3 current.
//   ACLK = VLO/2, MCLK = SMCLK = default DCO ~1.045MHz
//
//            MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

volatile unsigned int i;

void main(void)
{
  // interval: [VLO_freq/(2*32768)] ~ 1/6Hz = 6 second interval
  WDTCTL = WDT_ADLY_1000;                   // WDT 1s*4 interval timer, ACLK
  BCSCTL1 |= DIVA_1;                        // ACLK/2
  BCSCTL3 |= LFXT1S_2;                      // ACLK = VLO
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2SEL = 0;                                // All P2.x GPIO function
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

  while(1)
  {
    __bis_SR_register(LPM3_bits + GIE);     // Enter LPM3, enable interrupts
    P1OUT |= 0x01;                          // Set P1.0 LED on
    for (i = 20000; i > 0; i--);            // Delay
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
  }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
  __bic_SR_register_on_exit(LPM3_bits);     // Clear LPM3 bits from 0(SR)
}
