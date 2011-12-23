//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P1.0 3.6,3.7, Cont. Mode ISR, 32kHz ACLK
//
//  Description: Use Timer1_A2 CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, TA1CCR0, TA1CCR1 and TA1CCR2
//  output units are optionally selected with port pins P3.6 and P3.7
//  in toggle mode. As such, these pins will toggle when respective TA1CCRx
//  registers match the T1AR counter. Interrupts are also enabled with all
//  TA1CCRx units, software loads offset to next interval only - as long as the
//  interval offset is added to TA1CCRx, toggle rate is generated in hardware.
//  Timer1_A1 overflow ISR is used to toggle P1.0 with software. Proper use
//  of the TA1IV interrupt vector generator is demonstrated.
//  ACLK = TA1CLK = 32kHz, MCLK = SMCLK = default DCO ~1.2MHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//  As coded and with TA1CLK = 32768Hz, toggle rates are:
//  P3.6 = TA1CCR0 = 32768/(2*4) = 4096Hz
//  P3.7 = TA1CCR1 = 32768/(2*16) = 1024Hz
//  P1.0 = overflow = 32768/(2*65536) = 0.25Hz
//
//              MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
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
  TA1CCTL0 = OUTMOD_4 + CCIE;                // TACCR0 toggle, interrupt enabled
  TA1CCTL1 = OUTMOD_4 + CCIE;                // TACCR1 toggle, interrupt enabled
  TA1CTL = TASSEL_1 + MC_2 + TAIE;           // ACLK, contmode, interrupt enabled

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/interrupt
}

// Timer1 A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void)
{
  TA1CCR0 += 4;                              // Add Offset to TACCR0
}

// Timer1 A1 Interrupt Vector (TA1IV) handler

#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1_A1(void)
{
  switch (__even_in_range(TA1IV, 10))        // Efficient switch-implementation
  {
    case  2: TA1CCR1 += 16;                  // Add Offset to TACCR1
             break;

    case 10: P1OUT ^= 0x01;                 // Timer1_A3 overflow
             break;
  }
}

