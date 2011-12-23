//******************************************************************************
//   MSP430x41x2 Demo - Comparator A, Poll input CA0, interrupt triggered
//
//   Description:  Normal operation is in LPM3.  When Vcompare crosses the ref
//   voltage, an interrupt is generated, and the ISR toggles the LED.
//
//
//                MSP430x41x2
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST           CA0|<--Vcompare
//            |                 |
//            |                 |
//            |             P5.1|-->LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include  <msp430x41x2.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  CACTL1 = CAON+CAREF_2+CARSEL;             // Enable comp, ref = 0.5*Vcc
  CACTL2 = P2CA0;                           // Pin to CA0
  CAPD |= CAPD6;                            // Port pin buffer disable
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  P1DIR |= 0x20;                            // P1.5 = CAOUT
  P1SEL |= 0x20;                            // P1.5 = CAOUT

  CACTL1 |= CAIE;                           // Setup interrupt for Comparator
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, interrupts enabled
}


// Comp_A interrupt service routine -- toggles LED
#pragma vector=COMPARATORA_VECTOR
__interrupt void Comp_A_ISR (void)
{
  CACTL1 ^= CAIES;                          // Toggles interrupt edge
  P5OUT ^= 0x02;                            // Toggle P5.1
}
