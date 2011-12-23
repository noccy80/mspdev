//******************************************************************************
//  MSP430G2xx1 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
//
//  Description: Buffer ACLK on P2.0, default SMCLK(DCO) on P1.4 and MCLK/10 on
//  P1.1.
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = default DCO
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//               MSP430G2xx1
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |       P1.4/SMCLK|-->SMCLK = Default DCO
//            |             P1.1|-->MCLK/10 = DCO/10
//            |        P1.0/ACLK|-->ACLK = 32kHz
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2231.h>

void main(void)
{
  WDTCTL = WDTPW +WDTHOLD;                  // Stop Watchdog Timer
  P1DIR |= 0x13;                            // P1.0,1 and P1.4 outputs
  P1SEL |= 0x11;                            // P1.0,4 ACLK, SMCLK output

  while(1)
  {
    P1OUT |= 0x02;    	                    // P1.1 = 1
    P1OUT &= ~0x02;                         // P1.1 = 0
  }
}

