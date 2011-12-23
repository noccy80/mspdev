//******************************************************************************
//  MSP430x41x2 Demo - Software Port Interrupt Service on P1.4 from LPM4
//
//  Description: A hi to low transition on P1.4 will trigger P1_ISR which,
//  toggles P5.1. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
//  with the LED removed, all unused Px.x configured as output or inputs
//  pulled high or low, and ensure the P1.4 interrupt input does not float.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430x41x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.4         P5.1|-->LED
//     \|/
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include  <msp430x41x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  P5OUT &= ~0x02;
  P1IE |= 0x010;                            // P1.4 interrupt enabled
  P1IES |= 0x010;                           // P1.4 Hi/Lo edge
  P1IFG &= ~0x010;                          // P1.4 IFG cleared

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P5OUT ^= 0x02;                            // P5.1 = toggle
  P1IFG &= ~0x010;                          // P1.4 IFG cleared
}

