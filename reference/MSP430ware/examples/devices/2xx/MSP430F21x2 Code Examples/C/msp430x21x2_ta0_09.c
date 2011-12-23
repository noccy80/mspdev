//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
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
//  ACLK = MCLK = TA0CLK = LFXT1 = HF XTAL
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//  As coded with TA0CLK= HF XTAL and assuming HF XTAL = 8MHz, toggle rates are:
//  P1.1 = TA0CCR0 = 8MHz/(2*200) = 20kHz
//  P1.2 = TA0CCR1 = 8MHz/(2*1000) = 4kHz
//  P1.3 = TA0CCR2 = 8MHz/(2*10000) = 400Hz
//  P1.0 = overflow = 8MHz/(2*65536) = 61Hz
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//         --|RST          XOUT|-
//           |                 |
//           |         P1.1/TA0|--> TA0CCR0
//           |         P1.2/TA1|--> TA0CCR1
//           |         P1.3/TA2|--> TA0CCR2
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

  P1SEL |= 0x0E;                            // P1.1 - P1.3 option select
  P1DIR |= 0x0F;                            // P1.0 - P1.3 outputs
  TA0CCTL0 = OUTMOD_4 + CCIE;               // TA0CCR0 toggle, interrupt enabled
  TA0CCTL1 = OUTMOD_4 + CCIE;               // TA0CCR1 toggle, interrupt enabled
  TA0CCTL2 = OUTMOD_4 + CCIE;               // TA0CCR2 toggle, interrupt enabled
  TA0CCR0 = 200;
  TA0CCR1 = 1000;
  TA0CCR2 = 10000;
  TA0CTL = TASSEL_1 + MC_2 + TAIE;          // ACLK, contmode, interrupt enabled

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
}

// Timer0_A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
  TA0CCR0 += 200;                           // Add Offset to TA0CCR0
}

// Timer0_A1 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
  switch (__even_in_range(TAIV, 10))        // Efficient switch-implementation
  {
    case  2: TA0CCR1 += 1000;               // Add Offset to TA0CCR1
             break;
    case  4: TA0CCR2 += 10000;              // Add Offset to TA0CCR2
             break;
    case 10: P1OUT ^= 0x01;                 // Timer0_A3 overflow
             break;
  }
}

