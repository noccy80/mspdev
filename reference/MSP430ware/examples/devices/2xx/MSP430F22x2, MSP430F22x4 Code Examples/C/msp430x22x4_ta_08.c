//******************************************************************************
//  MSP430F22x4 Demo - Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
//
//  Description: Use Timer_A CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, TACCR0, TACCR1 and TACCR2
//  output units are optionally selected with port pins P1.1, P1.2 and P1.3
//  in toggle mode. As such, these pins will toggle when respective TACCRx
//  registers match the TAR counter. Interrupts are also enabled with all
//  TACCRx units, software loads offset to next interval only - as long as the
//  interval offset is added to TACCRx, toggle rate is generated in hardware.
//  Timer_A overflow ISR is used to toggle P1.0 with software. Proper use
//  of the TAIV interrupt vector generator is demonstrated.
//  ACLK = TACLK = 32kHz, MCLK = SMCLK = default DCO ~1.2MHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//  As coded and with TACLK = 32768Hz, toggle rates are:
//  P1.1 = TACCR0 = 32768/(2*4) = 4096Hz
//  P1.2 = TACCR1 = 32768/(2*16) = 1024Hz
//  P1.3 = TACCR2 = 32768/(2*100) = 163.84Hz
//  P1.0 = overflow = 32768/(2*65536) = 0.25Hz
//
//              MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.1/TA0|--> TACCR0
//           |         P1.2/TA1|--> TACCR1
//           |         P1.3/TA2|--> TACCR2
//           |             P1.0|--> Overflow/software
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1SEL |= 0x0E;                            // P1.1 - P1.3 option select
  P1DIR |= 0x0F;                            // P1.0 - P1.3 outputs
  TACCTL0 = OUTMOD_4 + CCIE;                // TACCR0 toggle, interrupt enabled
  TACCTL1 = OUTMOD_4 + CCIE;                // TACCR1 toggle, interrupt enabled
  TACCTL2 = OUTMOD_4 + CCIE;                // TACCR2 toggle, interrupt enabled
  TACTL = TASSEL_1 + MC_2 + TAIE;           // ACLK, contmode, interrupt enabled

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{
  TACCR0 += 4;                              // Add Offset to TACCR0
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
  switch (TAIV)        // Efficient switch-implementation
  {
    case  2: TACCR1 += 16;                  // Add Offset to TACCR1
             break;
    case  4: TACCR2 += 100;                 // Add Offset to TACCR2
             break;
    case 10: P1OUT ^= 0x01;                 // Timer_A3 overflow
             break;
  }
}

