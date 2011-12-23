//******************************************************************************
//  MSP430x26x Demo - Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK
//
//  Description: This program operates MSP430 normally in LPM3, pulsing P1.0
//  at 4 second intervals. WDT ISR used to wake-up system. All 6 I/O ports are 
//  configured as low outputs to eliminate floating inputs. Current consumption 
//  does increase when LED is powered on P1.0. Demo for measuring LPM3 current.
//  ACLK = LFXT1/4 = 32768/4, MCLK = SMCLK = default DCO ~1.045MHz
//  //* External watch crystal on XIN XOUT is required for ACLK *//
//
//        MSP430F261x/241x
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

volatile unsigned int i;

void main(void)
{
  BCSCTL1 |= DIVA_2;                        // ACLK/4 = 8.192 kHz
  WDTCTL = WDT_ADLY_1000;                   // WDT-ALCK Delay:1s*4 interval timer
                                            // interval period= 4sec=1/4Hz(freq)
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
  
  while(1)
  {
    __bis_SR_register(LPM3_bits + GIE);     // Enter LPM3, enable interrupts
    P1OUT |= 0x01;                          // Set P1.0 LED on
    for (i = 20000; i > 0; i--);            // Delay
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
  }
}

#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  //Wake up the system
  __bic_SR_register_on_exit(LPM3_bits);     // Clear LPM3 bits from 0(SR)
}
