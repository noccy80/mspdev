//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
//
//  Description: Use Timer0_A3 CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, TA0CCR0, TA0CCR1 and TA0CCR2
//  output units are optionally selected with port pins P1.1, P1.2 and P1.3
//  in toggle mode. As such, these pins will toggle when respective TA0CCRx
//  registers match the TA0R counter. Interrupts are also enabled with all
//  TA0CCRx units, software loads offset to next interval only - as long as
//  the interval offset is added to TACCRx, toggle rate is generated in
//  hardware. Timer0_A1 overflow ISR is used to toggle P1.0 with software.
//  Proper use of the TA0IV interrupt vector generator is demonstrated.
//  ACLK = n/a, MCLK = SMCLK = TA0CLK = default DCO ~1.2MHz
//
//  As coded with TACLK ~1.2MHz DCO, toggle rates are:
//  P1.1 = TA0CCR0 = 1.2MHz/(2*200) ~3000Hz
//  P1.2 = TACCR1 = 1.2MHz/(2*1000) ~600Hz
//  P1.3 = TACCR2 = 1.2MHz/(2*10000) ~60Hz
//  P1.0 = overflow = 1.2MHz/(2*65536) ~9Hz
//
//              MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
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
  TA0CCTL1 = OUTMOD_4 + CCIE;                // TA0CCR1 toggle, interrupt enabled
  TA0CCTL2 = OUTMOD_4 + CCIE;                // TA0CCR2 toggle, interrupt enabled
  TA0CTL = TASSEL_2 +  MC_2 + TAIE;          // SMCLK, Contmode, int enabled

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer0_A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
  TA0CCR0 += 200;                            // Add Offset to TA0CCR0
}

// Timer0_A1 Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
  switch (__even_in_range(TA0IV, 10))        // Efficient switch-implementation
  {
    case  2: TACCR1 += 1000;                // Add Offset to TA0CCR1
             break;
    case  4: TACCR2 += 10000;               // Add Offset to TA0CCR2
             break;
    case 10: P1OUT ^= 0x01;                 // Timer_A3 overflow
             break;
  }
}

