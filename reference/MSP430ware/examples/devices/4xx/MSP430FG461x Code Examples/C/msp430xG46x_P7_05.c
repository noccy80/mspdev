//******************************************************************************
//   MSP430xG46x Demo - Write a byte to Port 7
//
//   Description: Writes a byte(FFh) to Port 7 and stays in LPM4
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430xG461x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
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

  P7DIR |= 0x0FF;                           // P7.x output
  P7OUT |= 0x0FF;                           // Set all P7 pins HI

  _BIS_SR(LPM4_bits + GIE);                 // LPM4
}
