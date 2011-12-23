//******************************************************************************
//  MSP430F22x4 Demo - Configure RST/NMI as NMI
//
//  Description: Configure RST/NMI as NMI, hi/lo edge. Flash P1.0 inside of
//  NMI_ISR if NMI occurs. General enable interrupt in status register does
//  not need to be set for NMI. NMIIE does need to be re-set, as NMI_ISR
//  automatically clears NMI enable to prevent unintentional stack overflow
//  that could result from, bounce or uncontrolled NMI's.
//  ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST/NMI      XOUT|-
//           |                 |
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  December 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD + WDTNMI + WDTNMIES;  // WDT off NMI hi/lo
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  P1OUT &= ~0x01;                           // Clear P1.0 LED off
  IE1 |= NMIIE;                             // Enable NMI

  __bis_SR_register(LPM0_bits);             // Enter LPM0
}

//#pragma bis_nmi_ie1=NMIIE                   // Re-enable NMI
#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR(void)
{
  volatile unsigned int i;
  P1OUT |= 0x01;                            // Set P1.0 LED on
  for (i = 20000; i > 0; i--);              // Delay
  P1OUT &= ~0x01;                           // Clear P1.0 LED off
  IFG1 &= ~NMIIFG;                          // Reclear NMI flag in case bounce
}
