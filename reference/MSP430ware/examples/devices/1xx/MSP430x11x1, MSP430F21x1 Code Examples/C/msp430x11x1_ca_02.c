//******************************************************************************
//  MSP430x11x1 Demo - Comp_A, Detect Threshold, Set P1.0 if P2.3 > 0.25*Vcc
//
//   Description: Use Comparator_A to detect a voltage threshold.
//   Using an external potentiometer, an unknown voltage is applied to P2.3.
//   Comparator_A compares the unknown voltage to an internal reference
//   voltage, in this example 0.25*VCC. If the unknown voltage is higher
//   than 0.25*VCC, P1.0 is set, if not, P1.0 is reset.
//   ACLK = n/a, MCLK = SMCLK = default DCO ~800kHz
//
//          MSP430F1121
//       -----------------
//   /|\ |            XIN|-
//    |  |               |
//    ---|RST        XOUT|-
//    |  |               |
//    R<-|P2.3/CA0   P1.0|-->LED
//    |  |               |
//    ---|VSS
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include <msp430x11x1.h>

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  CAPD  |= 0x08;                            // Disconnect port pins
  CACTL1 = CARSEL + CAREF0 + CAON;          // 0.25 Vcc = -comp, on
  CACTL2 = P2CA0;                           // P2.3 = +comp

  while (1)                                 // Test comparator_A output
  {
    if ((CAOUT & CACTL2))
    P1OUT |= 0x01;                          // if CAOUT set, set P1.0
    else P1OUT &= ~0x01;                    // else reset
  }
}

