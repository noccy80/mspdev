//******************************************************************************
//  MSP430x41x2 Demo - FLL+, Runs Internal DCO at 2.45MHz
//
//  Description: This program demonstrates setting the internal DCO to run at
//  2.45MHz with auto-calibration by the FLL+ circuitry.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (74+1) x ACLK = 2457600Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                 MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.1|--> MCLK = 2.45MHz
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
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance for xtal
  SCFI0 |= FN_2;                            // x2 DCO, 4MHz nominal DCO
  SCFQCTL = 74;                             // (74+1) x 32768 = 2.45Mhz

  P1DIR = BIT1+BIT6;                        // P1.1 & P1.6 to output direction
  P1SEL = BIT1+BIT6;                        // P1.1 & P1.6 to output MCLK & ACLK

  while(1);                                 // Loop in place
}

