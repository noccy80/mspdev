//******************************************************************************
//  MSP-FET430P430 Demo - FLL+, Runs Internal DCO at 8MHz
//
//  Description: This program demostrates setting the internal DCO to run at
//  8MHz with auto-calibration by the FLL+.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (121+1) x 2 x ACLK = 7995392Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                 MSP430FG439
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
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  SCFI0 |= FN_4;                            // x2 DCO freq, 8MHz nominal DCO
  SCFQCTL = 121;                            // (121+1) x 32768 x 2 = 7.99 Mhz
  FLL_CTL0 |= DCOPLUS + XCAP18PF;           // DCO+ set so freq= xtal x D x N+1
  P1DIR = 0x22;                             // P1.1,5 to output direction
  P1SEL = 0x22;                             // P1.1,5 to output MCLK & ACLK

  while(1);                                 // Loop in place
}
