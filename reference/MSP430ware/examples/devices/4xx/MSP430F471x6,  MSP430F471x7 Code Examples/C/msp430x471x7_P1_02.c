//******************************************************************************
//    MSP430x471xx Demo - Software Port Interrupt on P2.7 from LPM4
//
//   Description: A hi/low transition on P2.7 will trigger P1_ISR which,
//   toggles P5.1. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
//   with the LED removed, all unused P1.x/P2.x configured as output or inputs
//   pulled high or low, and ensure the P1.4 interrupt input does not float.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430x471xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//      /|\   |                 |
//       --o--|P2.7         P5.1|-->LED
//      \|/
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P5DIR |= BIT1;                           // P5.1 output
  P2IE |= BIT7;                            // P2.7 Interrupt enabled
  P2IES |= BIT7;                           // P2.7 hi/low edge
  P2IFG &= ~BIT7;                          // P2.7 IFG Cleared

  _BIS_SR(LPM4_bits + GIE);                 // LPM4, enable interrupts

}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR (void)
{
  P5OUT ^= BIT1;                            // P5.1 = toggle
  P2IFG &= ~BIT7;                          // P2.7 IFG Cleared
}
