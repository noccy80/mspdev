//******************************************************************************
//  MSP430F552x Demo - Timer1_A3, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the TA_1 ISR. Timer1_A is
//  configured for up mode, thus the timer overflows when TAR counts
//  to CCR0. In this example, CCR0 is loaded with 1000-1.
//  Toggle rate = 32768/(1000) = 8.2Hz
//  ACLK = TACLK = 32768Hz, MCLK = SMCLK = default DCO ~1.045MHz
//
//           MSP430F552x
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA1CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TA1CCR0 = 1000-1;
  TA1CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, upmode, clear TAR

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
  __no_operation();                         // For debugger
}

// Timer1 A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

