//******************************************************************************
//  MSP430x41x2 Demo - Timer_A, Toggle P5.1, Overflow ISR, DCO SMCLK
//
//  Description: This program toggles P5.1 using software and the Timer_A
//  overflow ISR. In this example an ISR triggers when TA overflows.
//  Inside the ISR P5.1 is toggled. Toggle rate is 16Hz when default FLL+
//  register settings and an external 32kHz watch crystal.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//         MSP430x41x2
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//*****************************************************************************

#include  <msp430x41x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  TACTL = TASSEL_2 + MC_2 + TAIE;           // SMCLK, cont. mode, interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
 switch( TAIV )
 {
   case  2: break;                          // CCR1 not used
   case  4: break;                          // CCR2 not used
   case 10: P5OUT ^= 0x02;                  // overflow
            break;
 }
}

