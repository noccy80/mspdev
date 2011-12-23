//******************************************************************************
//  MSP430x11x1 Demo - Software Port Interrupt Service on P2.0 from LPM4
//
//  Description: A hi/low transition on P2.0 will trigger P2_ISR which,
//  toggles P1.0. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
//  with the LED removed, all unused P1.x/P2.x configured as output or inputs
//  pulled high or low, and ensure the P2.0 interrupt input does not float.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k
//
//                MSP430F1121
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--| P2.0        P1.0|-->LED
//     \|/
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include <msp430x11x1.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  P1DIR |= 0x01;                        // Set P1.0 to output direction
  P2IE |= 0x01;                         // P2.0 interrupt enabled
  P2IES |= 0x01;                        // P2.0 Hi/lo edge
  P2IFG &= ~0x01;                       // P2.0 IFG cleared

  _BIS_SR(LPM4_bits + GIE);             // Enter LPM4 w/interrupt
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
  P1OUT ^= 0x01;                        // P1.0 = toggle
  P2IFG &= ~0x01;                       // P2.0 IFG clearedf
}

