//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P1.0, 3.6,3.7, Cont. Mode ISR, HF XTAL ACLK
//
//  Description: Use Timer1_A2 CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, TA1CCR0, TA1CCR1
//  output units are optionally selected with port pins P3.6 and P3.7
//  in toggle mode. As such, these pins will toggle when respective TA1CCRx
//  registers match the TA1R counter. Interrupts are also enabled with all
//  TA1CCRx units, software loads offset to next interval only - as long as the
//  interval offset is added to TA1CCRx, toggle rate is generated in hardware.
//  Timer1_A1 overflow ISR is used to toggle P1.0 with software. Proper use
//  of the TA1IV interrupt vector generator is demonstrated.
//  ACLK = MCLK = TA1CLK = LFXT1 = HF XTAL
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//  As coded with TACLK= HF XTAL and assuming HF XTAL = 8MHz, toggle rates are:
//  P1.1 = TA1CCR0 = 8MHz/(2*200) = 20kHz
//  P1.2 = TA1CCR1 = 8MHz/(2*1000) = 4kHz
//  P1.0 = overflow = 8MHz/(2*65536) = 61Hz
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | HF XTAL (3 – 16MHz crystal or resonator)
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
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS;                           // ACLK= LFXT1= HF XTAL
  BCSCTL3 |= LFXT1S1;                       // LFXT1S1 = 3-16Mhz

  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFF; i > 0; i--);             // Time for flag to set
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?
  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 (safe)

  P3SEL |= 0xC0;                            // P3.6 - P3.7 option select
  P3DIR |= 0xC0;                            // P3.6 - P3.7 output
  P1DIR |= 0x01;                            // P1.0 output
  TA1CCTL0 = OUTMOD_4 + CCIE;               // TACCR0 toggle, interrupt enabled
  TA1CCTL1 = OUTMOD_4 + CCIE;               // TACCR1 toggle, interrupt enabled
  TA1CCR0 = 200;
  TA1CCR1 = 1000;
  TA1CTL = TASSEL_1 + MC_2 + TAIE;          // ACLK, contmode, interrupt enabled

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
}

// Timer1_A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (void)
{
  TA1CCR0 += 200;                           // Add Offset to TA1CCR0
}

// Timer1_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A1(void)
{
  switch (__even_in_range(TA1IV, 10))        // Efficient switch-implementation
  {
    case  2: TA1CCR1 += 1000;               // Add Offset to TA1CCR1
             break;
    case 10: P1OUT ^= 0x01;                 // overflow
             break;
  }
}

