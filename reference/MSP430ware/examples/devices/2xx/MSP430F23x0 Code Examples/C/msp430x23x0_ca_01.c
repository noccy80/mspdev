//******************************************************************************
//  MSP430F23x0 Demo - Comp_A+, Output Reference Voltages on P2.4
//
//  Description: Output Comparator_A+ reference levels on P2.4. Program will
//  cycle through the on-chip Comparator_A+ reference voltages with output on
//  P2.4. Normal mode is LPM0, Timer_A0 will interrupt LPM0.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
//
//                MSP430F23x0
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |         P2.4/CA1|-->Vref
//            |                 |
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
  CACTL2 = P2CA4;                           // P2.4/CA1 = +Comp
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TACTL = TASSEL_2 + ID_3 + MC_2;           // SMCLK/8, cont-mode

  while (1)                                 // Loop
  {
    CACTL1 = 0x00;                          // No reference voltage
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
    CACTL1 = CAREF0 + CAON;                 // 0.25*Vcc, Comp. on
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
    CACTL1 = CAREF1 + CAON;                 // 0.5*Vcc, Comp. on
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
    CACTL1 = CAREF1 + CAREF0 + CAON;        // 0.55V, Comp. on
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
  }
}

// Timer_A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
  __bic_SR_register_on_exit(LPM0_bits);     // Clear LPM0 bits from 0(SR)
}
