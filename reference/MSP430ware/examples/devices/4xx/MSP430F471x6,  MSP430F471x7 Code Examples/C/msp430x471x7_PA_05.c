//******************************************************************************
//   MSP430x471xx Demo - Write a Word to Port A (Port7+Port8)
//
//   Description: Writes a Word(FFFFh) to Port A and stays in LPM4
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//               MSP430x471xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
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

  PADIR |= 0x0FFFF;                         // PA.x output
  PAOUT |= 0x0FFFF;                         // Set all PA pins HI

  _BIS_SR(LPM4_bits + GIE);                 // LPM4
}
