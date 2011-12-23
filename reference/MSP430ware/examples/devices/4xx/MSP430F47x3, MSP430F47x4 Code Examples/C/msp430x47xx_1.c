//******************************************************************************
//   MSP430x47xx Demo - Software Toggle P5.1
//
//   Description: Toggle P5.1 by xor'ing P5.1 inside of a software loop.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430x47xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P5.1|-->LED
//
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x47x4.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P5DIR |= BIT1;                            // P5.1 output

  while(1)
  {
    P5OUT ^= BIT1;
    for(i=50000;i>0;i--);                   // Delay
  }
}
