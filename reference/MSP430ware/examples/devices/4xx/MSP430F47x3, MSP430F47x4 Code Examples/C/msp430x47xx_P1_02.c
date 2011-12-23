//******************************************************************************
//    MSP430x47xx Demo - Software Port Interrupt on P1.4 from LPM4
//
//   Description: A hi/low transition on P1.4 will trigger P1_ISR which,
//   toggles P5.1. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
//   with the LED removed, all unused P1.x/P2.x configured as output or inputs
//   pulled high or low, and ensure the P1.4 interrupt input does not float.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430x47xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//      /|\   |                 |
//       --o--|P1.4         P5.1|-->LED
//      \|/
//
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x47x4.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P5DIR |= BIT1;                           // P5.1 output
  P1IE |= BIT4;                            // P1.4 Interrupt enabled
  P1IES |= BIT4;                           // P1.4 hi/low edge
  P1IFG &= ~BIT4;                          // P1.4 IFG Cleared

  _BIS_SR(LPM4_bits + GIE);                 // LPM4, enable interrupts

}


// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR (void)
{
  P5OUT ^= BIT1;                            // P5.1 = toggle
  P1IFG &= ~BIT4;                          // P1.4 IFG Cleared
}
