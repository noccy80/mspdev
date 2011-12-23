//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
//
//  Description: Use Timer0_A3 CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, TA0CCR0, TA0CCR1 and TA0CCR2
//  output units are optionally selected with port pins P1.1, P1.2 and P1.3
//  in toggle mode. As such, these pins will toggle when respective TA0CCRx
//  registers match the TA0R counter. Interrupts are also enabled with all
//  TA0CCRx units, software loads offset to next interval only - as long as the
//  interval offset is added to TA0CCRx, toggle rate is generated in hardware.
//  Timer0_A1 overflow ISR is used to toggle P1.0 with software. Proper use
//  of the TA0IV interrupt vector generator is demonstrated.
//  ACLK = TACLK = 32kHz, MCLK = SMCLK = default DCO ~1.2MHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//  As coded and with TA0CLK = 32768Hz, toggle rates are:
//  P1.1 = TA0CCR0 = 32768/(2*4) = 4096Hz
//  P1.2 = TA0CCR1 = 32768/(2*16) = 1024Hz
//  P1.3 = TA0CCR2 = 32768/(2*100) = 163.84Hz
//  P1.0 = overflow = 32768/(2*65536) = 0.25Hz
//
//              MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.1/TA0|--> TA0CCR0
//           |         P1.2/TA1|--> TACCR1
//           |         P1.3/TA2|--> TACCR2
//           |             P1.0|--> Overflow/software
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1SEL |= 0x0E;                            // P1.1 - P1.3 option select
  P1DIR |= 0x0F;                            // P1.0 - P1.3 outputs
  TA0CCTL0 = OUTMOD_4 + CCIE;                // TA0CCR0 toggle, interrupt enabled
  TA0CCTL1 = OUTMOD_4 + CCIE;                // TACCR1 toggle, interrupt enabled
  TA0CCTL2 = OUTMOD_4 + CCIE;                // TACCR2 toggle, interrupt enabled
  TA0CTL = TASSEL_1 + MC_2 + TAIE;           // ACLK, contmode, interrupt enabled

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/interrupt
}

// Timer0_A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
  TA0CCR0 += 4;                              // Add Offset to TA0CCR0
}

// Timer0_A1 Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1(void)
{
  switch (__even_in_range(TA0IV, 10))        // Efficient switch-implementation
  {
    case  2: TACCR1 += 16;                  // Add Offset to TA0CCR1
             break;
    case  4: TACCR2 += 100;                 // Add Offset to TA0CCR2
             break;
    case 10: P1OUT ^= 0x01;                 // Timer0_A3 overflow
             break;
  }
}

