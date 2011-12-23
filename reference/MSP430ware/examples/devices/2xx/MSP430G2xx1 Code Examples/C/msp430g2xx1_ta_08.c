//******************************************************************************
//  MSP430G2xx1 Demo - Timer_A, Toggle P1.0-2, Cont. Mode ISR, 32kHz ACLK
//
//  Description: Use Timer_A CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, CCR0 and CCR1 output
//  units are optionally selected with port pins P1.1 and P1.2 in toggle
//  mode. As such, these pins will toggle when respective CCRx registers match
//  the TAR counter. Interrupts are also enabled with all CCRx units,
//  software loads offset to next interval only - as long as the interval offset
//  is aded to CCRx, toggle rate is generated in hardware. Timer_A overflow ISR
//  is used to toggle P1.0 with software. Proper use of TAIV interrupt vector
//  generator is demonstrated.
//  ACLK = TACLK = 32kHz, MCLK = SMCLK = Default DCO
//  As coded and with TACLK = 32768Hz, toggle rates are:
//  P1.1 = CCR0 = 32768/(2*4) = 4096Hz
//  P1.2 = CCR1 = 32768/(2*16) = 1024Hz
//  P1.0 = overflow = 32768/(2*65536) = 0.25Hz
//  //* External watch crystal on XIN XOUT is required for ACLK *//	
//
//              MSP430G2xx1
//            ---------------
//        /|\|            XIN|-
//         | |               | 32kHz
//         --|RST        XOUT|-
//           |               |
//           |       P1.1/TA0|--> CCR0
//           |       P1.2/TA1|--> CCR1
//           |           P1.0|--> Overflow/software
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
  P1SEL |= 0x06;                            // P1.1 - P1.2 option select
  P1DIR |= 0x07;                            // P1.0 - P1.2 outputs
  CCTL0 = OUTMOD_4 + CCIE;                  // CCR0 toggle, interrupt enabled
  CCTL1 = OUTMOD_4 + CCIE;                  // CCR1 toggle, interrupt enabled
  TACTL = TASSEL_1 + MC_2 + TAIE;           // ACLK, contmode, interrupt enabled

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
  CCR0 += 4;                                // Add Offset to CCR0
}

// Timer_A2 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
  switch( TAIV )
  {
  case  2: CCR1 += 16;                      // Add Offset to CCR1
           break;
  case 10: P1OUT ^= 0x01;                   // Timer_A3 overflow
           break;
 }
}

