//******************************************************************************
//   MSP430F22x4 Demo - Timer_B, Toggle P4.0-2, Cont. Mode ISR, 32kHz ACLK
//
//   Description: Use Timer_B CCRx units and overflow to generate four
//   independent timing intervals. For demonstration, TBCCR0-2 output
//   units are optionally selected with P4.0-2 respectively in toggle
//   mode. As such, these pins will toggle when respective TBCCRx registers
//   match the TBR counter. Interrupts are also enabled with all TBCCRx units,
//   software only adds offset to next interval - as long as the interval
//   offset is aded to TBCCRx, toggle rate is generated in hardware. Timer_B
//   overflow ISR is used to toggle P1.0 with software. Proper use of the
//   TBIV interrupt vector generator is demonstrated.
//   ACLK = TBCLK = 32kHz, MCLK = SMCLK = DCO ~1.2MHz
//   //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//   As coded and with TBCLK = 32768Hz, toggle rates are:
//   P4.0 = TBCCR0 = 32768/(2*4) = 4096Hz
//   P4.1 = TBCCR1 = 32768/(2*8) = 2048Hz
//   P4.2 = TBCCR2 = 32768/(2*16) = 1024Hz
//   P1.0 = overflow = 32768/(2*65536) = 0.25Hz
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |         P4.0/TB0|--> TBCCR0
//            |         P4.1/TB1|--> TBCCR1
//            |         P4.2/TB2|--> TBCCR2
//            |             P1.0|--> Overflow/software
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   April 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P4SEL |= 0x07;                            // P4.x - P4.2 option select
  P4DIR |= 0x07;                            // P4.x = outputs
  P1DIR |= 0x001;                           // P1.0 = output
  TBCCTL0 = OUTMOD_4 + CCIE;                // TBCCR0 interrupt enabled
  TBCCTL1 = OUTMOD_4 + CCIE;                // TBCCR1 interrupt enabled
  TBCCTL2 = OUTMOD_4 + CCIE;                // TBCCR2 interrupt enabled
  TBCTL = TBSSEL_1 + MC_2 + TBIE;           // ACLK, contmode, interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
}

// ISR for TBCCR0
#pragma vector=TIMERB0_VECTOR
__interrupt void TB0_ISR(void)
{
  TBCCR0 += 4;                              // Offset until next interrupt
}

// Common ISR for TBCCR1-2 and overflow
#pragma vector=TIMERB1_VECTOR
__interrupt void TBX_ISR(void)
{
  switch (TBIV)        // Efficient switch-implementation
  {
    case  2:                                // TBCCR1
      TBCCR1 += 8;                          // Offset until next interrupt
      break;
    case  4:                                // TBCCR2
      TBCCR2 += 16;                         // Offset until next interrupt
      break;
    case 14:                                // Overflow
      P1OUT ^= 0x01;                        // Toggle P1.0
      break;
  }
}
