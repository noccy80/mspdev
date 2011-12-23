//******************************************************************************
//  MSP430xG46x Demo - FLL+, Runs Internal DCO at 2.45MHz
//
//  Description: This program demonstrates setting the internal DCO to run at
//  2.45MHz with auto-calibration by the FLL+ circuitry.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (74+1) x ACLK = 2457600Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                 MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.1|--> MCLK = 2.45MHz
//            |                 |
//            |             P1.5|--> ACLK = 32kHz
//            |                 |
//
//  K. Quiring/ M.Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//*****************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance for xtal
  SCFI0 |= FN_2;                            // x2 DCO, 4MHz nominal DCO
  SCFQCTL = 74;                             // (74+1) x 32768 = 2.45Mhz

  P1DIR = 0x22;                             // P1.1 & P1.5 to output direction
  P1SEL = 0x22;                             // P1.1 & P1.5 to output MCLK & ACLK

  while(1);                                 // Loop in place
}

