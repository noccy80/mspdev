//******************************************************************************
//  MSP430x11x1 Demo - DCOCLK Biased with External Resistor Rosc
//
//  Description: Use external resistor on P2.5 as DCO current source. DCOCLK
//  is used by default as the MCLK source. Mainloop drives a 10 cycle software
//  loop toggling P1.1. Measure DCOCLK/10 on P1.1. Example also disables XTAL
//  buffer. Use of external resistor reduces temperature sensitivity of DCOCLK.
//
//  DCOCLK = Using default DCO and RSEL values @ 2.85V
//  022k ~ 5.5MHz
//  100k ~ 2Mhz
//  220k ~ 860kHz
//  470k ~ 400kHz
//
//               MSP430F1121
//            -----------------
//   /|\  /|\|              XIN|-
//    |    | |                 |
//    R    --|RST          XOUT|-
//    |      |                 |
//    -------|P2.5/ROSC    P1.1|-->DCOCLK/10
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include <msp430x11x1.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x02;                            // P1.1 = output direction
  BCSCTL2 |= DCOR;                          // Rosc
  _BIS_SR(OSCOFF);                          // XTAL not used


  while(1)
  {
    P1OUT |= 0x02;
    P1OUT &= ~0x02;
  }
}
