//******************************************************************************
//   MSP430xG46x Demo - Timer_B, Toggle P5.1, Overflow ISR, 32kHz ACLK
//
//   Description: Toggle P5.1 using software and the Timer_B overflow ISR.
//   In this example an ISR triggers when TA overflows. Inside the ISR P5.1
//   is toggled. Toggle rate is exactly 0.5Hz.
//   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                 MSP430xG46x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
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

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P5DIR |= 0x002;                           // P5.1 output

  TBCTL = TBSSEL_1+MC_2+TBIE;               // ACLK, cont. mode, interrupt

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3, interrupts enabled
}

// Timer_B7 Interrupt Vector (TBIV) handler -- common for TBCCR1-4 and overflow
#pragma vector=TIMERB1_VECTOR
__interrupt void Timer_B (void)
{
  switch( TBIV )
  {
    case  2: break;                         // TACCR1 not used
    case  4: break;                         // TACCR2 not used
    case 14: P5OUT ^= 0x02;                 // overflow (Toggle P5.1)
             break;
  }
}

