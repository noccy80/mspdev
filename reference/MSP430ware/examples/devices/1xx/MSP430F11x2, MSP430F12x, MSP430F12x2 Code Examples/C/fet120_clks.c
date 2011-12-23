//******************************************************************************
//  MSP-FET430P120 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
//
//  Description: Buffer ACLK on P2.0, default SMCLK(DCO) on P1.4 and MCLK/10 on
//  P1.1.  To measure SMCLK on P1.4 with the FET, use "Release JTAG on Go"
//  in the debugger to have access to the port. Then run the code.
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = default DCO ~ 800kHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//               MSP430F123(2)
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32k
//          --|RST          XOUT|-
//            |                 |
//            |             P1.4|-->SMCLK ~ 800kHz
//            |             P1.1|-->MCLK/10 = DCO/10
//            |             P2.0|-->ACLK = 32kHz
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

void main(void)
{
  WDTCTL = WDTPW +WDTHOLD;                  // Stop Watchdog Timer
  P1DIR |= 0x12;                            // P1.1 and P1.4 outputs
  P1SEL |= 0x10;                            // P1.4 SMCLK output
  P2DIR |= 0x01;                            // P2.0 output
  P2SEL |= 0x01;                            // P2.0 ACLK output

  while(1)
  {
    P1OUT |= 0x02;                          // P1.1 = 1
    P1OUT &= ~0x02;                         // P1.1 = 0
  }
}

