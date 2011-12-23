//******************************************************************************
//  MSP430F26x Demo - DCOCLK Biased with External Resistor Rosc
//
//  Description: Use external resistor on P2.5 as DCO current source. DCOCLK
//  is used by default as the MCLK source and this is buffered on P5.4. 
//  Mainloop drives a 10 cycle software loop toggling P1.1. Measure DCOCLK/10 
//  on P1.1. Example also disables XTAL buffer. Use of external resistor reduces
//  temperature sensitivity of DCOCLK.
//  NOTE: With no resistor conencted, the oscillator will stop. Also, in this
//  case, the ability of re-establishing JTAG connectivity may be affected.
//
//  DCOCLK Frequency using DCO = 3 and RSEL = 4 values @ 3V
//  R=100K -> ~2MHz (See device datasheet)
//
//               MSP430F261x/241x
//            -----------------
//   /|\  /|\|              XIN|-
//    |    | |                 |
//    R    --|RST          XOUT|-
//    |      |                 |
//    -------|P2.5/ROSC    P1.1|-->DCOCLK/10
//           |        P5.4/MCLK|-->MCLK = DCOCLK
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x02;                            // P1.1 = output direction
  BCSCTL2 |= DCOR;                          // Rosc
  BCSCTL1 &= ~(RSEL1 + RSEL0);              // RSEL = 4
  
  P5DIR |= 0x010;                           // P5.4= output direction
  P5SEL |= 0x010;                           // P5.4= MCLK option select
  
  __bis_SR_register(OSCOFF);                // XTAL not used

  while(1)                                  // 10 MCLK (= DCOCLK) cycle loop 
  {
    P1OUT |= 0x02;
    P1OUT &= ~0x02;
  }
}
