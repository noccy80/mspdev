//******************************************************************************
//  MSP430x26x Demo - Software Port Interrupt Service on P1.4 from LPM4
//
//  Description: A hi "TO" low transition on P1.4 will trigger P1_ISR which,
//  toggles P1.0. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
//  with the LED removed, all unused Px.x configured as output or inputs
//  pulled high or low, and ensure the P1.4 interrupt input does not float.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F261x/241x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.4         P1.0|-->LED
//     \|/
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h" 

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  P1IE |= 0x010;                            // P1.4 interrupt enabled
  P1IES |= 0x010;                           // P1.4 Hi/Lo edge
  P1IFG &= ~0x010;                          // P1.4 IFG cleared

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1OUT ^= 0x01;                            // P1.0 = toggle
  P1IFG &= ~0x010;                          // P1.4 IFG cleared
}

