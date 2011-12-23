//******************************************************************************
//   MSP430x21x2 Demo - Comparator A, Poll input CA0, interrupt triggered
//
//   Description:  Normal operation is in LPM3.  When Vcompare crosses the ref
//   voltage, an interrupt is generated, and the ISR toggles the LED.
//
//
//                 MSP430x21x2
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST           CA0|<--Vcompare
//            |                 |
//         <--|CAOUT/P2.6       |
//            |             P1.0|-->LED
//
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x21x2.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  CACTL1 = CAON+CAREF_2+CARSEL;             // Enable comp, ref = 0.5*Vcc
  CACTL2 = P2CA0;                           // Pin to CA0
  CAPD |= CAPD6;                            // Port pin buffer disable
  P1DIR |= BIT0;                            // P1.0 = output direction
  P2SEL |= BIT6;                            // P2.6 = CAOUT

  CACTL1 |= CAIE;                           // Setup interrupt for Comparator
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, interrupts enabled
}


// Comp_A interrupt service routine -- toggles LED
#pragma vector=COMPARATORA_VECTOR
__interrupt void Comp_A_ISR (void)
{
  CACTL1 ^= CAIES;                          // Toggles interrupt edge
  P1OUT ^= 0x01;                            // Toggle P1.0
}
