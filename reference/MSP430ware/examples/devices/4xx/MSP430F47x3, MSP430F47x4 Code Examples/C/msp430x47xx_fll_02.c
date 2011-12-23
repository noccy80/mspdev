//******************************************************************************
//   MSP430x47xx Demo - FLL+, Runs Internal DCO at 16MHz
//
//  Description: This program demonstrates setting the internal DCO to run at
//  8MHz with auto-calibration by the FLL+.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (121+1) x 4 x ACLK = 16MHz
//  For correct CPU operation @ 16MHz, the supply voltage should be set accordingly
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                  MSP430x47xx
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.1|--> MCLK = 16MHz
//            |                 |
//            |             P1.5|--> ACLK = 32kHz
//            |                 |
//
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//*****************************************************************************
#include  <msp430x47x4.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  FLL_CTL0 |= DCOPLUS + XCAP18PF;           // DCO+ set, freq = xtal x D x N+1
  SCFI0 = FLLD_4+FN_4;                      // x4 DCO freq, 16MHz nominal DCO
  SCFQCTL = 121;                            // (121+1) x 32768 x 4 = 16 MHz
  P1DIR = BIT1+BIT5;                        // P1.1 & P1.5 to output direction
  P1SEL = BIT1+BIT5;                        // P1.1 & P1.5 to output MCLK & ACLK

  while(1);                                 // Loop in place
}
