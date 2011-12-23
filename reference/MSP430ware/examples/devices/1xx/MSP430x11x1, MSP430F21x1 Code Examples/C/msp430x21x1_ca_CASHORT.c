//******************************************************************************
//  MSP430x21x1 Demo - Comp_A, Simple 2.2V Low Battery Detect using CASHORT
//
//  Description: Two comparator_A reference generators 0.25*Vcc and ~0.55V
//  are compared for a simple battery check of 2.2V. In the subroutine
//  Batt_Check, a small capacitor between P2.3 and Vss is first charged
//  to 0.25*Vcc using the CASHORT feature, and then compared to ~0.55V. If
//  0.25*Vcc, is above ~0.55V, P1.0 is toggled, else set. Batt_Check is
//  called constantly in an endless loop - in an actual application,
//  Batt_Check should be called infrequently to save power.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.16MHz
//
//  There is a tolerance of the Comp_A reference generator and in the
//  device specific datasheet. In most applications, the tolerence of the
//  reference generator is more than adequate to detect Low Battery.
//
//		           MSP430F21x1
//             -----------------
//       /|\  |              XIN|-
//        |   |                 |
//        ----|RST          XOUT|-
//            |                 |
//     +------|P2.3/CA0     P1.0|-->LED
//     |      |                 |
//    ===2.2uf|                 |
//     |      |                 |			
//     +------|Vss              |
//
//
//  H. Grewal / A. Dannenberg
//  Texas Instruments Inc.
//  July 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//*****************************************************************************

#include <msp430x21x1.h>

void Batt_Check(void);

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  CAPD  |= 0x08;                            // Disconnect port pins
  CACTL2 = P2CA0;                           // P2.3 = CA0
  _EINT();                                  // Enable interrupts
  while (1)                                 // Mainloop
  {
    Batt_Check();
  }
}

void Batt_Check(void)
{
  CACTL2 |= CASHORT;                        // Short Ref and P2.3
  CACTL1 = CAREF_1 + CAON + CARSEL;         // 0.25*Vcc on P2.3, Comp. on
  CCR1 = 3605;                              // CCR1 ~ 110ms (5tau)
  CCTL1 = CCIE;                             // Compare mode, interrupt
  TACTL = TASSEL0+TACLR+MC1;                // ACLK, TA clear, continuous mode
  LPM0;                                     // enter LPM0, wait for CCR1 interrupt
  CACTL2 &= ~CASHORT;                        // Disable the Short
  CACTL1 = CARSEL + CAREF_2 + CAREF_1 + CAON; // 0.55V on -, Comp. on
  if ((CACTL2 & CAOUT) > 0)
    P1OUT ^= 0x01;                          // P1.0 toggle
  else
    P1OUT |= 0x01;                          // P1.0 set
  CACTL1 = 0x00;                            // Disable Comp_A, save power
}

// Timer A1 interrupt service routine
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
  LPM0_EXIT;                                // Exit LPM0
  CCTL1 &= ~CCIFG;                          // Clear CCR1 interrupt flag
  TACTL = 0;                                // Stop Timer
 }
