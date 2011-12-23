//******************************************************************************
//  MSP430xG46x Demo - Timer_A, Toggle P5.1, Overflow ISR, DCO SMCLK
//
//  Description: This program toggles P5.1 using software and the Timer_A
//  overflow ISR. In this example an ISR triggers when TA overflows.
//  Inside the ISR P5.1 is toggled. Toggle rate is 16Hz when using default
//  FLL+ register settings and an external 32kHz watch crystal.	
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//           MSP430xG461x
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//  K. Quiring/ M. Mitchell
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include <msp430xG46x.h>

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

  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  TACTL = TASSEL_2 + MC_2 + TAIE;           // SMCLK, cont. mode, interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A (void)
{
  switch( TAIV )
  {
    case  2: break;                         // TACCR1 not used
    case  4: break;                         // TACCR2 not used
    case 10: P5OUT ^= 0x02;                 // overflow
             break;
  }
}

