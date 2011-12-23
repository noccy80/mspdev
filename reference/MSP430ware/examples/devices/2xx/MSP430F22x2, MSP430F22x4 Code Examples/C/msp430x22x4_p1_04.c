//******************************************************************************
//  MSP430F22x4 Demo - P1.2 Interrupt from LPM4 with Internal Pull-up
//
//  Description: A hi/low transition on P1.2 will trigger P1_ISR which,
//  toggles P1.0. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
//  with the LED removed, all unused Px.x configured as output or inputs
//  pulled high or low, and ensure the P1.2 interrupt input does not float.
//  Internal pullup enabled on P1.2.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |      R          |
//      --o--| P1.2-o      P1.0|-->LED
//     \|/
//
//  A. Dannenberg / W. Goh
//  Texas Instruments Inc.
//  November 2008
//  Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0x01;                             // P1.0 output, else input
  P1OUT = 0x04;                             // P1.2 pullup
  P1REN |= 0x04;                            // P1.2 pullup
  P1IE |= 0x04;                             // P1.2 interrupt enabled
  P1IES |= 0x04;                            // P1.2 Hi/lo edge
  P1IFG &= ~0x04;                           // P1.2 IFG cleared

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1OUT ^= 0x01;                            // P1.0 = toggle
  P1IFG &= ~0x04;                           // P1.2 IFG cleared
}
