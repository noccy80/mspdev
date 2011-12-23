//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P1.0, TA1CCR0 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer1_A0 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TA1CLK.
//  During the Timer1_A0 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  TA1CCR0. Timer1_A0 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TA_ISR.
//  ACLK = n/a, MCLK = SMCLK = TA1CLK = default DCO ~1.2MHz
//
//              MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.10A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA1CCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TA1CCR0 = 50000;
  TA1CTL = TASSEL_2 + MC_2;                  // SMCLK, contmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer1_A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
  TACCR0 += 50000;                          // Add Offset to TACCR0
}

