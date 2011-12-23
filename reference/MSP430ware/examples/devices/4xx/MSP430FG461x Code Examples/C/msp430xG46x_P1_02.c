//******************************************************************************
//   MSP430xG46x Demo - Software Port Interrupt on P1.4 from LPM4
//
//   Description: A hi/low transition on P1.4 will trigger P1_ISR which,
//   toggles P5.1. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
//   with the LED removed, all unused P1.x/P2.x configured as output or inputs
//   pulled high or low, and ensure the P2.0 interrupt input does not float.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430xG461x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//      /|\   |                 |
//       --o--|P1.4         P5.1|-->LED
//      \|/
//
//   K. Quiring/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P5DIR |= 0x002;                           // P5.1 output
  P1IE |= 0x010;                            // P1.4 Interrupt enabled
  P1IES |= 0x010;                           // P1.4 hi/low edge
  P1IFG &= ~0x010;                          // P1.4 IFG Cleared

  _BIS_SR(LPM4_bits + GIE);                 // LPM4, enable interrupts

}


// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port1_ISR (void)
{
  P5OUT ^= 0x02;                            // P5.1 = toggle
  P1IFG &= ~0x010;                          // P1.4 IFG Cleared
}
