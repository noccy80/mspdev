//******************************************************************************
//  MSP430F21x1 Demo - Timer1_A2, Toggle P1.0, TACCR1 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer1_A1 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TA1CLK.
//  During the Timer1_A1 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  TA1CCR0. Timer1_A1 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during Timer1_A1 ISR. Proper use of the TA1IV interrupt vector generator
//  is demonstrated.
//  ACLK = n/a, MCLK = SMCLK = TA1CLK = default DCO ~1.2MHz
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.10A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA1CCTL1 = CCIE;                          // TA1CCR1 interrupt enabled
  TA1CCR1 = 50000;
  TA1CTL = TASSEL_2 + MC_2;                 // SMCLK, Contmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer1_A1 Interrupt Vector (TAIV) handler
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1_A1(void)
{
  switch (__even_in_range(TA1IV, 10))        // Efficient switch-implementation
  {
    case  2:                                // TACCR1
      P1OUT ^= 0x01;                        // Toggle P1.0
      TA1CCR1 += 50000;                      // Add Offset to TACCR1
      break;
    case  4: break;                         // TA1CCR2 not used
    case 10: break;                         // Overflow not used
  }
}
