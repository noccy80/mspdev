//******************************************************************************
//   MSP430x471xx Demo - Timer_B, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P5.1 using software and TB_0 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TBCLK. During the
//  TB_0 ISR, P5.1 is toggled and 50000 clock cycles are added to
//  CCR0. TB_0 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TB_ISR.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//
//            MSP430x471xx
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5DIR |= BIT1;                            // P5.1 output
  TBCCTL0 = CCIE;                           // CCR0 interrupt enabled
  TBCCR0 = 50000;
  TBCTL = TBSSEL_2 + MC_2;                  // SMCLK, continuous mode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P5OUT ^= BIT1;                            // Toggle P5.1
  TBCCR0 += 50000;                          // Add Offset to CCR0
}

