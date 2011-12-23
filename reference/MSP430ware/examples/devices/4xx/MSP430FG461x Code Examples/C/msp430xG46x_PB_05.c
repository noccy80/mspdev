//******************************************************************************
//   MSP430xG46x Demo - Write a Word to Port B (Port9+Port10)
//
//   Description: Writes a Word(FFFFh) to Port B and stays in LPM4
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430xG46x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
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

  PBDIR |= 0x0FFFF;                         // PB.x output
  PBOUT |= 0x0FFFF;                         // Set all PB pins HI

  _BIS_SR(LPM4_bits + GIE);                 // LPM4
}
