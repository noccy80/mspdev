//******************************************************************************
//  MSP430F23x0 Demo - Comp_A+, Detect Threshold, Set P1.0 if P2.4 > 0.25*Vcc
//
//  Description: Use Comparator_A+ to detect a voltage threshold.
//  Using an external potentiometer, an unknown voltage is applied to P2.4.
//  Comparator_A+ compares the unknown voltage to an internal reference
//  voltage, in this example 0.25*VCC. If the unknown voltage is higher
//  than 0.25*VCC, P1.0 is set, if not, P1.0 is reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
//
//             MSP430F23x0
//            ---------------
//       /|\ |            XIN|-
//        |  |               |
//        ---|RST        XOUT|-
//        |  |               |
//        R<-|P2.4/CA1   P1.0|-->LED
//        |  |               |
//        ---|VSS            |
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x23x0.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  CACTL1 = CARSEL + CAREF0 + CAON;          // 0.25*Vcc = -Comp, on
  CACTL2 = P2CA4;                           // P2.4/CA1 = +Comp

  while (1)
  {
    if (CACTL2 & CAOUT)                     // Test Comparator_A+ output
      P1OUT |= 0x01;                        // if CAOUT set, set P1.0
    else
      P1OUT &= ~0x01;                       // else reset
  }
}
