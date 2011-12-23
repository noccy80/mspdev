//******************************************************************************
//  MSP430xG46x Demo - Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
//
//  Description: Use Timer_A CCRx units and overflow to generate four
//  independent timing intervals. For demonstration, TACCR0, TACCR1 and TACCR2
//  output units are optionally selected with port pins P1.1, P1.2 and P1.3
//  in toggle mode. As such, these pins will toggle when respective CCRx
//  registers match the TAR counter. Interrupts are also enabled with all
//  CCRx units, software loads offset to next interval only - as long as
//  the interval offset is added to CCRx, toggle rate is generated in
//  hardware. Timer_A overflow ISR is used to toggle P1.0 with software.
//  Proper use of the TAIV interrupt vector generator is demonstrated.
//  ACLK = TACLK = 32kHz, MCLK = SMCLK = default DCO ~1048kHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//  As coded and with TACLK = 32768Hz, toggle rates are:
//  TACCR0 = 32768/(2*4) = 4096Hz
//  TACCR1 = 32768/(2*16) = 1024Hz
//  TACCR2 = 32768/(2*100) = 163.84Hz
//  P1.3= overflow = 32768/(2*65536) = 0.25Hz
//
//               MSP430xG461x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.0/TA0|--> TACCR0
//           |         P1.2/TA1|--> TACCR1
//           |         P2.0/TA2|--> TACCR2
//           |             P1.3|--> Overflow/software
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************

#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW +WDTHOLD;                  // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P1SEL |= 0x05;                            // P1.2,0 option select
  P1DIR |= 0x0D;                            // P1.3,2,0 outputs
  P2SEL |= 0x01;                            // P2.0 option select
  P2DIR |= 0x01;                            // P2.0 output
  TACCTL0 = OUTMOD_4 + CCIE;                // TACCR0 toggle, interrupt enabled
  TACCTL1 = OUTMOD_4 + CCIE;                // TACCR1 toggle, interrupt enabled
  TACCTL2 = OUTMOD_4 + CCIE;                // TACCR2 toggle, interrupt enabled
  TACTL = TASSEL_1 + MC_2 + TAIE;           // ACLK, contmode, interrupt enabled

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
  TACCR0 += 4;                                // Add Offset to TACCR0
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
  switch( TAIV )
  {
  case  2: TACCR1 += 16;                    // Add Offset to TACCR1
           break;
  case  4: TACCR2 += 100;                   // Add Offset to TACCR2
           break;
  case 10: P1OUT ^= 0x08;                   // Timer_A3 overflow
           break;
 }
}

