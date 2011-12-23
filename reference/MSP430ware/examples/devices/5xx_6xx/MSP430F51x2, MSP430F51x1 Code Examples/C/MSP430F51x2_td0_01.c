//******************************************************************************
//  MSP430F51x2 Demo - TimerD0, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TD_0 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TDCLK.
//  During the TD_0 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  CCR0. TD_0 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TD_ISR. Toggle rate = 50000/1.045Mhz ~ 48ms. 
//  ACLK = n/a, MCLK = SMCLK = TDCLK = default DCO ~1.045MHz
//
//           MSP430F51x2
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TD0CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TD0CCR0 = 50000;
  TD0CTL0 = TDSSEL_2 + MC_2 + TDCLR;         // SMCLK, contmode, clear TDR

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  __no_operation();                         // For debugger
}

// Timer0_D0 interrupt service routine
#pragma vector=TIMER0_D0_VECTOR
__interrupt void TIMER0_D0_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
  TD0CCR0 += 50000;                         // Add Offset to CCR0
}

