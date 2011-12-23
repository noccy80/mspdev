//******************************************************************************
//  MSP430F23x0 Demo - Comp_A+, Simple 2.2V Low Battery Detect
//
//  Description: Two Comparator_A+ reference generators 0.25*Vcc and ~0.55V
//  are compared for a simple battery check of 2.2V. In the subroutine
//  Batt_Check, a small capacitor between P2.4 and Vss is first charged
//  to 0.25*Vcc and then compared to ~0.55V. If 0.25*Vcc,
//  is above ~0.55V, P1.0 is toggled, else set. Batt_Check is called
//  constantly in an endless loop. In an actual application, Batt_Check
//  should be called infrequently to save power.
//
//  There is a tolerance of the Comp_A+ reference generator and in the
//  device specific datasheet. In most applications, the tolerence of the
//  reference generator is more than adequate to detect Low Battery.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
//
//               MSP430F23x0
//            -----------------
//       /|\ |              XIN|-
//        |  |                 |
//        ---|RST          XOUT|-
//           |                 |
//     +-----|P2.4/CA1     P1.0|-->LED
//     |     |                 |
//    ===.1uF|                 |
//     |     |                 |
//     +-----|Vss              |
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x23x0.h"

void Batt_Check(void);

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  CACTL2 = P2CA4;                           // P2.4 = CA1
  while (1)                                 // Mainloop
  {
    Batt_Check();
  }
}

void Batt_Check(void)
{
  volatile unsigned int i;                  // volatile to prevent optimization

  CACTL1 = CAREF_1 + CAON;                  // 0.25*Vcc on P2.4, Comp. on
  for (i = 16384; i; i--);                  // SW delay, charge ext. cap
  CACTL1 = CARSEL + CAREF_3 + CAON;         // 0.55V on -Comp, on
  if (CACTL2 & CAOUT)                       // Test Comparator_A+ output
    P1OUT ^= 0x01;                          // P1.0 toggle
  else
    P1OUT |= 0x01;                          // P1.0 set
  CACTL1 = 0x00;                            // Disable Comp_A+, save power
}
