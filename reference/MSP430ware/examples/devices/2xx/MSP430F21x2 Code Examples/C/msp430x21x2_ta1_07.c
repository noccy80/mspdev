//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
//
//  Description: Use Timer1_A2 CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, TA1CCR0 and TA1CCR1
//  output units are optionally selected with port pins P3.6 and P3.7
//  in toggle mode. As such, these pins will toggle when respective TA1CCRx
//  registers match the TA1R counter. Interrupts are also enabled with all
//  TA1CCRx units, software loads offset to next interval only - as long as
//  the interval offset is added to TA1CCRx, toggle rate is generated in
//  hardware. Timer1_A1 overflow ISR is used to toggle P1.0 with software.
//  Proper use of the TA1IV interrupt vector generator is demonstrated.
//  ACLK = n/a, MCLK = SMCLK = TA1CLK = default DCO ~1.2MHz
//
//  As coded with TACLK ~1.2MHz DCO, toggle rates are:
//  P3.6 = TA1CCR0 = 1.2MHz/(2*200) ~3000Hz
//  P3.7 = TA1CCR1 = 1.2MHz/(2*1000) ~600Hz
//  P1.0 = overflow = 1.2MHz/(2*65536) ~9Hz
//
//              MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |       P3.6/TA0_1|--> TA1CCR0
//           |       P3.7/TA1_1|--> TA1CCR1
//           |                 |
//           |             P1.0|--> Overflow/software
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
  P3SEL |= 0xC0;                            // P3.6 - P3.7 option select
  P3DIR |= 0xC0;                            // P3.6 - P3.7 output
  P1DIR |= 0x01;                            // P1.0 output
  TA1CCTL0 = OUTMOD_4 + CCIE;               // TA1CCR0 toggle, interrupt enabled
  TA1CCTL1 = OUTMOD_4 + CCIE;               // TA1CCR1 toggle, interrupt enabled
  TA1CTL = TASSEL_2 +  MC_2 + TAIE;         // SMCLK, Contmode, int enabled

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer1_A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void)
{
  TA1CCR0 += 200;                            // Add Offset to TACCR0
}

// Timer1_A1 Interrupt Vector (TA1IV) handler
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A1(void)
{
  switch (__even_in_range(TA1IV, 10))        // Efficient switch-implementation
  {
    case  2: TA1CCR1 += 1000;                // Add Offset to TA1CCR1
             break;

    case 10: P1OUT ^= 0x01;                  // overflow
             break;
  }
}

