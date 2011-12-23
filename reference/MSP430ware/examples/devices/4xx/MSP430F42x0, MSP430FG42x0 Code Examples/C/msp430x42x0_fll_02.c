//******************************************************************************
//   MSP430x42x0 Demo - FLL+, Runs Internal DCO at 8MHz
//
//  Description: This program demonstrates setting the internal DCO to run at
//  8MHz with auto-calibration by the FLL+.
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = DCOCLK = (121+1) x 2 x ACLK = 7995392Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                 MSP430F4270
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |        P1.1/MCLK|--> MCLK = 8Mhz
//            |                 |
//            |        P1.5/ACLK|--> ACLK = 32kHz
//            |                 |
//
//  L. Westlund / S. Karthikeyan
//  Texas Instruments Inc.
//  June 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//*****************************************************************************
#include  <msp430x42x0.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  SCFI0 |= FN_3;                            // Set DCO operating range
  SCFQCTL = 121;                            // (121+1) x 32768 x 2 = 7.99 Mhz
  FLL_CTL0 = DCOPLUS + XCAP14PF;            // DCO+ set so freq = xtal x D x N+1
  P1DIR = 0x22;                             // P1.1,5 to output direction
  P1SEL = 0x22;                             // P1.1,5 to output MCLK & ACLK

  while(1);                                 // Loop in place
}

