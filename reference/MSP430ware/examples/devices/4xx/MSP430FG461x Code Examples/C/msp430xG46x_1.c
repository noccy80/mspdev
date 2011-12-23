//******************************************************************************
//   MSP430xG46x Demo - Software Toggle P5.1
//
//   Description: Toggle P5.1 by xor'ing P5.1 inside of a software loop.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430xG461x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P5.1|-->LED
//
//   K. Quiring/M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P5DIR |= 0x02;                            // P5.1 output

  while(1)
  {
    P5OUT ^= 0x02;
    for(i=50000;i>0;i--);                   // Delay
  }
}
