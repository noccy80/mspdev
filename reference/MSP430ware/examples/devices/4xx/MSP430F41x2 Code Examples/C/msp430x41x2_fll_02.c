//******************************************************************************
//  MSP430x41x2 Demo - FLL+, Runs Internal DCO at 8 MHz
//
//  Description: This program demonstrates setting the internal DCO to run at
//  8MHz with auto-calibration by the FLL+ circuitry.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (121+1) x 32768 x 2 = 7.99 Mhz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                 MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.1|--> MCLK = 8MHz
//            |                 |
//            |             P1.6|--> ACLK = 32.768kHz
//            |                 |
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//*****************************************************************************
#include  <msp430x41x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  SCFI0 |= FN_4;                            // x2 DCO freq, 8MHz nominal DCO
  SCFQCTL = 121;                            // (121+1) x 32768 x 2 = 7.99 Mhz
  FLL_CTL0 |= DCOPLUS + XCAP18PF;           // DCO+ set so freq= xtal x D x N+1

  P1DIR = BIT1+BIT6;                        // P1.1 & P1.6 to output direction
  P1SEL = BIT1+BIT6;                        // P1.1 & P1.6 to output MCLK & ACLK

  while(1);                                 // Loop in place
}

