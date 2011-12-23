//******************************************************************************
//  MSP430x26x Demo - Configure RST/NMI as NMI
//
//  Description: Configure RST/NMI as NMI, hi to low edge. Flash P1.0 inside of
//  NMI_ISR if NMI occurs. General enable interrupt in status register does
//  not need to be set for NMI. NMIIE does need to be re-set, as NMI_ISR
//  automatically clears NMI enable to prevent unintentional stack overflow
//  that could result from, bounce or uncontrolled NMI's.
//  ACLK = n/a, MCLK = SMCLK = DCO ~1.045MHz
//
//            MSP430F261x/241x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST/NMI      XOUT|-
//           |                 |
//           |             P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD + WDTNMI + WDTNMIES;  // WDT off NMI hi/lo
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  P1OUT &= ~0x01;                           // Clear P1.0 LED off
  IE1 |= NMIIE;                             // Enable NMI

  __bis_SR_register(LPM0_bits);             // Enter LPM0
}

/* Generates a BIS instruction just before the RETI instruction */


// NMI interrupt service routine
#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR(void)
{
  volatile unsigned int i, j;
  for (j=10; j>0; j--)                      // Toggle LED 5 times
  {                  
    P1OUT ^= 0x01;                          // Toggle P1.0 LED by using XOR
    for (i = 20000; i > 0; i--);            // Delay
  }
  P1OUT &= ~0x01;                           // Clear P1.0 LED off
  IFG1 &= ~NMIIFG;                          // Reclear NMI flag in case bounce
}
