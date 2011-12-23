//******************************************************************************
//  MSP430F23x0 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
//
//  Description: Buffer ACLK on P2.0, SMCLK(DCO) on P1.4 and MCLK/10 on
//  P2.2.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = CALxxx_8MHZ = 8MHz
//  //* External watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430F23x0
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P2.0|-->ACLK = 32kHz
//            |             P1.4|-->SMCLK = 8MHz
//            |             P2.2|-->MCLK/10 = DCO/10
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x23x0.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop Watchdog Timer
  if (CALBC1_8MHZ ==0xFF || CALDCO_8MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  }   
  BCSCTL1 = CALBC1_8MHZ;                    // Set DCO to 8MHz
  DCOCTL = CALDCO_8MHZ;
  P1DIR |= 0x10;                            // P1.4 output direction
  P1SEL |= 0x10;                            // P1.4 = SMCLK
  P2DIR |= 0x05;                            // P2.0,2 output direction
  P2SEL |= 0x01;                            // P2.0 = ACLK

  while (1)
  {
    P2OUT |= 0x04;                          // P2.2 = 1
    P2OUT &= ~0x04;                         // P2.2 = 0
  }
}
