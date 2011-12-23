//******************************************************************************
//  MSP430G2xx1 Demo - Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TA_1 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TACLK.
//  During the TA_1 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  CCR0. TA_1 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TA_ISR. Proper use of the TAIV interrupt vector generator
//  is demonstrated.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO
//
//           MSP430G2xx1
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2231.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  CCTL1 = CCIE;                             // CCR1 interrupt enabled
  CCR1 = 50000;
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, Contmode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch( TAIV )
  {
  case  2:                                  // CCR1
    {
    P1OUT ^= 0x01;                          // Toggle P1.0
    CCR1 += 50000;                          // Add Offset to CCR1
    }
           break;
  case  4: break;                           // CCR2 not used
  case 10: break;                           // overflow not used
 }
}

