//******************************************************************************
//  MSP430G2x11 Demo - Comp_A, Simple 2.2V Low Battery Detect
//
//  Description: Two comparator_A reference generators 0.25*Vcc and ~0.55V
//  are compared for a simple battery check of 2.2V. In the subroutine
//  Batt_Check, a small capacitor between P2.3 and Vss is first charged
//  to 0.25*Vcc and then compared to ~0.55V. If 0.25*Vcc,
//  is above ~0.55V, P1.0 is toggled, else set. Batt_Check is called
//  constantly in an endless loop - in an actual application, Batt_Check
//  should be called infrequently to save power.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//  There is a tolerance of the Comp_A reference generator and in the
//  device specific datasheet. In most applications, the tolerence of the
//  reference generator is more than adequate to detect Low Battery.
//
//		 MSP430G2x11
//            -----------------
//       /|\ |              XIN|-
//        |  |                 |
//        ---|RST          XOUT|-
//           |                 |
//     +-----|P1.1/CA1     P1.0|-->LED
//     |     |                 |
//    ===.1uf|                 |
//     |     |                 |			
//     +-----|Vss
//
void Batt_Check(void);
unsigned int i;
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2211.h>

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  CACTL2 = P2CA4;                           // P1.1 = CA1
  while (1)                                 // Mainloop
  {
    Batt_Check();
  }
}

void Batt_Check(void) {
  CACTL1 = CAREF_1 + CAON;                  // 0.25*Vcc on P1.1, Comp. on
  i = 16384;                                // delay
  while(i>0) {
    i--;
  }
  CACTL1 = CARSEL + CAREF_2 + CAREF_1 + CAON; // 0.55V on -, Comp. on
  if (CACTL2 & CAOUT)
    P1OUT ^= 0x01;                          // P1.0 toggle
  else P1OUT |= 0x01;                       // P1.0 set
  CACTL1 = 0x00;                            // Disable Comp_A, save power
}
