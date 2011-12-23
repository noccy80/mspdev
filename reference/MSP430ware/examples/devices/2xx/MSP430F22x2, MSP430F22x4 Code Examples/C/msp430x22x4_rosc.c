//******************************************************************************
//  MSP430F22x4 Demo - DCOCLK Biased with External Resistor Rosc
//
//  Description: Use external resistor on P2.5 as DCO current source. DCOCLK
//  is used by default as the MCLK source. Mainloop drives a 10 cycle software
//  loop toggling P1.1. Measure DCOCLK/10 on P1.1. Example also disables XTAL
//  buffer. Use of external resistor reduces temperature sensitivity of DCOCLK.
//  NOTE: With no resistor conencted, the oscillator will stop. Also, in this
//  case, the ability of re-establishing JTAG connectivity may be affected.
//
//  DCOCLK Frequency using DCO = 3 and RSEL = 4 values @ 3V
//  R=100K -> ~2MHz (See device datasheet)
//
//               MSP430F22x4
//            -----------------
//   /|\  /|\|              XIN|-
//    |    | |                 |
//    R    --|RST          XOUT|-
//    |      |                 |
//    -------|P2.5/ROSC    P1.1|-->DCOCLK/10
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x02;                            // P1.1 = output direction
  BCSCTL2 |= DCOR;                          // Rosc
  BCSCTL1 &= ~(RSEL1 + RSEL0);              // RSEL = 4
  __bis_SR_register(OSCOFF);                // XTAL not used

  while(1)
  {
    P1OUT |= 0x02;
    P1OUT &= ~0x02;
  }
}
