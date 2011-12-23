//******************************************************************************
//   MSP430x47xx Demo - Write a Word to Port B (Port9+Port10)
//
//   Description: Writes a Word(FFFFh) to Port B and stays in LPM4
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430x47xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
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

  PBDIR |= 0x0FFFF;                         // PB.x output
  PBOUT |= 0x0FFFF;                         // Set all PB pins HI

  _BIS_SR(LPM4_bits + GIE);                 // LPM4
}
