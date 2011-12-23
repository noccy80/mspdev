//******************************************************************************
//  MSP430F22x4 Demo - Software Toggle P1.0, MCLK = VLO/8
//
//  Description; Pulse P1.0 with a 1/100 active duty cycle using software.
//  Ultra-low frequency ~ 1.5kHz, ultra-low power active mode demonstrated.
//  ACLK = VL0, MCLK = VLO/8 ~1.5kHz, SMCLK = n/a
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

volatile unsigned int i;                    // volatile to prevent optimization

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  BCSCTL3 |= LFXT1S_2;                      // LFXT1 = VLO
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  __bis_SR_register(SCG1 + SCG0);           // Stop DCO
  BCSCTL2 |= SELM_3 + DIVM_3;               // MCLK = LFXT1/8
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2SEL = 0;                                // All P2.x GPIO function
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P3DIR = 0xFF;                             // All P3.x outputs
  P3OUT = 0;                                // All P3.x reset
  P4DIR = 0xFF;                             // All P4.x outputs
  P4OUT = 0;                                // All P4.x reset

  for (;;)
  {
    P1OUT |= 0x01;                          // P1.0 set
    for (i = 10; i > 0; i--);               // Delay 1x
    P1OUT &= ~0x01;                         // P1.0 reset
    for (i = 1000; i > 0; i--);             // Delay 100x
  }
}
