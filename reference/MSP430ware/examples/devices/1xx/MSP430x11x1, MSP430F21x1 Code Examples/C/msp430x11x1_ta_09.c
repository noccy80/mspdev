//******************************************************************************
//  MSP430x11x1 Demo - Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
//
//  Description: Use Timer_A CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, CCR0, CCR1 and CCR2 output
//  units are optionally selected with port pins P1.1, P1.2 and P1.3 in toggle
//  mode. As such, these pins will toggle when respective CCRx registers match
//  the TAR counter. Interrupts are also enabled with all CCRx units,
//  software loads offset to next interval only - as long as the interval offset
//  is aded to CCRx, toggle rate is generated in hardware. Timer_A overflow ISR
//  is used to toggle P1.0 with software. Proper use of the TAIV interrupt
//  vector generator is demonstrated.
//  ACLK= MCLK= TACLK= HF XTAL
//  As coded with TACLK= HF XTAL and assuming HF XTAL= 8MHz, toggle rates are:
//  P1.1 = CCR0 = 8MHz/(2*200) = 20kHz
//  P1.2 = CCR1 = 8MHz/(2*1000) = 4kHz
//  P1.3 = CCR2 = 8MHz/(2*10000) = 400Hz
//  P1.0 = overflow = 8MHz/(2*65536) = 61Hz
//  //* HF XTAL NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//           MSP430F1121
//         ---------------
//     /|\|            XIN|-
//      | |               | HF XTAL (455k - 8MHz)
//      --|RST        XOUT|-
//        |               |
//        |       P1.1/TA0|--> CCR0
//        |       P1.2/TA1|--> CCR1
//        |       P1.3/TA2|--> CCR2
//        |           P1.0|--> Overflow/software
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include <msp430x11x1.h>

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS;                           // ACLK= LFXT1= HF XTAL

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK= LFXT1 (safe)
  P1SEL |= 0x0E;                            // P1.1 - P1.3 option select
  P1DIR |= 0x0F;                            // P1.0 - P1.3 outputs
  CCTL0 = OUTMOD_4 + CCIE;                  // CCR0 toggle, interrupt enabled
  CCTL1 = OUTMOD_4 + CCIE;                  // CCR1 toggle, interrupt enabled
  CCTL2 = OUTMOD_4 + CCIE;                  // CCR2 toggle, interrupt enabled
  CCR0 = 200;
  CCR1 = 1000;
  CCR2 = 10000;
  TACTL = TASSEL_1 + MC_2 + TAIE;           // ACLK, contmode, interrupt enabled

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
  CCR0 += 200;                              // Add Offset to CCR0
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
  switch( TAIV )
  {
  case  2: CCR1 += 1000;                    // Add Offset to CCR1
           break;
  case  4: CCR2 += 10000;                   // Add Offset to CCR2
           break;
  case 10: P1OUT ^= 0x01;                   // Timer_A3 overflow
           break;
 }
}

