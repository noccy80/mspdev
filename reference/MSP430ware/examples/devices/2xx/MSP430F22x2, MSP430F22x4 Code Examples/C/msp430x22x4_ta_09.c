//******************************************************************************
//  MSP430F22x4 Demo - Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
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
//  ACLK = MCLK = TACLK = LFXT1 = HF XTAL
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//  As coded with TACLK= HF XTAL and assuming HF XTAL = 8MHz, toggle rates are:
//  P1.1 = TACCR0 = 8MHz/(2*200) = 20kHz
//  P1.2 = TACCR1 = 8MHz/(2*1000) = 4kHz
//  P1.3 = TACCR2 = 8MHz/(2*10000) = 400Hz
//  P1.0 = overflow = 8MHz/(2*65536) = 61Hz
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 | HF XTAL (3 – 16MHz crystal or resonator)
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
  TACCTL0 = OUTMOD_4 + CCIE;                // TACCR0 toggle, interrupt enabled
  TACCTL1 = OUTMOD_4 + CCIE;                // TACCR1 toggle, interrupt enabled
  TACCTL2 = OUTMOD_4 + CCIE;                // TACCR2 toggle, interrupt enabled
  TACCR0 = 200;
  TACCR1 = 1000;
  TACCR2 = 10000;
  TACTL = TASSEL_1 + MC_2 + TAIE;           // ACLK, contmode, interrupt enabled

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
  TACCR0 += 200;                            // Add Offset to TACCR0
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
  switch (TAIV)        // Efficient switch-implementation
  {
    case  2: TACCR1 += 1000;                // Add Offset to TACCR1
             break;
    case  4: TACCR2 += 10000;               // Add Offset to TACCR2
             break;
    case 10: P1OUT ^= 0x01;                 // Timer_A3 overflow
             break;
  }
}

