//******************************************************************************
//   MSP430xG46x Demo - Timer_B, Toggle P5.1, TBCCR0 Cont. Mode ISR, DCO SMCLK
//
//   Description: Toggle P5.1 using software and TB_0 ISR. Toggles every
//   50000 SMCLK cycles. SMCLK provides clock source for TACLK.
//   During the TB_0 ISR, P5.1 is toggled and 50000 clock cycles are added
//   to TBCCR0. TB_0 ISR is triggered every 50000 cycles. CPU is normally off
//   and used only during TB_ISR.
//   ACLK = 32.768kHz, MCLK = SMCLK = TACLK = default DCO
//
//                 MSP430xG46x
//             -----------------
//         /|\|              XIN|-
//          | |                 |  32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P5DIR |= 0x002;                           // P5.1 output

  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
  TBCCR0 = 50000;                           //
  TBCTL = TBSSEL_2+MC_2;                    // SMCLK, continuous mode

  _BIS_SR(LPM0_bits + GIE);                 // CPU off, interrupts enabled
}


// Timer_B interrupt service routine -- Toggle P5.1
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1
  TBCCR0 += 50000;                          // Add Offset to TACCR0
}

