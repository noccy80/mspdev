//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P1.0, Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer1_A2 overflow ISR.
//  In this example an ISR triggers when Timer1_A2 overflows. Inside the Timer1_A1
//  overflow ISR P1.0 is toggled. Toggle rate is approximately 18Hz.
//  Proper use of the TA1IV interrupt vector generator is demonstrated.
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
//  December 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.10A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA1CTL = TASSEL_2 + MC_2 + TAIE;          // SMCLK, contmode, interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer1_A1 Interrupt Vector (TAIV) handler
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A1(void)
{
  switch  (__even_in_range(TA1IV, 10))       // Efficient switch-implementation
  {
    case  2: break;                         // TACCR1 not used
    case  4: break;                         // TACCR2 not used
    case 10: P1OUT ^= 0x01;                 // overflow
             break;
  }
}

