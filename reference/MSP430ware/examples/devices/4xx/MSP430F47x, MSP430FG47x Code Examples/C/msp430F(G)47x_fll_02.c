//******************************************************************************
//  MSP430F(G)47x Demo - FLL+, Runs Internal DCO at 8MHz
//
//  Description: This program demostrates setting the internal DCO to run at
//  8MHz with auto-calibration by the FLL+.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (121+1) x 2 x ACLK = 7995392Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//                 MSP430F(G)47x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.1|--> MCLK = 8Mhz
//            |                 |
//            |             P1.5|--> ACLK = 32kHz
//            |                 |
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//******************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  SCFI0 |= FN_4;                            // x2 DCO freq, 8MHz nominal DCO
  SCFQCTL = 121;                            // (121+1) x 32768 x 2 = 7.99 Mhz
  FLL_CTL0 |= DCOPLUS + XCAP18PF;           // DCO+ set so freq= xtal x D x N+1
  P1DIR = 0x22;                             // P1.1,5 to output direction
  P1SEL = 0x22;                             // P1.1,5 to output MCLK & ACLK
  P1SEL2 |= 0x02;
  	
  while(1);                                 // Loop in place
}
