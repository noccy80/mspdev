//******************************************************************************
//  MSP430F543xA Demo - Software Port Interrupt Service on P1.4 from LPM4 with
//                    Internal Pull-up Resistance Enabled
//
//  Description: A hi "TO" low transition on P1.4 will trigger P1_ISR which,
//  toggles P1.0. P1.4 is internally enabled to pull-up. Normal mode is
//  LPM4 ~ 0.1uA. LPM4 current can be measured with the LED removed, all
//  unused Px.x configured as output or inputs pulled high or low.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F5438A
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.4         P1.0|-->LED
//     \|/
//
//   M. Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54xA.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  P1REN |= 0x10;                            // Enable P1.4 internal resistance
  P1OUT |= 0x10;                            // Set P1.4 as pull-Up resistance
  P1IE |= 0x10;                             // P1.4 interrupt enabled
  P1IES |= 0x10;                            // P1.4 Hi/Lo edge
  P1IFG &= ~0x10;                           // P1.4 IFG cleared

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
  __no_operation();                         // For debugger
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1OUT ^= 0x01;                            // P1.0 = toggle
  P1IFG &= ~0x010;                          // P1.4 IFG cleared
}

