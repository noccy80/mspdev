//******************************************************************************
//  MSP430F(G)47x Demo - FLL+, Runs Internal DCO at 2.45MHz
//
//  Description: This program demonstrates setting the internal DCO to run at
//  2.45MHz with auto-calibration by the FLL+ circuitry.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (74+1) x ACLK = 2457600Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//                MSP430F(G)47x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.1|--> MCLK = 2.4576Mhz
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
  SCFI0 |= FN_2;                            // x2 DCO, 4MHz nominal DCO
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance for xtal
  SCFQCTL = 74;                             // (74+1) x 32768 = 2.45Mhz

  P1DIR = 0x22;                             // P1.1 & P1.5 to output direction
  P1SEL = 0x22;                             // P1.1 & P1.5 to output MCLK & ACLK
  P1SEL2 |= 0x02;	
  while(1);                                 // loop in place
}

